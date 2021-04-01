#include<stdlib.h>
#include<stdio.h> 
#include<string.h> 
#define HASH_MULTIPLIER 65599
#define ERROR_FUNC 2
#define ERROR_VAR 3 
typedef struct Variable
{
    const char *name;
    unsigned int scope;
    unsigned int line;
} Variable;
typedef struct Function
{
    const char *name;

    struct SymbolTableEntry * head_arg;

    unsigned int scope;
    unsigned int line;
} Function;

enum SymbolType
{
    GLOBAL,
    LOCAL,
    FORMAL,
    USERFUNC,
    LIBFUNC
};
typedef struct SymbolTableEntry
{
    short  isActive;
    short isScopeListHead;
    struct value
    {
        Variable *varVal;
        Function *funcVal;
    } value;
    struct SymbolTableEntry * next;
    struct SymbolTableEntry * next_same_scope;
    struct SymbolTableEntry * next_arg;

    enum SymbolType type;
} SymbolTableEntry;

typedef struct SymbolTable
{
    SymbolTableEntry **symboltable;
} SymbolTable;
static unsigned int SymTable_hash(const char *pcKey);


SymbolTable  * symbolTable_create();
short symbolTable_insert( SymbolTable  *symbolTable , SymbolTableEntry *  bucket );
short symbolTable_hide(  SymbolTable * symbolTable  , unsigned int scope);
SymbolTableEntry * symbolTable_lookup_scope( SymbolTable * symbolTable , unsigned int  scope );
SymbolTableEntry *  symbolTable_lookup_scopeless_var( SymbolTable * symbolTable, char * );
SymbolTableEntry *symbolTable_lookup_head(SymbolTable *symbolTable, unsigned int scope);


SymbolTableEntry *  symbolTable_lookup_scopeless( SymbolTable * symbolTable, char * );

short symbolTable_lookup_exists(SymbolTable *symbolTable, unsigned int scope , const char * name);

void symbolTable_print(SymbolTable *symbolTable);


Variable * create_var(const char *name,unsigned int scope,unsigned int line);
Function * create_func(const char *name , unsigned int scope , unsigned int line  );
SymbolTableEntry *  create_bucket_var( short  isActive , Variable  * var  , enum SymbolType type  );
SymbolTableEntry *  create_bucket_func( short  isActive , Function *  func  , enum SymbolType type  );
void symbolTable_print_scope_list(SymbolTable *symbolTable, unsigned int scope);
static short  load_lib_functions(SymbolTable *symtable);
Variable **sanitize_arguments(char *arguments, unsigned int *arg_size, unsigned int scope , unsigned int line);
SymbolTableEntry ** create_arguments_buckets(Variable ** arguments , unsigned int size );
short symbolTable_insert_args(SymbolTable * symTable, SymbolTableEntry ** arg_buckets ,unsigned int size );
short symbolTable_lookup_exists_exact_scope(SymbolTable *symbolTable, unsigned int scope, const char *name);
short is_library_func(SymbolTable *symTable ,const char *name);
short symbolTable_lookup_function(SymbolTable *symTable ,unsigned int scope);
char *SymbolType_to_string(enum SymbolType type);
void symbolTable_print_scopes(SymbolTable *symbolTable, unsigned int scope);
void print_func_args(SymbolTableEntry * fnc);

short  create_arguments(SymbolTable *symtable, char *arguments, unsigned int scope);
SymbolTableEntry *find_bucket_by_scope_and_name(SymbolTable *symtable, char *name, unsigned int scope);
SymbolTableEntry * last_func_inserted_in_current_scope(SymbolTable *symtable,  unsigned int scope);
double  find_bucket_scope( SymbolTable * symbolTable  , char * name);



// function lala
short is_function(SymbolTableEntry * lvalue);
