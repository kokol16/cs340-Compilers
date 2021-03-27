#include "symbolTable.h"
unsigned int SIZE = 10;
SymbolTable *symbolTable_create()
{
    unsigned int i = 0;
    SymbolTable *symtable = malloc(sizeof(SymbolTable));
    symtable->symboltable = malloc(SIZE * sizeof(SymbolTableEntry));

    for (i = 0; i < SIZE; i++)
    {
        symtable->symboltable[i] = NULL;
    }

    return symtable;
}
static unsigned int SymTable_hash(const char *pcKey)
{

    /*size_t ui;
    unsigned int uiHash = 0U;
    for (ui = 0U; pcKey[ui] != '\0'; ui++)

        uiHash = (uiHash + pcKey[ui]) / 3;*/

    size_t ui;
    unsigned int uiHash = 0U;
    for (ui = 0U; pcKey[ui] != '\0'; ui++)

        uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
    return (uiHash % SIZE);
}

Variable *create_var(const char *name, unsigned int scope, unsigned int line)
{
    Variable *var = malloc(sizeof(Variable));
    int length = strlen(name) + 1;
    var->name = malloc(sizeof(char) * length);
    memcpy((void *)var->name, name, length * sizeof(char));
    var->scope = scope;
    var->line = line;
    return var;
}
Function *create_func(const char *name, unsigned int scope, unsigned int line)
{

    if (name == NULL)
    {
        fprintf(stderr, "NULL name create_func\n");
        return NULL;
    }
    Function *func = malloc(sizeof(Function));
    if (func == NULL)
    {
        fprintf(stderr, "error allocating func\n");
        return NULL;
    }
    int length = strlen(name) + 1;

    func->name = malloc(sizeof(char) * length);
    memcpy((void *)func->name, name, length * sizeof(char));
    func->scope = scope;
    func->line = line;

    return func;
}
SymbolTableEntry *create_bucket_var(short isActive, Variable *var, enum SymbolType type)
{
    SymbolTableEntry *bucket = malloc(sizeof(SymbolTableEntry));
    bucket->isActive = 1;
    bucket->next = NULL;
    bucket->next_same_scope = NULL;
    bucket->type = type;
    bucket->value.varVal = var;
    bucket->isScopeListHead = 0;

    bucket->value.funcVal = NULL;
    return bucket;
}
SymbolTableEntry *create_bucket_func(short isActive, Function *func, enum SymbolType type)
{
    SymbolTableEntry *bucket = malloc(sizeof(SymbolTableEntry));
    bucket->isActive = 1;
    bucket->next = NULL;
    bucket->next_same_scope = NULL;
    bucket->type = type;
    bucket->isScopeListHead = 0;

    bucket->value.varVal = NULL;
    bucket->value.funcVal = func;
    return bucket;
}

short symbolTable_insert(SymbolTable *symbolTable, SymbolTableEntry *bucket, unsigned int scope)
{

    unsigned int index = 0;
    SymbolTableEntry *head, *tmp, *tmp2;

    tmp = symbolTable_lookup(symbolTable, scope);
    tmp2 = tmp;
    if (tmp != NULL)
    {
        while (tmp2->next_same_scope != NULL)
            tmp2 = tmp2->next_same_scope;

        tmp2->next_same_scope = bucket;
    }
    else
    {
        bucket->isScopeListHead = 1;
    }

    if (symbolTable == NULL)
    {
        return 0;
    }
    if (bucket == NULL)
    {
        return 0;
    }
    if (bucket->type == USERFUNC || bucket->type == LIBFUNC)
    {
        index = SymTable_hash(bucket->value.funcVal->name);
    }
    else
    {
        index = SymTable_hash(bucket->value.varVal->name);
    }
    head = symbolTable->symboltable[index];
    if (head == NULL)
    {
        symbolTable->symboltable[index] = bucket;
    }
    else
    {
        tmp = head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = bucket;
    }

    return 1;
}

