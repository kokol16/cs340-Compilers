#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../general_functions/lib.h"
#define HASH_MULTIPLIER 65599
#define ERROR_FUNC 2
#define ERROR_VAR 3

extern int yylineno;
extern short is_local_id;
extern unsigned int scope;
extern unsigned int need_check;
extern unsigned int iam_in_function;
extern unsigned int iam_in_loop;

enum func_loops
{
    func,
    for_loop,
    while_loop
};
typedef struct func_loop_stack
{
    enum func_loops func_loop;
    struct func_loop_stack *next;
} func_loop_stack;

typedef struct Variable
{
    const char *name;
    unsigned int scope;
    unsigned int line;
} Variable;
typedef struct return_list
{
    unsigned address;
    struct return_list *next;
}return_list;
typedef struct Function
{
    const char *name;

    struct SymbolTableEntry *head_arg;
    unsigned iadress;
    unsigned total_locals;
    unsigned int scope;
    unsigned int line;
    return_list * returnList;
    unsigned func_enter_jump;

} Function;

enum SymbolType
{
    GLOBAL,
    LOCAL,
    FORMAL,
    USERFUNC,
    LIBFUNC
};
typedef enum scopespace_t
{
    programvar,
    functionlocal,
    formalarg
} scopespace_t;
typedef struct SymbolTableEntry
{
    short isActive;
    short isScopeListHead;
    struct value
    {
        Variable *varVal;
        Function *funcVal;
    } value;
    unsigned offset;
    scopespace_t space;
    struct SymbolTableEntry *next;
    struct SymbolTableEntry *next_same_scope;
    struct SymbolTableEntry *next_arg;
    unsigned taddress;

    enum SymbolType type;
} SymbolTableEntry;

typedef struct SymbolTable
{
    SymbolTableEntry **symboltable;
} SymbolTable;
typedef struct scope_offset_stack
{
    unsigned scope_offset;
    struct scope_offset_stack *next;
} scope_offset_stack;
typedef struct function_stack
{
    SymbolTableEntry *func;
    struct function_stack *next;
} function_stack;
extern unsigned program_var_offset;
extern unsigned function_local_offset;
extern unsigned formal_arg_offset;
extern unsigned scope_space_counter;

unsigned curr_scope_offset();
void enter_scope_space();
void exit_scope_space();
void in_current_scope_offset(void);
void reset_function_locals_offset();
scopespace_t curr_scope_space();
void restore_curr_scope_offset(unsigned n);

/**
 * @brief  the hash function
 * @note   
 * @param  *pcKey: 
 * @retval 
 */
static unsigned int SymTable_hash(const char *pcKey);

/**
 * @brief  a function that creates the symbol table
 * @note   
 * @retval the symbol table
 */
SymbolTable *symbolTable_create();

/**
 * @brief  a function that inserts a bucket in symbol table
 * @note   
 * @param  symbolTable: the symbol table
 * @param  bucket: bucket to be inserted
 * @retval 
 */
short symbolTable_insert(SymbolTable *symbolTable, SymbolTableEntry *bucket);

/**
 * @brief  a function that makes all symbols in scope inactive
 * @note   
 * @param  symbolTable:the symbol table
 * @param  scope: the scope to make inactive
 * @retval 
 */
short symbolTable_hide(SymbolTable *symbolTable, unsigned int scope);

/**
 * @brief  lookup in the scope
 * @note   
 * @param  symbolTable: the symbol table
 * @param  scope: the scope to lookup in
 * @retval first bucket in scope
 */
SymbolTableEntry *symbolTable_lookup_scope(SymbolTable *symbolTable, unsigned int scope);

/**
 * @brief lookup for variable with name name 
 * @note   
 * @param  symbolTable: the symbol table
 * @param  name: the name of variable to lookup
 * @retval the variable-bucket with name name
 */
SymbolTableEntry *symbolTable_lookup_scopeless_var(SymbolTable *symbolTable, char *name);

/**
 * @brief  lookup for the head of the list in given scope
 * @note   
 * @param  symbolTable: the symbol table 
 * @param  scope: the scope to lookup in 
 * @retval the head-bucket in the scope list
 */
SymbolTableEntry *symbolTable_lookup_head(SymbolTable *symbolTable, unsigned int scope);

/**
 * @brief  
 * @note   
 * @param  symbolTable: 
 * @param  *name: 
 * @retval 
 */
SymbolTableEntry *symbolTable_lookup_scopeless(SymbolTable *symbolTable, const char *name);

/**
 * @brief  lookup if a symbol with given name exists in scope<=given scope
 * @note   
 * @param  symbolTable: the symbol table
 * @param  scope: given scope
 * @param  name: given name 
 * @retval 0 if not found , 1 if found
 */
short symbolTable_lookup_exists(SymbolTable *symbolTable, unsigned int scope, const char *name);

/**
 * @brief  function to print the symbol table
 * @note   
 * @param  symbolTable: the symbol table to be printed 
 * @retval None
 */
void symbolTable_print(SymbolTable *symbolTable);

/**
 * @brief  create a variable
 * @note   
 * @param  name: name of variable 
 * @param  scope: scope of variable
 * @param  line: line of variable 
 * @retval return created variable
 */
Variable *create_var(const char *name, unsigned int scope, unsigned int line);

/**
 * @brief  create a function
 * @note   
 * @param  name: name of function 
 * @param  scope: scope of function
 * @param  line: line of function 
 * @retval return created function
 */
Function *create_func(const char *name, unsigned int scope, unsigned int line);

