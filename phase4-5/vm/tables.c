#include "vm.h"
#include <stdlib.h>
#include <assert.h>
#define HASH_MULTIPLIER 65599

void avm_table_inc_ref_counter(avm_table *t)
{
    ++t->refCounter;
}
void avm_table_dec_ref_counter(avm_table *t)
{
    assert(t->refCounter > 0);
    if (!--t->refCounter)
    {
        avm_table_destroy(t);
    }
}

void memclear_table(avm_memcell *m)
{
    assert(m->data.tableVal);
    avm_table_dec_ref_counter(m->data.tableVal);
}
typedef void (*memclear_func_t)(avm_memcell *);

void memclear_string(avm_memcell *m)
{
    assert(m->data.strVal);
    free(m->data.strVal);
}

memclear_func_t memclearFuncs[] = {
    0, //number
    memclear_string,
    0, //bool
    memclear_table,
    0, //userfunc
    0, //libfunc
    0, //nil
    0  //undef

};
void avm_memcell_clear(avm_memcell *m)
{
    if (m->type != undef_m)
    {
        memclear_func_t f = memclearFuncs[m->type];
        if (f)
        {
            (*f)(m);
        }
        m->type = undef_m;
    }
}
void avm_table_buckets_destroy(avm_table_bucket **p)
{
    unsigned i = 0;
    for (i = 0; i < AVM_TABLE_SIZE; ++i, ++p)
    {
        for (avm_table_bucket *b = *p; b;)
        {
            avm_table_bucket *del = b;
            b = b->next;
            avm_memcell_clear(del->key);
            avm_memcell_clear(del->value);
            free(del);
        }
        p[i] = (avm_table_bucket *)0;
    }
}
void avm_table_destroy(avm_table *t)
{
    avm_table_buckets_destroy(t->str_indexed);
    avm_table_buckets_destroy(t->bool_indexed);
    avm_table_buckets_destroy(t->num_indexed);
    avm_table_buckets_destroy(t->library_func_indexed);
    avm_table_buckets_destroy(t->user_func_indexed);

    free(t);
}

void avm_table_buckets_init(avm_table_bucket **p)
{
    unsigned i = 0;
    for (i = 0; i < AVM_TABLE_SIZE; ++i)
    {
        p[i] = (avm_table_bucket *)0;
    }
}


avm_table *avm_table_new()
{
    avm_table *t = malloc(sizeof(avm_table));
    AVM_WIPEOUT(t);
    t->refCounter = t->total = 0;
    avm_table_buckets_init(t->num_indexed);
    avm_table_buckets_init(t->bool_indexed);
    avm_table_buckets_init(t->str_indexed);
    avm_table_buckets_init(t->library_func_indexed);
    avm_table_buckets_init(t->user_func_indexed);
    return t;
}
/*
 number_m = 0,
    string_m = 1,
    bool_m = 2,
    table_m = 3,
    userfunc_m = 4,
    libfunc_m = 5,
    nil_m = 6,
    undef_m = 7*/
static unsigned int hash_str(const char *pcKey)
{
    size_t ui;
    unsigned int uiHash = 0U;
    for (ui = 0U; pcKey[ui] != '\0'; ui++)

        uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
    return (uiHash % AVM_TABLE_SIZE);
}

static unsigned int hash_double(double key)
{
    int _key = (int)key;
    return (_key * 2654435761 % 2 ^ 32) % AVM_TABLE_SIZE;
}

avm_table_bucket *avm_table_create_bucket(avm_memcell *left, avm_memcell *right)
{
    avm_table_bucket *bucket = malloc(sizeof(avm_table_bucket));
    bucket->key = left;
    bucket->value = right;
    bucket->next = NULL;
    return bucket;
}

