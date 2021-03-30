#include<stdlib.h>
#include<stdio.h> 
#include<string.h> 
#define HASH_MULTIPLIER 65599

typedef struct Variable
{
    const char *name;
    unsigned int scope;
    unsigned int line;
    struct Variable * next_arg;
} Variable;
typedef struct Function
{
    const char *name;

    Variable * arg_head;
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
SymbolTableEntry *  symbolTable_lookup_scopeless( SymbolTable * symbolTable );
SymbolTableEntry *symbolTable_lookup_head(SymbolTable *symbolTable, unsigned int scope);
short symbolTable_lookup_exists(SymbolTable *symbolTable, unsigned int scope , const char * name);

void symbolTable_print(SymbolTable *symbolTable);


Variable * create_var(const char *name,unsigned int scope,unsigned int line);
Function * create_func(const char *name , unsigned int scope , unsigned int line , Variable ** arguments , unsigned int arg_size);
SymbolTableEntry *  create_bucket_var( short  isActive , Variable  * var  , enum SymbolType type  );
SymbolTableEntry *  create_bucket_func( short  isActive , Function *  func  , enum SymbolType type  );
void symbolTable_print_scope_list(SymbolTable *symbolTable, unsigned int scope);
static short  load_lib_functions(SymbolTable *symtable);
Variable **sanitize_arguments(char *arguments, unsigned int *arg_size, unsigned int scope , unsigned int line);
void print_args(Function * func);
SymbolTableEntry ** create_arguments_buckets(Variable ** arguments , unsigned int size );
short symbolTable_insert_args(SymbolTable * symTable, SymbolTableEntry ** arg_buckets ,unsigned int size );
short symbolTable_lookup_exists_exact_scope(SymbolTable *symbolTable, unsigned int scope, const char *name);
short is_library_func(SymbolTable *symTable ,const char *name);
short symbolTable_lookup_function(SymbolTable *symTable ,unsigned int scope);

// function lala
