#pragma once
#include <string.h>
#include "exec_arith/exec_arith.h"
#include "exec_funcs/exec_funcs.h"
#include "exec_jumps/exec_jumps.h"
#include "exec_tables/exec_tables.h"
#include "exec_other/exec_other.h"
#define AVM_STACKENV_SIZE 4
#define AVM_MAX_INSTRUCTIONS 24
#define AVM_ENDING_PC codeSize
#define AVM_STACK_SIZE 4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_SIZE 211
extern unsigned char execution_finished ;
extern unsigned pc ;
extern unsigned currLine ;
extern unsigned codeSize;
extern instruction *code;
extern unsigned totalActuals;
extern double *consts_number;
extern unsigned total_numbers;
extern char **consts_string;
extern unsigned total_strings;
extern unsigned total_user_funcs;
extern struct userfunc *user_funcs;
extern char **lib_funcs;
extern unsigned total_lib_funcs;
extern struct avm_memcell ax, bx, cx;
extern struct avm_memcell retval;
extern unsigned top, topsp;
typedef enum avm_memcell_t
{
    number_m = 0,
    string_m = 1,
    bool_m = 2,
    table_m = 3,
    userfunc_m = 4,
    libfunc_m = 5,
    nil_m = 6,
    undef_m = 7

} avm_memcell_t;

typedef struct avm_table avm_table;
typedef struct avm_memcell
{
    avm_memcell_t type;
    union data
    {
        double numVal;
        char *strVal;
        unsigned char boolVal;
        avm_table *tableVal;
        unsigned funVal;
        char *libfuncVal;
    } data;

} avm_memcell;

typedef struct avm_table_bucket
{
    struct avm_memcell *key;
    struct avm_memcell *value;
    struct avm_table_bucket *next;
} avm_table_bucket;

typedef struct avm_table
{
    unsigned refCounter;
    avm_table_bucket *str_indexed[AVM_TABLE_SIZE];
    avm_table_bucket *num_indexed[AVM_TABLE_SIZE];
    avm_table_bucket *user_func_indexed[AVM_TABLE_SIZE];
    avm_table_bucket *library_func_indexed[AVM_TABLE_SIZE];
    avm_table_bucket *bool_indexed[AVM_TABLE_SIZE];
    unsigned total;
} avm_table;

avm_memcell stack[AVM_STACK_SIZE];
void avm_ini_stack(void);
avm_table *avm_table_new();
void avm_table_destroy(avm_table *);
avm_memcell *avm_table_get_elem(avm_memcell *key);
void avm_table_set_elem(avm_memcell *key, avm_memcell *value);
void read_binary_file();
avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg);
void avm_memcell_clear(avm_memcell *m);
void avm_assign(avm_memcell *lv, avm_memcell *rv);

//tables
void avm_table_dec_ref_counter(avm_table *t);
void avm_table_inc_ref_counter(avm_table *t);
avm_table *avm_table_new();
int avm_table_insert_str_indexed(avm_table *table, avm_memcell *left, avm_memcell *right);
int avm_table_insert_lib_func_indexed(avm_table *table, avm_memcell *left, avm_memcell *right);

int avm_table_insert_user_func_indexed(avm_table *table, avm_memcell *left, avm_memcell *right);

int avm_table_insert_number_indexed(avm_table *table, avm_memcell *left, avm_memcell *right);

int avm_table_insert_bool_indexed(avm_table *table, avm_memcell *left, avm_memcell *right);

avm_memcell *avm_table_get_number_indexed(avm_table *table, avm_memcell *left);

avm_memcell *avm_table_get_string_indexed(avm_table *table, avm_memcell *left);

avm_memcell *avm_table_get_bool_indexed(avm_table *table, avm_memcell *left);

avm_memcell *avm_table_get_user_func_indexed(avm_table *table, avm_memcell *left);

avm_memcell *avm_table_get_lib_func_indexed(avm_table *table, avm_memcell *left);
int avm_table_get(avm_table *table, avm_memcell *left);

int avm_table_insert(avm_table *table, avm_memcell *left, avm_memcell *right);

void avm_error(char *message , char * arg1 , char * arg2);
