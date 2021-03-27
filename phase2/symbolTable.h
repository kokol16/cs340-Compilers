#include<stdlib.h>
#include<stdio.h> 
#include<string.h> 
#define HASH_MULTIPLIER 65599

typedef struct Variable
{
    const char *name;
    unsigned int scope;
    unsigned int line;
} Variable;
typedef struct Function
{
    const char *name;
    //List of arguments
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
    union
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
short symbolTable_insert( SymbolTable  *symbolTable , SymbolTableEntry *  bucket , unsigned int  scope);
short symbolTable_hide(  SymbolTable * symbolTable  , unsigned int scope);
SymbolTableEntry * symbolTable_lookup( SymbolTable * symbolTable , unsigned int  scope );
SymbolTableEntry *  symbolTable_lookup_scopeless( SymbolTable * symbolTable );
SymbolTableEntry *symbolTable_lookup_head(SymbolTable *symbolTable, unsigned int scope);

void symbolTable_print(SymbolTable *symbolTable);


Variable * create_var(const char *name,unsigned int scope,unsigned int line);
Function * create_func(const char *name , unsigned int scope , unsigned int line);
SymbolTableEntry *  create_bucket_var( short  isActive , Variable  * var  , enum SymbolType type  );
SymbolTableEntry *  create_bucket_func( short  isActive , Function *  func  , enum SymbolType type  );
void symbolTable_print_scope_list(SymbolTable *symbolTable, unsigned int scope);


// function lala
