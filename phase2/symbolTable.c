#include "symbolTable.h"
unsigned int SIZE =500;

SymbolTable *symbolTable_create()
{
    unsigned int i = 0;
    SymbolTable * symtable = malloc(sizeof(SymbolTable) );
    symtable->symboltable= malloc(SIZE * sizeof(SymbolTableEntry));
    

    for (i = 0; i < SIZE; i++)
    {
        symtable->symboltable[i]=NULL;
        
    }

    return symtable;
}
static unsigned int SymTable_hash(const char *pcKey)
{

    size_t ui;
    unsigned int uiHash = 0U;
    for (ui = 0U; pcKey[ui] != '\0'; ui++)

        uiHash = (uiHash + pcKey[ui]) / 3;

    /*
size_t ui;
unsigned int uiHash = 0U;
for (ui = 0U; pcKey[ui] != '\0'; ui++)
 
uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
return (uiHash%Size);*/
    return (uiHash % SIZE);
}

Variable * create_var(const char *name,unsigned int scope,unsigned int line)
{
    Variable * var = malloc(sizeof(Variable));
    int length = strlen(name)+1;
    var->name= malloc(sizeof(char)* length);
    memcpy(var->name , name , length * sizeof(char));
    var->scope=scope;
    var->line=line;
    return var;
}
Function * create_func(const char *name , unsigned int scope , unsigned int line)
{
    
    if(name==NULL) { fprintf(stderr,"NULL name create_func\n") ; return NULL;}
    Function * func = malloc(sizeof(Function));
    if(func==NULL) {fprintf(stderr,"error allocating func\n"); return NULL;}
    int length = strlen(name)+1;

    func->name= malloc(sizeof(char)* length);
    memcpy(func->name , name , length * sizeof(char));
    func->scope=scope;
    func->line=line;

    return func;
    
}
SymbolTableEntry *  create_bucket_var( short  isActive , Variable  * var  , enum SymbolType type  )
{
    SymbolTableEntry *  bucket = malloc(sizeof(SymbolTableEntry));
    bucket->isActive=1;
    bucket->next=NULL;
    bucket->type=type;
    bucket->value.varVal=var;
    bucket->value.funcVal=NULL;
    return bucket;
    
} 
SymbolTableEntry *  create_bucket_func( short  isActive , Function *  func  , enum SymbolType type  )
{   
    SymbolTableEntry *  bucket = malloc(sizeof(SymbolTableEntry));
    bucket->isActive=1;
    bucket->next=NULL;
    bucket->type=type;
    bucket->value.varVal=NULL;
    bucket->value.funcVal=func;
    return bucket;
}

short symbolTable_insert(SymbolTable *symbolTable, SymbolTableEntry * bucket, int scope)
{

    unsigned int index = 0;
    SymbolTableEntry * head , *tmp;

    if (bucket->type == USERFUNC || bucket->type == LIBFUNC)
    {
        index = SymTable_hash(bucket->value.funcVal->name);
    }
    else
    {
        index = SymTable_hash(bucket->value.varVal->name);
    }
    index =2;
    head = symbolTable->symboltable[index];
    
    if(head==NULL) { symbolTable->symboltable[index]=bucket; return 1; }
    tmp=head;
    while(tmp->next!=NULL)
    {
        tmp=tmp->next;
    }
    tmp->next=bucket;
    

    return 1;
}

void print_var(Variable * var)
{
    fprintf(stdout, " line : %d", var->line);
    fprintf(stdout, " name :%s", var->name);
    fprintf(stdout, " scope %d", var->scope);

}
void print_func(Function * func)
{
    fprintf(stdout, " line : %d", func->line);
    fprintf(stdout, " name :%s", func->name);
    fprintf(stdout, " scope %d", func->scope);

}
void symbolTable_print(SymbolTable *symbolTable)
{
    unsigned int i =0;
    SymbolTableEntry * head , *tmp;
    for(i=0; i<SIZE; i++)
    {
        fprintf(stdout ,"index : %d\n", i);
        tmp=symbolTable->symboltable[i];
        while(tmp!=NULL )
        {
            fprintf(stdout,"status : %d" , tmp->isActive);
            fprintf(stdout," type : %d", tmp->type);
            (tmp->value.funcVal==NULL) ? print_var(tmp->value.varVal): print_func(tmp->value.funcVal);
            fprintf(stdout," --> ");
        
            tmp=tmp->next;
        }
        fprintf(stdout,"\n");

    }

}

short symbolTable_hide(SymbolTable * symbolTable, int scope)
{

}
short symbolTable_lookup(SymbolTable * symbolTable, int scope)
{

}
short symbolTable_lookup_scopeless(SymbolTable  * symbolTable)
{

}
