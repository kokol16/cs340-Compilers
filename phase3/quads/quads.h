#include "../Symboltable_functions/symbolTable.h"
typedef enum iopcode
{
    assign,
    mul,
    uminus,
    add,
    sub,
    _div,
    mod,
    and,
    or
    ,
    not,
    if_eq,
    if_noteq,
    if_lesseq,
    if_greatereq,
    if_less,
    if_greater,
    call,
    param,
    ret,
    getretval,
    funcstart,
    funcend,
    tablecreate,
    tablegetelem,
    tablesetelem,
    jump
} iopcode;

typedef struct expr expr;
typedef enum expr_t expr_t;

typedef struct for_struct
{
    expr * expr ;
    unsigned test;
    unsigned enter;
}for_struct;
typedef struct indexed
{
    expr *left;
    expr *right;
    struct indexed *next;
} indexed;

typedef struct quad
{
    iopcode op;
    expr *result;
    expr *arg1;
    expr *arg2;
    unsigned label;
    unsigned line;
    unsigned quad_no;
} quad;
extern quad *quads;
extern unsigned total;
extern unsigned int curr_quad;
#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)
void expand();
void emit(iopcode op, expr *arg1, expr *arg2, expr *result,unsigned quad_no, unsigned label, unsigned line);
void print_quad(iopcode op, expr *arg1, expr *arg2, expr *result,unsigned curr_no, unsigned label, unsigned line, FILE *quad_file );
expr *lvalue_expr(SymbolTableEntry *bucket);
void resettemp();
unsigned next_quad(void);
SymbolTableEntry *new_temp(SymbolTable *symbolTable);

char *newtempname();
unsigned next_quad_label();
void patch_label(unsigned int quad_no, unsigned label);
char *opcode_to_string(iopcode);

expr *new_expr_const_string(char *name);
expr *new_expr(expr_t type);
expr *new_expr_const_nil();

expr *new_expr_const_bool(unsigned char bool);
expr *new_expr_const_double(double doubleVal);
expr *new_expr_const_int(int intVal);

expr *emit_if_table_item(expr *_expr);
unsigned pop_elist(expr **elist_entry);
int push_elist(expr **elist_entry, expr *entry);
void print_elist(expr *head);

void print_indexed_list(indexed *head);

void check_arith(expr *e, const char *context);
int print_by_type(expr *_expr, FILE *fp);
typedef enum expr_t
{
    var_e,
    tableitem_e,
    programfunc_e,
    libraryfunc_e,
    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,
    constint_e,
    constdouble_e,
    constbool_e,
    conststring_e,
    nil_e
} expr_t;

typedef struct expr
{
    expr_t type;
    SymbolTableEntry *sym;
    expr *index;
    double doubleConst;
    int intConst;
    char *strConst;
    unsigned char boolConst;
    expr *next;
    expr *prev;
    expr *tail;

} expr;

typedef struct call_info
{
    struct expr *elist;
    unsigned char method;
    char *name;
} call_info;

extern int temp_counter;
