#include"../Symboltable_functions/symbolTable.h"
#include"../general_functions/lib.h"

void process_id(SymbolTable *symbolTable, unsigned int scope, int yylineno, char *id_name , unsigned int iam_in_function , function_stack **functions_stack,SymbolTableEntry * *lvalue );
void process_local_id(SymbolTable *symbolTable, unsigned int scope, int yylineno, char *id_name,unsigned int iam_in_function, SymbolTableEntry ** lvalue);
void process_double_colon_id(SymbolTable *symbolTable , char * name , int yylineno );
void process_function_id(SymbolTable *symbolTable, unsigned int scope, int yylineno, char * func_name,unsigned int iam_in_function, function_stack **functions_stack);
void process_anonymous_function(SymbolTable *symbolTable, unsigned int scope, int yylineno,function_stack **functions_stack);
void process_function_arguments(SymbolTable *symbolTable, unsigned int scope, int yylineno, char *arg_name);
void   print_error( char * name , int line , char *  msg );
void   print_to_stream(char *msg );