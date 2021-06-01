#include <string.h>
#define AVM_STACK_SIZE 4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_SIZE 211
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
    union datta
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
    struct avm_memcell key;
    struct avm_memcell value;
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