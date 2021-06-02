#include "exec_jumps.h"
#include "../vm.h"
#include <assert.h>
unsigned char execution_finished;
unsigned pc;
unsigned currLine;
unsigned codeSize;
instruction *code;

unsigned totalActuals;
double *consts_number;
unsigned total_numbers;
char **consts_string;
unsigned total_strings;
unsigned total_user_funcs;
struct userfunc *user_funcs;
char **lib_funcs;
unsigned total_lib_funcs;
struct avm_memcell ax, bx, cx;
struct avm_memcell retval;
unsigned top, topsp;

typedef unsigned char (*tobool_func_t)(avm_memcell *);

unsigned char number_to_bool(avm_memcell *m)
{
    return m->data.numVal != 0;
}
unsigned char string_to_bool(avm_memcell *m)
{
    return m->data.strVal[0] != 0;
}
unsigned char bool_to_bool(avm_memcell *m)
{
    return m->data.boolVal;
}
unsigned char table_to_bool(avm_memcell *m)
{
    return 1;
}
unsigned char userfunc_to_bool(avm_memcell *m)
{
    return 1;
}
unsigned char libfunc_to_bool(avm_memcell *m)
{
    return 1;
}
unsigned char nil_to_bool(avm_memcell *m)
{
    return 0;
}
unsigned char undef_to_bool(avm_memcell *m)
{
    assert(0);
    return 0;
}

tobool_func_t toboolFuncs[] = {
    number_to_bool,
    string_to_bool,
    bool_to_bool,
    table_to_bool,
    userfunc_to_bool,
    libfunc_to_bool,
    nil_to_bool,
    undef_to_bool};

char *typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"};

unsigned char avm_tobool(avm_memcell *m)
{

    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}

void execute_jeq(instruction *instr)
{
    assert(instr->result.type == label_a);
    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);
    unsigned char result = 0;
    if (rv1->type == undef_m || rv2->type == undef_m)
    {
        //avm_error
        execution_finished = 1;
    }
    else if (rv1->type == nil_m || rv2->type == nil_m)
    {
        result = (rv1->type == nil_m) && (rv2->type == nil_m);
    }
    else if (rv1->type == bool_m || rv2->type == bool_m)
    {
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    }
    else if (rv1->type != rv2->type)
    {
        //avm_error
    }
    else
    {
        //dispatching
    }

    if (!execution_finished && result)
    {
        pc = instr->result.val;
    }
}
void execute_jne(instruction *instr) {}
void execute_jle(instruction *instr) {}
void execute_jge(instruction *instr) {}
void execute_jlt(instruction *instr) {}
void execute_jgt(instruction *instr) {}