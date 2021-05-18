#include "symbolTable.h"
#include "../general_functions/lib.h"
#define DEBUG_OFFSET 0
unsigned int SIZE = 10;
int yylineno;
short is_local_id = 0;
unsigned int scope = 0;
unsigned int need_check = 0;
unsigned int iam_in_function = 0;
unsigned int iam_in_loop = 0;
func_loop_stack *root_func_loop_stack = NULL;
function_stack *functions_stack = NULL;
scope_offset_stack *scope_offset_stack_root = NULL;

unsigned program_var_offset = 0;
unsigned function_local_offset = 0;
unsigned formal_arg_offset = 0;
unsigned scope_space_counter = 1;

void restore_curr_scope_offset(unsigned n)
{
    switch (curr_scope_space())
    {
    case programvar:
        program_var_offset = n;
        break;
    case functionlocal:
        function_local_offset = n;
        break;
    case formalarg:
        formal_arg_offset = n;
        break;
    default:
        assert(0);
    }
}

void reset_function_locals_offset()
{
    function_local_offset = 0;
}
unsigned curr_scope_offset()
{
    switch (curr_scope_space())
    {
    case programvar:
        return program_var_offset;
    case functionlocal:
        return function_local_offset;
    case formalarg:
        return formal_arg_offset;
    default:
        assert(0);
    }
}
void enter_scope_space()
{
    ++scope_space_counter;
}
void exit_scope_space()
{
    assert(scope_space_counter > 1);
    --scope_space_counter;
}

scopespace_t curr_scope_space()
{
    if (scope_space_counter == 1)
        return programvar;
    else if (scope_space_counter % 2 == 0)
        return formalarg;
    else
        return functionlocal;
}

void in_current_scope_offset(void)
{
    switch (curr_scope_space())
    {
    case programvar:
        ++program_var_offset;
        break;
    case functionlocal:
        ++function_local_offset;
        break;
    case formalarg:
        ++formal_arg_offset;
        break;
    default:
        assert(0);
    }
}
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
    Function *func_print = create_func("print", 0, 0);
    Function *func_input = create_func("input", 0, 0);
    Function *func_objectmemberkeys = create_func("objectmemberkeys", 0, 0);
    Function *func_objecttotalmembers = create_func("objecttotalmembers", 0, 0);
    Function *func_objectcopy = create_func("objectcopy", 0, 0);
    Function *func_totalarguments = create_func("totalarguments", 0, 0);
    Function *func_argument = create_func("argument", 0, 0);
    Function *func_typeof = create_func("typeof", 0, 0);
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

    return 1;
}

static unsigned int SymTable_hash(const char *pcKey)
{
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
char *new_func_name()
{
    static unsigned int counter = 1;
    int counter_str_size;
    char *anon_name;
    counter_str_size = snprintf(NULL, 0, "%u", counter);
    anon_name = malloc(sizeof(char) * (counter_str_size + 6));
    memcpy(anon_name, "$func", 5);
    snprintf(anon_name + 5, counter_str_size + 1, "%u", counter);
    counter++;
    return anon_name;
}
Function *create_func(const char *name, unsigned int scope, unsigned int line)
{
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
        fprintf(stderr, "error null function name\n");
        return NULL;
    }
    else
    {
        int length = strlen(name) + 1;
        func->name = malloc(sizeof(char) * length);
        memcpy((void *)func->name, name, length * sizeof(char));
    }
    func->scope = scope;
    func->line = line;
    func->head_arg = NULL;
    return func;
}
SymbolTableEntry *create_bucket_var(short isActive, Variable *var, enum SymbolType type)
{
    SymbolTableEntry *bucket = malloc(sizeof(SymbolTableEntry));
    bucket->isActive = 1;
    bucket->next = NULL;
    bucket->next_same_scope = NULL;
    bucket->next_arg = NULL;
    bucket->type = type;
    bucket->value.funcVal = NULL;
    bucket->value.varVal = var;

    bucket->space = curr_scope_space();
    bucket->offset = curr_scope_offset();
    in_current_scope_offset();

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
    bucket->next_arg = NULL;

    bucket->type = type;
    bucket->isScopeListHead = 0;

    bucket->value.varVal = NULL;
    bucket->value.funcVal = func;
    bucket->value.funcVal->head_arg = NULL;

    bucket->space = curr_scope_space();
    bucket->offset = curr_scope_offset();
    in_current_scope_offset();
    return bucket;
}

