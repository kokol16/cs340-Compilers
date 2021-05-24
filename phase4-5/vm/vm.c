#include "vm.h"
#include <stdlib.h>
#include <assert.h>
void avm_ini_stack(void)
{
    unsigned i = 0;
    for (i = 0; i < AVM_STACK_SIZE; ++i)
    {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

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
void avm_memcell_clear(avm_memcell *m)
{
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
            avm_memcell_clear(&del->key);
            avm_memcell_clear(&del->value);
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