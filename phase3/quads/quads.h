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
    or,
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
    tablesetelem
} iopcode;

typedef struct expr expr;

typedef struct quad
{
    iopcode op;
    expr *result;
    expr *arg1;
    expr *arg2;
    unsigned label;
    unsigned line;
} quad;
quad *quads = NULL;
unsigned total = 0;
unsigned int curr_quad = 0;
#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)
void expand();
void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line);

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
    constnum_e,
    constbool_e,
    conststring_e,
    nil_e
} expr_t;
typedef struct expr
{
    expr_t type;
    SymbolTableEntry *sym;
    expr *index;
    double numConst;
    char *strConst;
    unsigned char boolConst;
    expr *next;
} expr;