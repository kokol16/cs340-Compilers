#include "bison_functions.h"

#define lvalue_ptr (*lvalue)
void process_local_id(SymbolTable *symbolTable, char *id_name, expr **lvalue)
{

    SymbolTableEntry *bucket;
    Variable *var;
    var = create_var(id_name, scope, yylineno);
    if (scope != 0)
        bucket = create_bucket_var(1, var, LOCAL);
    else
        bucket = create_bucket_var(1, var, GLOBAL);
    if (symbolTable_lookup_exists_exact_scope(symbolTable, scope, (const char *)id_name) == 0)
    {
        if (is_library_func(symbolTable, (const char *)id_name))
        {
            print_error(NULL, yylineno, "ERROR : conflict with library function");
            //*lvalue = NULL;
        }
        else
        {
            symbolTable_insert(symbolTable, bucket);
            bucket->space = curr_scope_space();
            bucket->offset = curr_scope_offset();
            in_current_scope_offset();
        }
    }
    else
    {
        bucket = find_bucket_by_scope_and_name(symbolTable, id_name, scope);
        bucket->space = curr_scope_space();
        bucket->offset = curr_scope_offset();
        in_current_scope_offset();
    }
    lvalue_ptr = lvalue_expr(bucket);
}
void process_id(SymbolTable *symbolTable, char *id_name, expr **lvalue)
{
    SymbolTableEntry *bucket;
    Variable *var;

    bucket = symbolTable_lookup_scopeless(symbolTable, id_name);
    if (bucket == NULL)
    {

        symbolTable_insert(symbolTable, bucket);
        bucket->space = curr_scope_space();
        bucket->offset = curr_scope_offset();
        in_current_scope_offset();
    }
    lvalue_ptr = lvalue_expr(bucket);
}

void process_assign(SymbolTable *symbolTable, expr **lvalue)
{
    if (lvalue == NULL)
    {
        return;
    }
    if (is_function(lvalue_ptr->sym))
    {

        print_error(NULL, yylineno, "ERROR : assign to function");

        *lvalue = NULL;
        return;
    }
    check_access(symbolTable, &lvalue_ptr->sym);
}

void process_callsuffix(SymbolTable *symbolTable, expr **lvalue)
{
    check_access(symbolTable, &lvalue_ptr->sym);
}
void process_primary(SymbolTable *symbolTable, expr **lvalue)
{

    check_access(symbolTable, &lvalue_ptr->sym);
}

void process_plus_plus(SymbolTable *symbolTable, expr **lvalue)
{
    if (is_function(lvalue_ptr->sym))
    {

        print_error(NULL, yylineno, "ERROR : ++ to function");

        *lvalue = NULL;
        return;
    }
    check_access(symbolTable, &lvalue_ptr->sym);
}
void process_minus_minus(SymbolTable *symbolTable, expr **lvalue)
{
    if (is_function(lvalue_ptr->sym))
    {

        print_error(NULL, yylineno, "ERROR : -- to function");

        *lvalue = NULL;
        return;
    }
    check_access(symbolTable, &lvalue_ptr->sym);
}

short check_access(SymbolTable *symbolTable, SymbolTableEntry **lvalue)
{
    if (*lvalue == NULL || lvalue == NULL)
    {
        return 0;
    }
    const char *id_name;
    id_name = ((*lvalue)->value.varVal != NULL) ? (*lvalue)->value.varVal->name : (*lvalue)->value.funcVal->name;
    if ((*lvalue)->value.varVal != NULL && (*lvalue)->value.varVal->scope == scope || (*lvalue)->value.varVal != NULL && (*lvalue)->value.varVal->scope == scope)
    {
        //all good
    }
    else if (!is_function(*lvalue) && (*lvalue)->value.varVal->scope == 0)
    {
        //tipota
    }
    else if (iam_in_function <= 0) //i have access
    {
    }
    else
    {
        SymbolTableEntry *func_entry = top(functions_stack);
        if (is_function(*lvalue) || (*lvalue)->value.varVal->scope == 0 ||
            func_entry != NULL && (*lvalue)->value.varVal->scope > func_entry->value.funcVal->scope)
        {
        }
        else
        {

            print_error(id_name, yylineno, "ERROR : no access to variable");
            *lvalue = NULL;
            return 0;
        }
    }
    return 1;
}