int avm_table_set_str_indexed(avm_table *table, avm_memcell *left, avm_memcell *right)
{
    if (table == NULL)
        return 0;
    int index = hash_str(left->data.strVal);

    avm_table_bucket *tmp = table->str_indexed[index];
    //avm_table_bucket *bucket = avm_table_create_bucket(left, right);

    if (tmp == NULL)
    {
        //table->str_indexed[index] = bucket;
        return 0;
    }
    avm_table_bucket *prev;
    while (tmp->next != NULL)
    {

        if (tmp->key == left)
        {
            if (right->type == nil_m)
            {
                if (prev == NULL)
                {

                    table->str_indexed[index] = tmp->next;
                }
                else
                {
                    prev->next = tmp->next;
                }

                avm_memcell_clear(tmp->key);
                avm_memcell_clear(tmp->value);
                free(tmp);
            }
            else
            {
                avm_assign(tmp->value, right);
            }
            return 1;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    //tmp->next = bucket;
    return 1;
}
int avm_table_set_lib_func_indexed(avm_table *table, avm_memcell *left, avm_memcell *right)
{
    if (table == NULL)
        return 0;
    int index = hash_str(left->data.libfuncVal);

    avm_table_bucket *tmp = table->library_func_indexed[index];
    //avm_table_bucket *bucket = avm_table_create_bucket(left, right);

    if (tmp == NULL)
    {
        //table->library_func_indexed[index] = bucket;
        return 0;
    }
    avm_table_bucket *prev;
    while (tmp->next != NULL)
    {
        if (tmp->key == left)
        {
            if (right->type == nil_m)
            {
                if (prev == NULL)
                {

                    table->library_func_indexed[index] = tmp->next;
                }
                else
                {
                    prev->next = tmp->next;
                }

                avm_memcell_clear(tmp->key);
                avm_memcell_clear(tmp->value);
                free(tmp);
            }
            else
            {
                avm_assign(tmp->value, right);
            }
            return 1;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    //tmp->next = bucket;
    return 1;
}

int avm_table_set_user_func_indexed(avm_table *table, avm_memcell *left, avm_memcell *right)
{
    if (table == NULL)
        return 0;
    int index = hash_str(user_funcs[left->data.funVal].id);

    avm_table_bucket *tmp = table->user_func_indexed[index];
    //avm_table_bucket *bucket = avm_table_create_bucket(left, right);

    if (tmp == NULL)
    {
    //    table->user_func_indexed[index] = bucket;
        return 0;
    }
    avm_table_bucket *prev;
    while (tmp->next != NULL)
    {
        if (tmp->key == left)
        {
            if (right->type == nil_m)
            {
                if (prev == NULL)
                {

                    table->user_func_indexed[index] = tmp->next;
                }
                else
                {
                    prev->next = tmp->next;
                }

                avm_memcell_clear(tmp->key);
                avm_memcell_clear(tmp->value);
                free(tmp);
            }
            else
            {
                avm_assign(tmp->value, right);
            }
            return 1;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    //tmp->next = bucket;
    return 1;
}

int avm_table_set_number_indexed(avm_table *table, avm_memcell *left, avm_memcell *right)
{
    if (table == NULL)
        return 0;
    int index = hash_double(left->data.numVal);

    avm_table_bucket *tmp = table->num_indexed[index];
    //avm_table_bucket *bucket = avm_table_create_bucket(left, right);

    if (tmp == NULL)
    {
        //table->num_indexed[index] = bucket;
        return 0;
    }
    avm_table_bucket *prev;
    while (tmp->next != NULL)
    {
        if (tmp->key == left)
        {
            if (right->type == nil_m)
            {
                if (prev == NULL)
                {

                    table->num_indexed[index] = tmp->next;
                }
                else
                {
                    prev->next = tmp->next;
                }
                avm_memcell_clear(tmp->key);
                avm_memcell_clear(tmp->value);
                free(tmp);
            }
            else
            {
                avm_assign(tmp->value, right);
            }
            return 1;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    //tmp->next = bucket;
    return 1;
}

int avm_table_set_bool_indexed(avm_table *table, avm_memcell *left, avm_memcell *right)
{
    if (table == NULL)
        return 0;
    int index = left->data.boolVal;

    avm_table_bucket *tmp = table->bool_indexed[index];
    //avm_table_bucket *bucket = avm_table_create_bucket(left, right);

    if (tmp == NULL)
    {
        //table->bool_indexed[index] = bucket;
        return 0;
    }
    avm_table_bucket *prev;
    while (tmp->next != NULL)
    {
        if (tmp->key == left)
        {
            if (right->type == nil_m)
            {
                if (prev == NULL)
                {

                    table->bool_indexed[index] = tmp->next;
                }
                else
                {
                    prev->next = tmp->next;
                }

                avm_memcell_clear(tmp->key);
                avm_memcell_clear(tmp->value);
                free(tmp);
            }
            else
            {
                avm_assign(tmp->value, right);
            }
            return 1;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    //tmp->next = bucket;
    return 1;
}

avm_memcell *avm_table_get_number_indexed(avm_table *table, avm_memcell *left)
{
    if (table == NULL)
        return NULL;
    int index = hash_double(left->data.numVal);

    avm_table_bucket *tmp = table->num_indexed[index];
    while (tmp != NULL)
    {
        if (tmp->key == left)
        {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return NULL;
}

avm_memcell *avm_table_get_string_indexed(avm_table *table, avm_memcell *left)
{
    if (table == NULL)
        return NULL;
    int index = hash_str(left->data.strVal);

    avm_table_bucket *tmp = table->str_indexed[index];
    while (tmp != NULL)
    {
        if (tmp->key == left)
        {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return NULL;
}

avm_memcell *avm_table_get_bool_indexed(avm_table *table, avm_memcell *left)
{
    if (table == NULL)
        return NULL;
    int index = (left->data.boolVal);

    avm_table_bucket *tmp = table->bool_indexed[index];
    while (tmp != NULL)
    {
        if (tmp->key == left)
        {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return NULL;
}

avm_memcell *avm_table_get_user_func_indexed(avm_table *table, avm_memcell *left)
{
    if (table == NULL)
        return NULL;
    int index = hash_str(user_funcs[left->data.funVal].id);

    avm_table_bucket *tmp = table->user_func_indexed[index];
    while (tmp != NULL)
    {
        if (tmp->key == left)
        {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return NULL;
}

avm_memcell *avm_table_get_lib_func_indexed(avm_table *table, avm_memcell *left)
{
    if (table == NULL)
        return NULL;
    int index = hash_str(left->data.libfuncVal);

    avm_table_bucket *tmp = table->library_func_indexed[index];
    while (tmp != NULL)
    {
        if (tmp->key == left)
        {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return NULL;
}
int avm_table_get(avm_table *table, avm_memcell *left)
{
    switch (left->type)
    {
    case number_m:
        avm_table_get_number_indexed(table, left);
        table->total++;

        break;
    case string_m:
        avm_table_get_string_indexed(table, left);

        table->total++;

        break;

    case bool_m:
        avm_table_get_bool_indexed(table, left);

        table->total++;

        break;
    case userfunc_m:
        avm_table_get_user_func_indexed(table, left);

        table->total++;

        break;
    case libfunc_m:
        avm_table_get_lib_func_indexed(table, left);

        table->total++;

        break;
    default:
        //avm error???
        break;
    }
}

int avm_table_set(avm_table *table, avm_memcell *left, avm_memcell *right)
{
    switch (left->type)
    {
    case number_m:
        avm_table_set_number_indexed(table, left, right);
        table->total++;

        break;
    case string_m:
        avm_table_set_str_indexed(table, left, right);
        table->total++;

        break;

    case bool_m:
        avm_table_set_bool_indexed(table, left, right);
        table->total++;

        break;
    case userfunc_m:
        avm_table_set_user_func_indexed(table, left, right);
        table->total++;

        break;
    case libfunc_m:
        avm_table_set_lib_func_indexed(table, left, right);
        table->total++;

        break;
    default:
        //avm error???
        break;
    }
}