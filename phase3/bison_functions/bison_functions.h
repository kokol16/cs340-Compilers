

#include "../quads/quads.h"
#include "../general_functions/lib.h"

void process_id(SymbolTable *symbolTable, char *id_name, expr **lvalue);
void process_local_id(SymbolTable *symbolTable, char *id_name, expr **lvalue);
void process_double_colon_id(SymbolTable *symbolTable, char *name, expr **);
expr *process_function_prefix(SymbolTable *symbolTable, char *func_name);
void process_anonymous_function(SymbolTable *symbolTable);
void process_function_arguments(SymbolTable *symbolTable, char *arg_name);
void print_error(const char *name, int line, char *msg);
void print_to_stream(char *msg);
void process_assign(SymbolTable *symbolTable, expr **lvalue , expr ** assign_expr , expr * _expr);
void process_primary(SymbolTable *symbolTable, expr **lvalue);
void process_plus_plus(SymbolTable *symbolTable, expr **lvalue);
void process_minus_minus(SymbolTable *symbolTable, expr **lvalue);
short check_access(SymbolTable *symbolTable, SymbolTableEntry **lvalue);
void process_callsuffix(SymbolTable *symbolTable, expr **lvalue);
char *new_func_name();
expr *process_funcdef(expr *func_prefix, unsigned total_args);
expr * member_item(expr *  lvalue , char * name );