short symbolTable_insert(SymbolTable *symbolTable, SymbolTableEntry *bucket)
{

    unsigned int index = 0;
    SymbolTableEntry *head, *tmp, *tmp2;

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

char *SymbolType_to_string(enum SymbolType type)
{

    switch (type)
    {
    case GLOBAL:
        return "global variable";
    case LOCAL:
        return "local variable";

    case USERFUNC:
        return "user function";
    case FORMAL:
        return "formal argument";
    case LIBFUNC:
        return "library function";

    default:
        return NULL;
    }
}
void print_var(SymbolTableEntry *var)
{
    if (var == NULL)
        return;

    fprintf(output_file, " \"%s\"", var->value.varVal->name);
    fprintf(output_file, " [%s]", SymbolType_to_string(var->type));

    fprintf(output_file, " (line  %d)", var->value.varVal->line);
    fprintf(output_file, " (scope %d)", var->value.varVal->scope);
    fprintf(output_file, " (active %d)", var->isActive);
    if (DEBUG_OFFSET)
        fprintf(output_file, " (offset %u)", var->offset);
}
void print_func(SymbolTableEntry *func)
{
    if (func == NULL)
        return;

    fprintf(output_file, " \"%s\"", func->value.funcVal->name);
    fprintf(output_file, " [%s]", SymbolType_to_string(func->type));

    fprintf(output_file, " (line %d)", func->value.funcVal->line);
    fprintf(output_file, " (scope %d)", func->value.funcVal->scope);
    fprintf(output_file, " (active %d)", func->isActive);
    if (DEBUG_OFFSET)
        fprintf(output_file, " (offset %u)", func->offset);
}
void symbolTable_print(SymbolTable *symbolTable)
{
    unsigned int i = 0;
    SymbolTableEntry *head, *tmp;
    if (symbolTable == NULL)
        return;
    for (i = 0; i < SIZE; i++)
    {
        tmp = symbolTable->symboltable[i];
        fprintf(output_file, "index : %d\n", i);
        while (tmp != NULL)
        {

            (tmp->value.funcVal == NULL) ? print_var(tmp) : print_func(tmp);
            fprintf(output_file, "\n");

            tmp = tmp->next;
        }
    }
}
int symbolTable_print_scope_list(SymbolTable *symbolTable, unsigned int scope)
{
    unsigned int i = 0;
    SymbolTableEntry *head, *tmp;
    if (symbolTable == NULL)
        return 0;

    head = symbolTable_lookup_head(symbolTable, scope);
    tmp = head;
    if (tmp != NULL)
        fprintf(output_file, "=============== scope #%d=====================\n", scope);
    else
        return 0;

    while (tmp != NULL)
    {
        if (tmp->value.funcVal == NULL)
        {

            print_var(tmp);
        }
        else
        {
            print_func(tmp);
        }

        fprintf(output_file, "\n");

        tmp = tmp->next_same_scope;
    }
    return 1;
}

void symbolTable_print_scopes(SymbolTable *symbolTable, unsigned int scope)
{
    unsigned int tmp_scope = 0;
    unsigned int i = 0;
    SymbolTableEntry *head, *tmp;
    if (symbolTable == NULL)
        return;

    while (tmp_scope < scope)
    {
        if (!symbolTable_print_scope_list(symbolTable, tmp_scope))
            break;
        tmp_scope++;
    }
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
/* na tin allaxw na diatrexei tin lista twn scopes*/
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
SymbolTableEntry *symbolTable_lookup_scopeless_var(SymbolTable *symbolTable, char *name)
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

            if (tmp->isActive && tmp->value.varVal != NULL && strcmp(tmp->value.varVal->name, name) == 0)
            {
                return tmp;
            }
            tmp = tmp->next;
        }
    }
    return NULL;
}