/**
 * @brief  create a bucket for a variable
 * @note   
 * @param  isActive: indicates if a variable is active
 * @param  var: the variable
 * @param  type: the type of the variable
 * @retval a variable-bucket
 */
SymbolTableEntry *create_bucket_var(short isActive, Variable *var, enum SymbolType type);

/**
 * @brief  create a bucket for a function
 * @note   
 * @param  isActive: indicates if a function is active
 * @param  var: the function
 * @param  type: the type of the function
 * @retval a function-bucket
 */
SymbolTableEntry *create_bucket_func(short isActive, Function *func, enum SymbolType type);

/**
 * @brief  a function to print the scope list for a given scope 
 * @note   
 * @param  symbolTable: the symbol table 
 * @param  scope: given scope
 * @retval None
 */
int  symbolTable_print_scope_list(SymbolTable *symbolTable, unsigned int scope);

/**
 * @brief  a function that inserts all library functions in the symbol table
 * @note   
 * @param  symtable: the symbol table 
 * @retval 
 */
static short load_lib_functions(SymbolTable *symtable);

//SymbolTableEntry ** create_arguments_buckets(Variable ** arguments , unsigned int size );

/**
 * @brief  insert arguments of a fuction in the symbol table
 * @note   
 * @param  symTable: the symbol table
 * @param  arg_buckets: the argument-buckets to be inserted
 * @param  size: size of arg_buckets array 
 * @retval 
 */
short symbolTable_insert_args(SymbolTable *symTable, SymbolTableEntry **arg_buckets, unsigned int size);

/**
 * @brief  find if a symbol with a given name exists in a given scope
 * @note   
 * @param  symbolTable:the symbol table 
 * @param  scope: given scope 
 * @param  name: given name 
 * @retval 
 */
short symbolTable_lookup_exists_exact_scope(SymbolTable *symbolTable, unsigned int scope, const char *name);

/**
 * @brief  find if a function with a given name is library function
 * @note   
 * @param  symTable: the symbol table 
 * @param  name: given name 
 * @retval 
 */
short is_library_func(SymbolTable *symTable, const char *name);

/**
 * @brief  find if there is a user function in a given scope
 * @note   
 * @param  symTable: symbol table 
 * @param  scope: given scope
 * @retval 
 */
short symbolTable_lookup_function(SymbolTable *symTable, unsigned int scope);

//char *SymbolType_to_string(enum SymbolType type);
void symbolTable_print_scopes(SymbolTable *symbolTable, unsigned int scope);

/**
 * @brief  given a function-bucket print function's arguments 
 * @note   
 * @param  fnc: given function-bucket 
 * @retval None
 */
void print_func_args(SymbolTableEntry *fnc);

short create_arguments(SymbolTable *symtable, char *arguments, unsigned int scope);

SymbolTableEntry *find_bucket_by_scope_and_name(SymbolTable *symtable, char *name, unsigned int scope);

/**
 * @brief  find the last function inserted in given scope
 * @note   
 * @param  symtable: symbol table 
 * @param  scope: given scope 
 * @retval function-bucket
 */
SymbolTableEntry *last_func_inserted_in_current_scope(SymbolTable *symtable, unsigned int scope);

/**
 * @brief  given the name of a symbol find its scope
 * @note   
 * @param  symbolTable: symbol table  
 * @param  name: given name
 * @retval the scope
 */
double find_bucket_scope(SymbolTable *symbolTable, char *name);

//short is_argument( SymbolTableEntry * func);
short create_argument(SymbolTable *symtable, char *argument, unsigned int scope);

/**
 * @brief  find if given bucket is a function
 * @note   
 * @param  lvalue: given bucket
 * @retval 
 */
short is_function(SymbolTableEntry *lvalue);

/**
 * @brief  push for the stack of functions inserted in symbol table (insert in the stack)
 * @note   
 * @param  root: root of the stack
 * @param  func: bucket to be pushed
 * @retval 
 */
int push(function_stack *root, SymbolTableEntry *func);

/**
 * @brief  pop for the stack of functions inserted in symbol table (delete from stack)
 * @note   
 * @param  root: root of the stack
 * @retval 
 */
int pop(function_stack *root);

/**
 * @brief  top for the stack of functions inserted in symbol table (return last inserted function)
 * @note   
 * @param  root: root of the stack
 * @retval last inserted function-bucket
 */
SymbolTableEntry *top(function_stack *root);

/**
 * @brief  print the function stack 
 * @note   
 * @param  root: root of stack
 * @retval None
 */
void print_stack(function_stack *root);

/**
 * @brief  push for the stack of opened functions and loops  (insert in the stack)
 * @note   
 * @param  entry: entry to be inserted in  the stack
 * @retval 
 */
int push_func_loop(enum func_loops entry);

/**
 * @brief  pop for the stack of opened functions and loops (delete from stack)
 * @note   
 * @retval 
 */
int pop_func_loop();

/**
 * @brief  top for the stack  of opened functions and loops  
 * @note   
 * @retval last opened loop or function
 */
enum func_loops top_func_loop();

/**
 * @brief  print the function stack 
 * @note   
 * @retval None
 */
void print_stack_func_loop();

extern func_loop_stack *root_func_loop_stack;

extern function_stack *functions_stack;
extern scope_offset_stack *scope_offset_stack_root;

unsigned  pop_scope_offset_stack();
int   push_scope_offset_stack(unsigned scope_offset);
unsigned top_scope_offset_stack();


