#include "../Symboltable_functions/symbolTable.h"

typedef enum iopcode
{
    assign=0,//0
    mul,//1
    uminus,//2
    add,//3
    sub,//4
    _div,//5
    mod,//6
    and,//7
    or,//8
    not,//9
    if_eq,//10
    if_noteq,//11
    if_lesseq,//12
    if_greatereq,//13
    if_less,//14
    if_greater,//15
    call,//16
    param,//17
    ret,//18
    getretval,//19
    funcstart,//20
    funcend,//21
    tablecreate,//22
    tablegetelem,//23
    tablesetelem,//24
    jump,//25
    nop//26
} iopcode;

typedef struct expr expr;
typedef enum expr_t expr_t;
typedef struct stmt_t _stmt_t;

/*
typedef struct truth_list
{
    int truelist, falselist;
} truth_list;
*/
typedef struct stmt_t
{
    int breaklist, contlist;
} stmt_t;
typedef struct for_struct
{
    expr *expr;
    unsigned test;
    unsigned enter;
} for_struct;
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
    unsigned taddress;
} quad;
extern int found_compile_error;
extern quad *quads;
extern unsigned total;
extern unsigned int curr_quad;
#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)
void expand();
void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned quad_no, unsigned label, unsigned line);
void print_quad(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned curr_no, unsigned label, unsigned line, FILE *quad_file);
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

void make_stmt(stmt_t *s);
int newlist(int i);

int mergelist(int l1, int l2);
void patchlist(int list, int label);
void make_truth_list(expr *s);
void print_quads(FILE *quad_file);
void print_list(int list);
void print_quad_analytic(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned curr_no, unsigned label, unsigned line, FILE *quad_file);
void generate_eq_eq(FILE *quad_file, unsigned numb_of_eq);
void print_quad_analytic_2nd_try(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned curr_no, unsigned label, unsigned line, FILE *quad_file);

typedef enum expr_t
{
    var_e,//0
    tableitem_e,//1
    programfunc_e,//2
    libraryfunc_e,//3
    arithexpr_e,//4
    boolexpr_e,//5
    assignexpr_e,//6
    newtable_e,//7
    constint_e,//8
    constdouble_e,//9
    constbool_e,//10
    conststring_e,//11
    nil_e//12
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
    int truelist;
    int falselist;
} expr;

typedef struct call_info
{
    struct expr *elist;
    unsigned char method;
    char *name;
} call_info;

extern int temp_counter;
