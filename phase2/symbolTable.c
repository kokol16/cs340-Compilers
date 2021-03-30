#include "symbolTable.h"
#include "lib.h"
unsigned int SIZE = 15;
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
    
    unsigned int size;
    Variable **arguments = sanitize_arguments("lala", &size, 0, 0);
    Function *func_print = create_func("print", 0, 0, arguments, size);
    Function *func_input = create_func("input", 0, 0, arguments, size);
    Function *func_objectmemberkeys = create_func("objectmemberkeys", 0, 0, arguments, size);
    Function *func_objecttotalmembers = create_func("objecttotalmembers", 0, 0, arguments, size);
    Function *func_objectcopy = create_func("objectcopy", 0, 0, arguments, size);
    Function *func_totalarguments = create_func("totalarguments", 0, 0, arguments, size);
    Function *func_argument = create_func("argument", 0, 0, arguments, size);
    Function *func_typeof = create_func(" typeof", 0, 0, arguments, size);
    Function *func_strtonum = create_func("strtonum", 0, 0, arguments, size);
    Function *func_sqrt = create_func("sqrt", 0, 0, arguments, size);
    Function *func_cos = create_func("cos", 0, 0, arguments, size);
    Function *func_sin = create_func("sin", 0, 0, arguments, size);

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
        counter_str_size = snprintf(NULL, 0, "%u", counter);
        anon_name = malloc(sizeof(char) * (counter_str_size + 6));
        memcpy(anon_name, "$func", 5);
        snprintf(anon_name + 5, counter_str_size + 1, "%u", counter);
        func->name = anon_name;
        counter++;
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
    bucket->value.funcVal = NULL;
    bucket->value.varVal = var;
    //printf("lala%s\n",bucket->value.funcVal->name);

    bucket->isScopeListHead = 0;

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
    tmp = symbolTable_lookup_scope(symbolTable, scope); //find bucket on same scope
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
SymbolTableEntry *symbolTable_lookup_scope(SymbolTable *symbolTable, unsigned int scope)
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

short symbolTable_lookup_exists(SymbolTable *symbolTable, unsigned int scope, const char *name)
{
    unsigned int index;
    SymbolTableEntry *bucket;
    index = SymTable_hash(name);
    bucket = symbolTable->symboltable[index];
    while (bucket != NULL)
    {
        if (bucket->isActive)
        {
            if (bucket->value.funcVal != NULL && strcmp(bucket->value.funcVal->name, name) == 0 && bucket->value.funcVal->scope <= scope)
            {
                print_Red();

                if (bucket->type == LIBFUNC)
                    fprintf(stderr, "error librady function name exists : %s\n ", name);
                else
                {
                    //fprintf(stderr, "error function  with same  name exists : %s\n", name);
                }
                reset_Red();

                return 1;
            }
            else if (bucket->value.varVal != NULL && strcmp(bucket->value.varVal->name, name) == 0 && bucket->value.varVal->scope <= scope)
            {
                print_Red();

                //fprintf(stderr, "error variable  with same  name exists : %s\n", name);

                reset_Red();
                return 1;
            }
        }
        bucket = bucket->next;
    }

    return 0;
}

short symbolTable_lookup_exists_exact_scope(SymbolTable *symbolTable, unsigned int scope, const char *name)
{
    unsigned int index;
    SymbolTableEntry *bucket;
    index = SymTable_hash(name);
    bucket = symbolTable->symboltable[index];
    while (bucket != NULL)
    {
        if (bucket->isActive)
        {
            if (bucket->value.funcVal != NULL && strcmp(bucket->value.funcVal->name, name) == 0 && bucket->value.funcVal->scope == scope && bucket->isActive)
            {

                return 1;
            }
            else if (bucket->value.varVal != NULL && strcmp(bucket->value.varVal->name, name) == 0 && bucket->value.varVal->scope == scope && bucket->isActive)
            {

                return 1;
            }
        }
        bucket = bucket->next;
    }

    return 0;
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
SymbolTableEntry **create_arguments_buckets(Variable **arguments, unsigned int size)
{
    SymbolTableEntry **arg_buckets;
    unsigned int i = 0;
    arg_buckets = malloc(sizeof(SymbolTableEntry *));

    for (i = 0; i < size; i++)
    {
        arg_buckets[i] = malloc(sizeof(SymbolTableEntry));
        arg_buckets[i] = create_bucket_var(1, arguments[i], FORMAL);
        //printf("%s\n",arg_buckets[i]->value.varVal->name);
    }
    return arg_buckets;
}
short symbolTable_insert_args(SymbolTable *symTable, SymbolTableEntry **arg_buckets, unsigned int size)
{
    unsigned int i = 0;
    if (symTable == NULL || arg_buckets == NULL)
        return 0;
    for (i = 0; i < size; i++)
    {

        symbolTable_insert(symTable, arg_buckets[i]);
    }

    return 1;
}

short is_library_func(SymbolTable *symTable ,const char *name)
{
        unsigned int index =SymTable_hash(name);
        SymbolTableEntry * head =symTable->symboltable[index];
        while(head!=NULL )
        {
            if(head->type==LIBFUNC && strcmp(name,head->value.funcVal->name)==0)
            {
                return 1;   
            }
            head=head->next;
        }


    return 0;
}
short symbolTable_lookup_function(SymbolTable *symTable ,unsigned int scope)
{
    unsigned int i = 0;
    SymbolTableEntry *head, *tmp;
    head = symbolTable_lookup_head(symTable, scope);
    tmp = head;
    while (tmp != NULL)
    {
        fprintf(stdout, "scope : %d name  : %d \n", scope ,tmp->value);
        if(tmp->type==USERFUNC)
        {
            return 1;
        }
        tmp = tmp->next_same_scope;
    }
    return 0;
}
//static short  create_function_arguments_list(Function * func , )

Variable **sanitize_arguments(char *arguments, unsigned int *arg_size, unsigned int scope, unsigned int line)
{
    Variable **arguments_array = NULL;
    char delim[] = ",(";
    char *ptr, *tmp_args;
    unsigned int index = 0, size = 0, arg_index = 0, counter = 0;

    while (arguments[index] != '\0')
    {
        if (arguments[index] == ')')
        {
            arguments[index] = '\0';
            break;
        }
        index++;
    }
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