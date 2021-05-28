

#include "../quads/quads.h"
#include "../general_functions/lib.h"



extern  int Came_From_OP;

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

expr *process_elist_element(expr **head, expr *new_elist);
expr *process_elists_element(expr **head, expr *new_elist);
expr *make_call(expr *lvalue, expr *reverse_list, SymbolTable *symboltable);
expr *process_array_elist(expr *head, SymbolTable * symboltable);
expr *process_table_indexed(indexed *objects_list,SymbolTable *symboltable);
expr *process_term_lvalue_plus_plus(expr *lvalue, expr **term, SymbolTable *symboltable);
expr *process_term_plus_plus_lvalue(expr *lvalue, expr **term, SymbolTable *symboltable);
expr *process_term_lvalue_minus_minus(expr *lvalue, expr **term, SymbolTable *symboltable);
expr *process_term_minus_minus_lvalue(expr *lvalue, expr **term, SymbolTable *symboltable);
expr *process_arithm_operation(iopcode opcode, expr *expr1, expr *expr2, SymbolTable *symboltable);
int do_the_arith_operations_double(iopcode opcode, expr *_expr, expr *expr1, expr *expr2);
int do_the_arith_operations_int(iopcode opcode, expr *_expr, expr *expr1, expr *expr2);

int  check_if_bool_emit(expr ** left);


void  create_emits_after_bool_op(expr **$3, SymbolTable * symbolTable);

int are_same_type(expr *left, expr *right);