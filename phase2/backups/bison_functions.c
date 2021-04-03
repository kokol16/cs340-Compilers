#include "bison_functions.h"
void process_id(SymbolTable *symbolTable, unsigned int scope, int yylineno, char *id_name,
                unsigned int iam_in_function, function_stack **functions_stack, SymbolTableEntry *lvalue)
{

    SymbolTableEntry *bucket = symbolTable_lookup_scopeless(symbolTable, id_name);
    if (bucket == NULL)
    {

        // printf("do insert in line %d\n",yylineno);
        Variable *var;

        var = create_var(id_name, scope, yylineno);
        if (scope != 0)
            bucket = create_bucket_var(1, var, LOCAL);
        else
            bucket = create_bucket_var(1, var, GLOBAL);
        symbolTable_insert(symbolTable, bucket);
    }
    if (is_function(bucket))
    {
        //tipota
        lvalue = bucket;
    }
    if (!is_function(bucket) && bucket->value.varVal->scope == 0)
    {
        lvalue = bucket;

        //tipota
    }
    if (iam_in_function == 0) //i have access
    {
        lvalue = bucket;
    }
    else
    {
        print_stack(*functions_stack);
        SymbolTableEntry *func_entry = top(*functions_stack);
       
        printf("haha\n");

        //fprintf(stderr,"scope func :%d\n",func_entry->value.funcVal->scope);
        //fprintf(stderr,"scope var :%d\n",bucket->value.varVal->scope);

        if (is_function(bucket) || bucket->value.varVal->scope == 0 ||
            func_entry!=NULL &&  bucket->value.varVal->scope > func_entry->value.funcVal->scope)
        {
            lvalue = bucket;
        }
        else
        {
            print_Red();
            fprintf(stderr, "Error in line %d: no access to variable  %s \n", yylineno, id_name);
            reset_Red();
        }
    }
    printf("haha\n");

}
void process_function_id(SymbolTable *symbolTable, unsigned int scope, int yylineno, char *func_name,
                         unsigned int iam_in_function, function_stack **functions_stack)
{
    Function *func;
    SymbolTableEntry *bucket;
    func = create_func(func_name, scope, yylineno);
    bucket = create_bucket_func(1, func, USERFUNC);
    short status = symbolTable_lookup_exists_exact_scope(symbolTable, scope, func_name);
    if (is_library_func(symbolTable, func_name))
    {
        print_error(func_name,yylineno, "ERROR : function name shadows libfunc");
        
    }
    else if (status == ERROR_FUNC)
    {
        print_error(func_name,yylineno, "ERROR : function already exists");

    }
    else if (status == ERROR_VAR)
    {
        print_Red();
        fprintf(stderr, "Error in line %d: %s is variable\n", yylineno, func_name);
        reset_Red();
    }
    else
    {
        //fprintf(stderr,"staus : %d\n",status);
        symbolTable_insert(symbolTable, bucket);
        push(functions_stack, bucket);
    }
}

void   print_to_stream(char *msg )
{
  FILE *out;
  if (output_file != NULL)
  {
    out = output_file;
  }
  else
  {
    out = stdout;
  }
  fprintf(out,"%s\n",msg);
}
void   print_error( char * name , int line , char *  msg )
{
    print_Red();
    fprintf(stderr,"%s",msg);
    fprintf(stderr," in line : %d",line);
    if(name!=NULL)
    fprintf(stderr," ID : %s\n",name);
    else 
    fprintf(stderr,"\n");

    reset_Red();
}
void process_anonymous_function(SymbolTable *symbolTable, unsigned int scope, int yylineno, function_stack **functions_stack)
{
    Function *func;
    SymbolTableEntry *bucket;
    func = create_func(NULL, scope, yylineno);
    bucket = create_bucket_func(1, func, USERFUNC);
    symbolTable_insert(symbolTable, bucket);
    push(functions_stack, bucket);

}
void process_function_arguments(SymbolTable *symbolTable, unsigned int scope, int yylineno, char *arg_name)
{
    SymbolTableEntry *bucket;
    Variable *var;
    var = create_var(arg_name, scope, yylineno);
    bucket = create_bucket_var(1, var, FORMAL);
    if (is_library_func(symbolTable, arg_name))
    {
        print_Red();

        fprintf(stderr, "Error in line %d:formal argument shadows libfunc\n", yylineno);
        reset_Red();
    }
    else if (symbolTable_lookup_exists_exact_scope(symbolTable, scope, arg_name) != 0)
    {
        print_Red();

        fprintf(stderr, "Error in line %d:formal argument redeclaration\n", yylineno);
        reset_Red();
    }
    else
    {
        symbolTable_insert(symbolTable, bucket);
        create_argument(symbolTable,arg_name, scope);
    }
}
void process_double_colon_id(SymbolTable *symbolTable, char *name, int yylineno)
{
    if (symbolTable_lookup_exists_exact_scope(symbolTable, 0, name) == 0)
    {
        print_Red();
        fprintf(stderr, "Error in line %d:global variable : %s doesn't exist\n", yylineno, name);
        reset_Red();
    }
}
void process_local_id(SymbolTable *symbolTable, unsigned int scope, int yylineno, char *id_name, unsigned int iam_in_function,  SymbolTableEntry *lvalue)
{

    SymbolTableEntry *bucket;
    Variable *var;
    //printf("%s\n",$2);

    var = create_var(id_name, scope, yylineno);
    if (scope != 0)
        bucket = create_bucket_var(1, var, LOCAL);
    else
        bucket = create_bucket_var(1, var, GLOBAL);
    if (symbolTable_lookup_exists_exact_scope(symbolTable, scope, (const char *)id_name) == 0)
    {
        if (is_library_func(symbolTable, (const char *)id_name))
        {
            print_Red();
            fprintf(stderr, "Error in line %d: conflict with library function\n", yylineno);
            reset_Red();
        }
        else
        {
            //fprintf(stderr,"eisai otti nane  %s  line %d\n", bucket->value.varVal->name , yylineno);
            symbolTable_insert(symbolTable, bucket);

            // printf("%d\n",symbolTable_insert(symbolTable, bucket));
            lvalue = bucket;
        }
    }
    else
    {
        lvalue = symbolTable_lookup_scope(symbolTable, scope); //iparxon
    }
}