short symbolTable_lookup_exists(SymbolTable *symbolTable, unsigned int scope, const char *name)
{
    unsigned int index;
    SymbolTableEntry *bucket;
    if (symbolTable == NULL)
        return 0;
    index = SymTable_hash(name);
    bucket = symbolTable->symboltable[index];
    while (bucket != NULL)
    {
        if (bucket->isActive)
        {
            if (bucket->value.funcVal != NULL && strcmp(bucket->value.funcVal->name, name) == 0 && bucket->value.funcVal->scope <= scope)
            {

                return ERROR_FUNC;
            }
            else if (bucket->value.varVal != NULL && strcmp(bucket->value.varVal->name, name) == 0 && bucket->value.varVal->scope <= scope)
            {

                return ERROR_VAR;
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
    //index = SymTable_hash(name);
    if (symbolTable == NULL)
        return 0;
    bucket = symbolTable_lookup_head(symbolTable, scope);
    while (bucket != NULL)
    {
        if (bucket->isActive)
        {
            if (bucket->value.funcVal != NULL && strcmp(bucket->value.funcVal->name, name) == 0)
            {

                return ERROR_FUNC;
            }
            else if (bucket->value.varVal != NULL && strcmp(bucket->value.varVal->name, name) == 0)
            {

                return ERROR_VAR;
            }
        }
        bucket = bucket->next_same_scope;
    }

    return 0;
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

short is_library_func(SymbolTable *symTable, const char *name)
{
    SymbolTableEntry *head;
    unsigned int index;
    if (symTable == NULL)
        return 0;
    index = SymTable_hash(name);
    head = symTable->symboltable[index];
    while (head != NULL)
    {
        if (head->type == LIBFUNC && strcmp(name, head->value.funcVal->name) == 0)
        {
            return 1;
        }
        head = head->next;
    }

    return 0;
}
short symbolTable_lookup_function(SymbolTable *symTable, unsigned int scope)
{
    unsigned int i = 0;
    SymbolTableEntry *head, *tmp;
    if (symTable == NULL)
        return 0;

    head = symbolTable_lookup_head(symTable, scope);
    tmp = head;
    while (tmp != NULL)
    {
        if (tmp->type == USERFUNC)
        {
            return 1;
        }
        tmp = tmp->next_same_scope;
    }
    return 0;
}
//static short  create_function_arguments_list(Function * func , )

short create_arguments(SymbolTable *symtable, char *arguments, unsigned int scope)
{
    char delim[] = ",() ";
    unsigned int size = 0;
    SymbolTableEntry *arg = NULL, *func, *tmp;
    char *ptr;
    if (symtable == NULL)
        return 0;
    func = last_func_inserted_in_current_scope(symtable, scope - 1);

    if (func == NULL)
    { /*fprintf(stderr,"didnt find function in scope %u\n",scope-1);*/
        return 0;
    }
    ptr = strtok(arguments, delim);
    tmp = func;
    while (ptr != NULL)
    {

        size++;
        arg = find_bucket_by_scope_and_name(symtable, ptr, scope);
        if (func->value.funcVal->head_arg == NULL)
        {
            func->value.funcVal->head_arg = arg;
            tmp = arg;
        }
        else
        {
            tmp->next_arg = arg;
            tmp = arg;
        }

        ptr = strtok(NULL, delim);
    }
}

short create_argument(SymbolTable *symtable, char *argument, unsigned int scope)
{
    SymbolTableEntry *arg = NULL, *func, *tmp;
    char *ptr;
    if (symtable == NULL)
        return 0;
    func = last_func_inserted_in_current_scope(symtable, scope - 1);
    if (func == NULL)
    {
        return 0;
    }
    arg = find_bucket_by_scope_and_name(symtable, argument, scope);

    tmp = func->value.funcVal->head_arg;
    if (tmp == NULL)
    {
        func->value.funcVal->head_arg = arg;
    }
    else
    {
        while (tmp->next_arg != NULL)
        {
            tmp = tmp->next_arg;
        }
        tmp->next_arg = arg;
    }

    //print_func_args(func);

    return 1;
}

void print_func_args(SymbolTableEntry *fnc)
{
    SymbolTableEntry *head = fnc->value.funcVal->head_arg;
    while (head != NULL)
    {
        fprintf(output_file, "[%s]", head->value.varVal->name);
        head = head->next_arg;
    }
    fprintf(output_file, "\n");
}

SymbolTableEntry *find_bucket_by_scope_and_name(SymbolTable *symtable, char *name, unsigned int scope)
{
    unsigned int index;
    SymbolTableEntry *bucket;

    if (symtable == NULL)
        return NULL;

    bucket = symbolTable_lookup_head(symtable, scope);

    //printf("%s\n", name);
    while (bucket != NULL)
    {
        if (bucket->value.varVal != NULL && strcmp(bucket->value.varVal->name, name) == 0 && bucket->isActive)
        {

            return bucket;
        }
        else if (bucket->value.funcVal != NULL && strcmp(bucket->value.funcVal->name, name) == 0 && bucket->isActive)
        {
            return bucket;
        }
        bucket = bucket->next_same_scope;
    }
    return NULL;
}

SymbolTableEntry *last_func_inserted_in_current_scope(SymbolTable *symtable, unsigned int scope)
{
    unsigned int index;
    SymbolTableEntry *bucket, *last_func = NULL;
    if (symtable == NULL)
        return NULL;

    bucket = symbolTable_lookup_head(symtable, scope);
    while (bucket != NULL)
    {
        if (bucket->value.funcVal != NULL && bucket->isActive)
        {

            last_func = bucket;
        }
        bucket = bucket->next_same_scope;
    }
    return last_func;
}
double find_bucket_scope(SymbolTable *symbolTable, char *name)
{
    SymbolTableEntry *func;
    if (symbolTable == NULL)
        return -1;
    func = symbolTable_lookup_scopeless_var(symbolTable, name);
    if (func != NULL)
    {
        return func->value.varVal->scope;
    }
    return -1;
}

SymbolTableEntry *symbolTable_lookup_scopeless(SymbolTable *symbolTable, const char *name)
{
    unsigned int i = 0, index = 0;
    double prev_scope = -1;
    SymbolTableEntry *head, *tmp = NULL;
    if (symbolTable == NULL || name == NULL)
        return NULL;
    index = SymTable_hash(name);
    head = symbolTable->symboltable[index];
    while (head != NULL)
    {
        if (head->isActive && head->value.funcVal != NULL && strcmp(head->value.funcVal->name, name) == 0 && prev_scope < head->value.funcVal->scope)
        {
            prev_scope = head->value.funcVal->scope;
            tmp = head;
        }
        else if (head->isActive && head->value.varVal != NULL && strcmp(head->value.varVal->name, name) == 0 && prev_scope < head->value.varVal->scope)
        {
            prev_scope = head->value.varVal->scope;
            tmp = head;
        }
        head = head->next;
    }
    return tmp;
}

short is_function(SymbolTableEntry *lvalue)
{
    if (lvalue == NULL)
        return 0;
    if (lvalue->value.funcVal != NULL)
    {
        return 1;
    }
    return 0;
}

short is_argument(SymbolTableEntry *func)
{
}

int push(function_stack *root, SymbolTableEntry *func)
{
    function_stack *stack_entry = malloc(sizeof(function_stack));
    stack_entry->func = func;
    stack_entry->next = NULL;

    if (root == NULL)
    {
        root = stack_entry;
        return 1;
    }

    stack_entry->next = root;
    root = stack_entry;
    return 1;
}

int pop(function_stack *root)
{
    if (root == NULL)
    {
        return 0;
    }
    root = (root)->next;
    return 1;
}

SymbolTableEntry *top(function_stack *root)
{
    if (root != NULL)
    {
        return root->func;
    }
    else
    {
        return NULL;
    }
}

void print_stack(function_stack *root)
{
    function_stack *tmp = root;
    if (root == NULL)
    {
        fprintf(output_file, "wtf\n");
    }

    while (tmp != NULL)
    {
        fprintf(output_file, " %s", tmp->func->value.funcVal->name);
        tmp = tmp->next;
    }
    fprintf(stderr, "\n");
}

int push_func_loop(enum func_loops entry)
{
    func_loop_stack *stack_entry = malloc(sizeof(func_loop_stack));
    stack_entry->func_loop = entry;
    stack_entry->next = NULL;
    if (root_func_loop_stack == NULL)
    {
        root_func_loop_stack = stack_entry;
        return 1;
    }

    stack_entry->next = root_func_loop_stack;
    root_func_loop_stack = stack_entry;
    return 1;
}

int pop_func_loop()
{
    if (root_func_loop_stack == NULL)
    {
        return 0;
    }
    root_func_loop_stack = root_func_loop_stack->next;
    return 1;
}

enum func_loops top_func_loop()
{
    if (root_func_loop_stack != NULL)
    {
        return root_func_loop_stack->func_loop;
    }
    else
    {
        return -1;
    }
}

void print_stack_func_loop()
{
}

unsigned pop_scope_offset_stack()
{
    unsigned offset = 0;
    if (scope_offset_stack_root == NULL)
    {
        return 0;
    }
    offset = scope_offset_stack_root->scope_offset;
    scope_offset_stack_root = scope_offset_stack_root->next;
    return offset;
}

int push_scope_offset_stack(unsigned scope_offset)
{
    scope_offset_stack *stack_entry = malloc(sizeof(scope_offset_stack));
    stack_entry->scope_offset = scope_offset;
    stack_entry->next = NULL;
    if (scope_offset_stack_root == NULL)
    {
        scope_offset_stack_root = stack_entry;
        return 1;
    }

    stack_entry->next = scope_offset_stack_root;
    scope_offset_stack_root = stack_entry;
    return 1;
}

unsigned top_scope_offset_stack()
{
    if (scope_offset_stack_root != NULL)
    {
        return scope_offset_stack_root->scope_offset;
    }
    else
    {
        return -1;
    }
}
