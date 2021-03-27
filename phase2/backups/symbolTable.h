#include<stdlib.h>
#include<stdio.h> 
#include<string.h> 
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
    union
    {
        Variable *varVal;
        Function *funcVal;
    } value;
    struct SymbolTableEntry * next;
    enum SymbolType type;
} SymbolTableEntry;

typedef struct SymbolTable
{
    SymbolTableEntry **symboltable;
} SymbolTable;
static unsigned int SymTable_hash(const char *pcKey);


SymbolTable  * symbolTable_create();
short symbolTable_insert( SymbolTable  *symbolTable , SymbolTableEntry *  bucket , int scope);
short symbolTable_hide(  SymbolTable * symbolTable  , int scope);
short symbolTable_lookup( SymbolTable * symbolTable , int scope );
short symbolTable_lookup_scopeless( SymbolTable * symbolTable );
void symbolTable_print(SymbolTable *symbolTable);


Variable * create_var(const char *name,unsigned int scope,unsigned int line);
Function * create_func(const char *name , unsigned int scope , unsigned int line);
SymbolTableEntry *  create_bucket_var( short  isActive , Variable  * var  , enum SymbolType type  );
SymbolTableEntry *  create_bucket_func( short  isActive , Function *  func  , enum SymbolType type  );


// function lala
