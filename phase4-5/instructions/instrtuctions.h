typedef enum vmopcode
{
    assign_v,
    mul_v,
    uminus_v,
    add_v,
    sub_v,
    _div_v,
    mod_v,
    and_v,
    or_v,
    not_v,
    if_eq_v,
    if_noteq_v,
    if_lesseq_v,
    if_greatereq_v,
    if_less_v,
    if_greater_v,
    call_v,
    param_v,
    ret_v,
    getretval_v,
    funcstart_v,
    funcend_v,
    tablecreate_v,
    tablegetelem_v,
    tablesetelem_v,
    jump_v
} iopcode;

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
}vmarg_t;

typedef struct vmarg
{
    vmarg_t type;
    unsigned val;
}vmarg;
typedef struct instruction
{
    vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;
}instruction;
struct userfunc
{
    unsigned address;
    unsigned localSize;
    char * id;
};
double * num_consts;
unsigned total_num_consts;
char ** string_consts;
unsigned total_string_consts;
char ** named_lib_funcs;
unsigned total_named_lib_funcs;
userfunc * user_funcs;
unsigned total_user_funcs;



