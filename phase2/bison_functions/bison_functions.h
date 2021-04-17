#include"../Symboltable_functions/symbolTable.h"
#include"../general_functions/lib.h"

void process_id(SymbolTable *symbolTable,  char *id_name , unsigned int iam_in_function , function_stack **functions_stack,SymbolTableEntry * *lvalue );
void process_local_id(SymbolTable *symbolTable,  char *id_name,unsigned int iam_in_function, SymbolTableEntry ** lvalue);
void process_double_colon_id(SymbolTable *symbolTable , char * name , int yylineno , SymbolTableEntry **  );
void process_function_id(SymbolTable *symbolTable,  char * func_name,unsigned int * iam_in_function, function_stack **functions_stack);
void process_anonymous_function(SymbolTable *symbolTable, function_stack **functions_stack);
void process_function_arguments(SymbolTable *symbolTable,  char *arg_name);
void   print_error( const char * name , int line , char *  msg );
void   print_to_stream(char *msg );
void process_assign(SymbolTable *symbolTable, unsigned int iam_in_function, function_stack **functions_stack, SymbolTableEntry **lvalue);
void process_primary(SymbolTable *symbolTable, unsigned int iam_in_function, function_stack **functions_stack, SymbolTableEntry **lvalue);
void process_plus_plus(SymbolTable *symbolTable, unsigned int iam_in_function, function_stack **functions_stack, SymbolTableEntry **lvalue);
void process_minus_minus(SymbolTable *symbolTable, unsigned int iam_in_function, function_stack **functions_stack, SymbolTableEntry **lvalue);
short check_access(SymbolTable *symbolTable, unsigned int iam_in_function, function_stack **functions_stack, SymbolTableEntry **lvalue);
void process_callsuffix(SymbolTable *symbolTable,  unsigned int iam_in_function, function_stack **functions_stack, SymbolTableEntry **lvalue);
