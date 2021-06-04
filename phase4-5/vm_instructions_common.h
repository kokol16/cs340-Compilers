#pragma once
#include <stdio.h>
typedef enum vmopcode
{
    assign_v,
    add_v,
    sub_v,
    mul_v,
    div_v,
    mod_v,
    uminus_v,
    and_v,
    or_v,
    not_v,
    jeq_v,
    jne_v,
    jle_v,
    jge_v,
    jlt_v,
    jgt_v,
    call_v,
    pusharg_v,
    return_v,
    get_ret_val_v,
    funcenter_v,
    funcexit_v,
    newtable_v,
    tablegetelem_v,
    tablesetelem_v,
    jump_v,
    nop_v,

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
    const char *name;
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
void print_instructions_analytics(vmopcode op, vmarg *arg1, vmarg *arg2, vmarg *result, unsigned curr_no, FILE *instr_file);
 void print_text_file(vmopcode op, vmarg *arg1, vmarg *arg2, vmarg *result, unsigned curr_no, FILE *instr_file, unsigned line);
