#include "vm.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
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

int main()
{
    read_binary_file();
}
double *consts_number;
unsigned total_numbers;
char **consts_string;
unsigned total_strings;
unsigned total_user_funcs;
struct userfunc *user_funcs;
void read_binary_file()
{
    unsigned magic_number;
    FILE *fp;

    fp = fopen("target_code.abc", "rb"); // r for read, b for binary

    fread(&magic_number, sizeof(magic_number), 1, fp);
    fprintf(stderr, "magic number %u\n", magic_number);
    fread(&total_numbers, sizeof(total_numbers), 1, fp);
    fprintf(stderr, "total number %u\n", total_numbers);

    consts_number = malloc(sizeof(double) * total_numbers);
    
    fread(consts_number, sizeof(double), total_numbers, fp);


    fread(&total_strings, sizeof(total_strings), 1, fp);

    fprintf(stderr, "total string %u\n", total_strings);

    consts_string = malloc(sizeof(char) * total_strings);
    int i = 0;
    unsigned size = 0;

    //10 5 "lala" 6 "ofsafdf"
    for (i = 0; i < total_strings; i++)
    {
        fread(&size, sizeof(size), 1, fp);
        consts_string[i] = malloc(sizeof(char) * size);
        fread(consts_string[i], sizeof(char), size, fp);
    }

   fread(&total_user_funcs, sizeof( total_user_funcs), 1, fp);

    fprintf(stderr, "total user funcs %u\n", total_user_funcs);

    user_funcs = malloc(sizeof(struct userfunc*) * total_user_funcs );
    
    

    //10 5 "lala" 6 "ofsafdf"
    for (i = 0; i <  total_user_funcs; i++)
    {
        fread( &user_funcs[i].address, sizeof(user_funcs[i].address), 1, fp);
        fread( &user_funcs[i].localSize, sizeof(user_funcs[i].localSize), 1, fp);
        fread(&size, sizeof(size), 1, fp);
        user_funcs[i].id = malloc(sizeof(char) * size);
        fread(user_funcs[i].id, sizeof(char), size, fp);
    }
 for (i = 0; i <  total_user_funcs; i++)
    {
        fprintf(stderr, "%s\n", user_funcs[i].id);
    }
  
    for (i = 0; i < total_strings; i++)
    {
        fprintf(stderr, "%s\n", consts_string[i]);
    }

    fclose(fp);
}