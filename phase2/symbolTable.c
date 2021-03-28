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
    load_lib_functions(symtable);

    return symtable;
}
static short load_lib_functions(SymbolTable *symtable)
{
    /*
    Function *func_print = create_func("print", 0, 0);
    Function *func_input = create_func("input", 0, 0);
    Function *func_objectmemberkeys = create_func("objectmemberkeys", 0, 0);
    Function *func_objecttotalmembers = create_func("objecttotalmembers", 0, 0);
    Function *func_objectcopy = create_func("objectcopy", 0, 0);
    Function *func_totalarguments = create_func("totalarguments", 0, 0);
    Function *func_argument = create_func("argument", 0, 0);
    Function *func_typeof = create_func(" typeof", 0, 0);
    Function *func_strtonum = create_func("strtonum", 0, 0);
    Function *func_sqrt = create_func("sqrt", 0, 0);
    Function *func_cos = create_func("cos", 0, 0);
    Function *func_sin = create_func("sin", 0, 0);

    SymbolTableEntry *print_bucket = create_bucket_func(1, func_print, LIBFUNC);
    SymbolTableEntry *input_bucket = create_bucket_func(1, func_input, LIBFUNC);
    SymbolTableEntry *objectmemberkeys_bucket = create_bucket_func(1, func_objectmemberkeys, LIBFUNC);
    SymbolTableEntry *objecttotalmembers_bucket = create_bucket_func(1, func_objecttotalmembers, LIBFUNC);
    SymbolTableEntry *objectcopy_bucket = create_bucket_func(1, func_objectcopy, LIBFUNC);
    SymbolTableEntry *totalarguments_bucket = create_bucket_func(1, func_totalarguments, LIBFUNC);
    SymbolTableEntry *argument_bucket = create_bucket_func(1, func_argument, LIBFUNC);
    SymbolTableEntry *typeof_bucket = create_bucket_func(1, func_typeof, LIBFUNC);
    SymbolTableEntry *strtonum_bucket = create_bucket_func(1, func_strtonum, LIBFUNC);
    SymbolTableEntry *sqrt_bucket = create_bucket_func(1, func_sqrt, LIBFUNC);
    SymbolTableEntry *cos_bucket = create_bucket_func(1, func_cos, LIBFUNC);
    SymbolTableEntry *sin_bucket = create_bucket_func(1, func_sin, LIBFUNC);

    symbolTable_insert(symtable, print_bucket);
    symbolTable_insert(symtable, input_bucket);
    symbolTable_insert(symtable, objectmemberkeys_bucket);
    symbolTable_insert(symtable, objecttotalmembers_bucket);
    symbolTable_insert(symtable, objectcopy_bucket);
    symbolTable_insert(symtable, totalarguments_bucket);
    symbolTable_insert(symtable, argument_bucket);
    symbolTable_insert(symtable, typeof_bucket);
    symbolTable_insert(symtable, strtonum_bucket);
    symbolTable_insert(symtable, sqrt_bucket);
    symbolTable_insert(symtable, cos_bucket);
    symbolTable_insert(symtable, sin_bucket);
    */
    return 1;
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
    var->next_arg = NULL;
    return var;
}
Function *create_func(const char *name, unsigned int scope, unsigned int line, Variable **arguments, unsigned int arg_size)
{
    static unsigned int counter = 1;
    unsigned int index = 0;
    int counter_str_size;
    Variable *tmp;
    Function *func;
    func = malloc(sizeof(Function));
    if (func == NULL)
    {
        fprintf(stderr, "error allocating func\n");
        return NULL;
    }
    if (name == NULL)
    {
        char *anon_name;
        counter_str_size= snprintf(NULL, 0, "%u", counter);
        anon_name = malloc(sizeof(char) * (counter_str_size+6));
        memcpy(anon_name, "$func", 5);
        snprintf(anon_name+5 , counter_str_size+1, "%u", counter);
        func->name =anon_name;
        counter ++;
    }
    else
    {
        int length = strlen(name) + 1;
        func->name = malloc(sizeof(char) * length);
        memcpy((void *)func->name, name, length * sizeof(char));
    }

    func->scope = scope;
    func->line = line;
    func->arg_head = NULL;
    //Think abou doing memcpy instead of = and free the arguments array
    if (arguments != NULL)
    {
        while (index < arg_size)
        {
            if (func->arg_head == NULL)
            {
                func->arg_head = malloc(sizeof(Variable));
                memcpy(func->arg_head, arguments[index], sizeof(Variable));
            }
            else
            {
                tmp = func->arg_head;
                while (tmp->next_arg != NULL)
                {
                    tmp = tmp->next_arg;
                }
                tmp->next_arg = malloc(sizeof(Variable));
                memcpy(tmp->next_arg, arguments[index], sizeof(Variable));
            }

            index++;
        }
    }


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

short symbolTable_insert(SymbolTable *symbolTable, SymbolTableEntry *bucket)
{

    unsigned int index = 0;
    SymbolTableEntry *head, *tmp, *tmp2;
    unsigned int scope = (bucket->value.funcVal == NULL) ? bucket->value.varVal->scope : bucket->value.funcVal->scope;
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
       // printf("name , scope  %s %u \n",bucket->value.funcVal->name,bucket->value.funcVal->scope);

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
        (tmp->value.funcVal == NULL) ? fprintf(stdout, " %s ", tmp->value.varVal->name) : fprintf(stdout, " %s() ", tmp->value.funcVal->name);
        fprintf(stdout, "-->");
        tmp = tmp->next_same_scope;
    }
    fprintf(stdout, "\n");
}

short symbolTable_hide(SymbolTable *symbolTable, unsigned int scope)
{
    unsigned int i = 0;
    SymbolTableEntry *head, *tmp;
    if (symbolTable == NULL)
        return 0;
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

void print_args(Function *func)
{
    Variable *head;
    unsigned int argument_number = 0;
    head = func->arg_head;
    while (head != NULL)
    {
        fprintf(stdout, "argument %u : %s ", argument_number, head->name);
        argument_number++;
        head = head->next_arg;
    }
    fprintf(stdout, "\n");
}

//static short  create_function_arguments_list(Function * func , )
Variable **sanitize_arguments(char *arguments, unsigned int *arg_size, unsigned int scope, unsigned int line)
{
    Variable **arguments_array = NULL;
    char delim[] = ",() {}";
    char *ptr, *tmp_args;
    unsigned int index = 0, size = 0, arg_index = 0, counter = 0;
    tmp_args = malloc(sizeof(char) * (strlen(arguments) + 1));
    memcpy(tmp_args, arguments, strlen(arguments) + 1);

    ptr = strtok(arguments, delim);
    while (ptr != NULL)
    {
        size++;
        ptr = strtok(NULL, delim);
    }
    if (size == 0)
    {
        return NULL;
    } //no arguments found
    arguments_array = malloc(sizeof(Variable *));
    while (counter < size)
    {
        arguments_array[counter] = malloc(sizeof(Variable));
        counter++;
    }
    *arg_size = size;
    ptr = strtok(tmp_args, delim);
    while (ptr != NULL)
    {
        arguments_array[arg_index] = create_var(ptr, scope, line);
        //printf("'%s'\n", arguments_array[arg_index]->name);
        arg_index++;

        ptr = strtok(NULL, delim);
    }
    //printf("size : %u \n", *arg_size);

    return arguments_array;
}