void print_var(Variable *var)
{
    fprintf(stdout, " line : %d", var->line);
    fprintf(stdout, " name :%s", var->name);
    fprintf(stdout, " scope %d", var->scope);
}
void print_func(Function *func)
{
    fprintf(stdout, " line : %d", func->line);
    fprintf(stdout, " name :%s", func->name);
    fprintf(stdout, " scope %d", func->scope);
}
void symbolTable_print(SymbolTable *symbolTable)
{
    unsigned int i = 0;
    SymbolTableEntry *head, *tmp;
    for (i = 0; i < SIZE; i++)
    {
        fprintf(stdout, "index : %d\n", i);
        tmp = symbolTable->symboltable[i];
        while (tmp != NULL)
        {
            fprintf(stdout, "status : %d", tmp->isActive);
            fprintf(stdout, " type : %d", tmp->type);
            (tmp->value.funcVal == NULL) ? print_var(tmp->value.varVal) : print_func(tmp->value.funcVal);
            fprintf(stdout, " --> ");

            tmp = tmp->next;
        }
        fprintf(stdout, "\n");
    }
}
void symbolTable_print_scope_list(SymbolTable *symbolTable, unsigned int scope)
{
    unsigned int i = 0;
    SymbolTableEntry *head, *tmp;
    head = symbolTable_lookup_head(symbolTable, scope);
    tmp = head;
    fprintf(stdout, "scope : %d", scope);
    while (tmp != NULL)
    {
        (tmp->value.funcVal == NULL) ? fprintf(stdout, " %s ", tmp->value.varVal->name) : fprintf(stdout, " %s ", tmp->value.funcVal->name);
        fprintf(stdout, "-->");
        tmp = tmp->next_same_scope;
    }
    fprintf(stdout, "\n");
}

short symbolTable_hide(SymbolTable *symbolTable, unsigned int scope)
{
    unsigned int i = 0;
    SymbolTableEntry *head, *tmp;
    if(symbolTable==NULL) return 0;
    head = symbolTable_lookup_head(symbolTable, scope);
    tmp = head;
    while (tmp != NULL)
    {
        tmp->isActive = 0;
        tmp = tmp->next_same_scope;
    }
    return 1;
    
}
SymbolTableEntry *symbolTable_lookup_head(SymbolTable *symbolTable, unsigned int scope)
{
    unsigned int i = 0;
    SymbolTableEntry *head, *tmp;
    if (symbolTable == NULL)
        return NULL;
    for (i = 0; i < SIZE; i++)
    {
        tmp = symbolTable->symboltable[i];
        while (tmp != NULL)
        {
            if (tmp->value.funcVal == NULL)
            {
                if (tmp->value.varVal->scope == scope && tmp->isScopeListHead == 1)
                {
                    return tmp;
                }
            }
            else
            {
                if (tmp->value.funcVal->scope == scope && tmp->isScopeListHead == 1)
                {
                    return tmp;
                }
            }
            tmp = tmp->next;
        }
    }
    return NULL;
}
SymbolTableEntry *symbolTable_lookup(SymbolTable *symbolTable, unsigned int scope)
{
    unsigned int i = 0;
    SymbolTableEntry *head, *tmp;
    if (symbolTable == NULL)
        return NULL;
    for (i = 0; i < SIZE; i++)
    {
        tmp = symbolTable->symboltable[i];
        while (tmp != NULL)
        {
            if (tmp->value.funcVal == NULL)
            {
                if (tmp->value.varVal->scope == scope)
                {
                    return tmp;
                }
            }
            else
            {
                if (tmp->value.funcVal->scope == scope)
                {
                    return tmp;
                }
            }
            tmp = tmp->next;
        }
    }
    return NULL;
}
SymbolTableEntry *symbolTable_lookup_scopeless(SymbolTable *symbolTable)
{
}
