#include "bison_functions.h"

void process_id(SymbolTable *symbolTable, char *id_name, SymbolTableEntry **lvalue)
{
    SymbolTableEntry *bucket = symbolTable_lookup_scopeless(symbolTable, id_name);
    if (bucket == NULL)
    {

        Variable *var;

        var = create_var(id_name, scope, yylineno);
        if (scope != 0)
            bucket = create_bucket_var(1, var, LOCAL);
        else
            bucket = create_bucket_var(1, var, GLOBAL);
        symbolTable_insert(symbolTable, bucket);
    }    
    *lvalue = bucket;
}

void process_assign(SymbolTable *symbolTable, SymbolTableEntry **lvalue)
{
    if (lvalue == NULL)
    {
        return;
    }
    if (is_function(*lvalue))
    {

        print_error(NULL, yylineno, "ERROR : assign to function");

        *lvalue = NULL;
        return;
    }
    check_access(symbolTable, lvalue);
}

void process_callsuffix(SymbolTable *symbolTable, SymbolTableEntry **lvalue)
{
    check_access(symbolTable,  lvalue);
}
void process_primary(SymbolTable *symbolTable, SymbolTableEntry **lvalue)
{

    check_access(symbolTable,  lvalue);
}

void process_plus_plus(SymbolTable *symbolTable, SymbolTableEntry **lvalue)
{
    if (is_function(*lvalue))
    {

        print_error(NULL, yylineno, "ERROR : ++ to function");

        *lvalue = NULL;
        return;
    }
    check_access(symbolTable, lvalue);
}
void process_minus_minus(SymbolTable *symbolTable, SymbolTableEntry **lvalue)
{
    if (is_function(*lvalue))
    {

        print_error(NULL, yylineno, "ERROR : -- to function");

        *lvalue = NULL;
        return;
    }
    check_access(symbolTable, lvalue);
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

void process_function_id(SymbolTable *symbolTable, char *func_name)
{
    Function *func;
    SymbolTableEntry *bucket;
    func = create_func(func_name, scope, yylineno);
    bucket = create_bucket_func(1, func, USERFUNC);
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
}

void print_to_stream(char *msg)
{

    fprintf(output_file, "%s\n", msg);
}
void print_error(const char *name,int line ,  char *msg  )
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
void process_double_colon_id(SymbolTable *symbolTable, char *name, SymbolTableEntry **lvalue)
{
    if (symbolTable_lookup_exists_exact_scope(symbolTable, 0, name) == 0)
    {
        print_error(name, yylineno, "ERROR : global variable doesn't exist");
    }
    (*lvalue) = find_bucket_by_scope_and_name(symbolTable, name, 0);
}
void process_local_id(SymbolTable *symbolTable, char *id_name, SymbolTableEntry **lvalue)
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
            *lvalue = NULL;
        }
        else
        {
            symbolTable_insert(symbolTable, bucket);

            *lvalue = bucket;
        }
    }
    else
    {

        *lvalue = find_bucket_by_scope_and_name(symbolTable, id_name, scope); //iparxon
        if (lvalue == NULL)
        {
        }
    }
}