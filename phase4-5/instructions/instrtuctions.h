#include "../quads/quads.h"

typedef enum vmopcode
{
    assign_v,
    mul_v,
    uminus_v,
    not_v,
    jle_v,
    jgt_v,
    funcenter_v,
    tablegetelem_v,
    add_v,
    div_v,
    and_v,
    jeq_v,
    jge_v,
    call_v,
    funcexit_v,
    tablesetelem_v,
    sub_v,
    mod_v,
    or_v,
    jne_v,
    jlt_v,
    pusharg_v,
    newtable_v,
    nop_v,
    jump_v,
    callfunc_v

} vmopcode;

typedef enum vmarg_t
{
    label_a = 0,
    global_a = 1,
    formal_a = 2,
    local_a = 3,
    number_a = 4,
    string_a = 5,
    bool_a = 6,
    nil_a = 7,
    userfunc_a = 8,
    libfunc_a = 9,
    retval_a = 10
} vmarg_t;

typedef struct vmarg
{
    vmarg_t type;
    unsigned val; /* index  in array */
} vmarg;
typedef struct instruction
{
    vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;
} instruction;
typedef struct userfunc
{
    unsigned address;
    unsigned localSize;
    char *id;
} userfunc;

typedef struct incomplete_jump
{
    unsigned instr_no;            //the jump instruction number
    unsigned iaddress;            //the i-code jump-target address
    struct incomplete_jump *next; //linked list
} incomplete_jump;

incomplete_jump *ij_head = NULL;

unsigned ij_total = 0;
instruction *instructions;
unsigned curr_instr = 0;
void expand_instr();
void add_incomplete_jump(unsigned intr_no, unsigned iaddress);

double *num_consts;
unsigned total_num_consts;
char **string_consts;
unsigned total_string_consts;
char **named_lib_funcs;
unsigned total_named_lib_funcs;
struct userfunc *user_funcs;
unsigned total_user_funcs;

#define EXPAND_SIZE 1024

#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)

unsigned consts_new_number(double number);
unsigned consts_new_string(char *str);
unsigned libfuncs_new_used(const char *s);
unsigned userfuncs_new_func(SymbolTableEntry *sym);
void make_ret_val_operand(vmarg *arg);
void make_operand(expr *e, vmarg *arg);
void generate(vmopcode opcode, quad quad);

void expand_incomplete_instr();
void emit_instr(instruction t);
void make_retvaloperand(vmarg *arg);