void reset_formal_arg_offset()
{
    formal_arg_offset = 0;
}
expr *process_funcdef(expr *func_prefix, unsigned total_locals)
{
    exit_scope_space();
    printf("scope space : %u\n", curr_scope_space());
    printf("total locals  : %u\n", total_locals);
    func_prefix->sym->value.funcVal->total_locals = total_locals;
    unsigned offset = pop_scope_offset_stack();
    //printf("lala2\n");
    restore_curr_scope_offset(offset);
    emit(funcend, func_prefix, NULL, NULL, curr_quad, yylineno);
    return func_prefix;
}

expr *process_function_prefix(SymbolTable *symbolTable, char *func_name)
{
    expr *_expr;
    Function *func;
    SymbolTableEntry *bucket;

    func = create_func(func_name, scope, yylineno);
    bucket = create_bucket_func(1, func, USERFUNC);
    if (bucket->value.funcVal != NULL)
        bucket->value.funcVal->iadress = curr_quad;
    _expr = lvalue_expr(bucket);
    emit(funcstart, _expr, NULL, NULL, curr_quad, yylineno);
    push_scope_offset_stack(curr_scope_offset());
    enter_scope_space();
    reset_formal_arg_offset();
    short status = symbolTable_lookup_exists_exact_scope(symbolTable, scope, func_name);

    if (is_library_func(symbolTable, func_name))
    {
        print_error(func_name, yylineno, "ERROR : function name shadows libfunc");
        //(*iam_in_function)--;
    }
    else if (status == ERROR_FUNC)
    {
        print_error(func_name, yylineno, "ERROR : function already exists");
        //(*iam_in_function)--;
    }
    else if (status == ERROR_VAR)
    {
        print_error(func_name, yylineno, "ERROR : use variable as function"); //kalo?
        //(*iam_in_function)--;

        // fprintf(stderr, "Error in line %d: %s is variable\n", yylineno, func_name);
    }
    else
    {
        //fprintf(stderr,"staus : %d\n",status);
        symbolTable_insert(symbolTable, bucket);

        push(functions_stack, bucket);
    }

    return _expr;
}

void print_to_stream(char *msg)
{

    fprintf(output_file, "%s\n", msg);
}
void print_error(const char *name, int line, char *msg)
{
    print_Red();
    fprintf(stderr, "%s", msg);
    fprintf(stderr, " in line : %d", line);
    if (name != NULL)
        fprintf(stderr, " ID : %s\n", name);
    else
        fprintf(stderr, "\n");

    reset_Red();
}
void process_anonymous_function(SymbolTable *symbolTable)
{
    Function *func;
    SymbolTableEntry *bucket;
    func = create_func(NULL, scope, yylineno);
    bucket = create_bucket_func(1, func, USERFUNC);
    symbolTable_insert(symbolTable, bucket);
    push(functions_stack, bucket);
}
void process_function_arguments(SymbolTable *symbolTable, char *arg_name)
{
    SymbolTableEntry *bucket;
    Variable *var;
    var = create_var(arg_name, scope, yylineno);
    bucket = create_bucket_var(1, var, FORMAL);
    if (is_library_func(symbolTable, arg_name))
    {
        print_error(NULL, yylineno, "ERROR : formal argument shadows libfunc");
    }
    else if (symbolTable_lookup_exists_exact_scope(symbolTable, scope, arg_name) != 0)
    {
        print_error(NULL, yylineno, "ERROR : formal argument redeclaration");
    }
    else
    {
        symbolTable_insert(symbolTable, bucket);
        create_argument(symbolTable, arg_name, scope);
    }
}
void process_double_colon_id(SymbolTable *symbolTable, char *name, expr **lvalue)
{
    if (symbolTable_lookup_exists_exact_scope(symbolTable, 0, name) == 0)
    {
        print_error(name, yylineno, "ERROR : global variable doesn't exist");
    }
    lvalue_ptr->sym = find_bucket_by_scope_and_name(symbolTable, name, 0);
}
