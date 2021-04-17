#include "../Symboltable_functions/symbolTable.h"
#include "../general_functions/lib.h"

void process_id(SymbolTable *symbolTable,char *id_name ,  SymbolTableEntry **lvalue);
void process_local_id(SymbolTable *symbolTable, char *id_name, SymbolTableEntry **lvalue);
void process_double_colon_id(SymbolTable *symbolTable, char *name, SymbolTableEntry **);
void process_function_id(SymbolTable *symbolTable, char *func_name);
void process_anonymous_function(SymbolTable *symbolTable);
void process_function_arguments(SymbolTable *symbolTable, char *arg_name);
void print_error(const char *name, int line, char *msg);
void print_to_stream(char *msg);
void process_assign(SymbolTable *symbolTable, SymbolTableEntry **lvalue);
void process_primary(SymbolTable *symbolTable, SymbolTableEntry **lvalue);
void process_plus_plus(SymbolTable *symbolTable, SymbolTableEntry **lvalue);
void process_minus_minus(SymbolTable *symbolTable, SymbolTableEntry **lvalue);
short check_access(SymbolTable *symbolTable, SymbolTableEntry **lvalue);
void process_callsuffix(SymbolTable *symbolTable, SymbolTableEntry **lvalue);
