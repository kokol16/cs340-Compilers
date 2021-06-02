#include "exec_funcs.h"
#include "../vm.h"
#include <assert.h>
#include "../exec_other/exec_other.h"

#define AVM_NUMACTUALS_OFFSET 4
#define AVM_SAVEDPC_OFFSET 3
#define AVM_SAVEDTOP_OFFSET 2
#define AVM_SAVEDTOPSP_OFFSET 1

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

void avm_assign_v2(avm_memcell *lv, avm_memcell *rv)
{
    if (lv == rv)
        return;

    if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal)
    {
        return;
    }
    if (rv->type == undef_m)
    {
    } //warning

    avm_memcell_clear(lv);
    memcpy(lv, rv, sizeof(avm_memcell));
    if (lv->type == string_m)
    {
        lv->data.strVal = strdup(rv->data.strVal);
    }
    else if (lv->type == table_m)
    {
        avm_table_inc_ref_counter(lv->data.tableVal);
    }
}

void avm_dec_top()
{
    if (!top)
    {
        //avm error stack overflow
        execution_finished = 1;
    }
    else
    {
        --top;
    }
}

void avm_push_envalue(unsigned val)
{
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}
void avm_callsaveenviroment()
{
    avm_push_envalue(totalActuals);
    avm_push_envalue(pc + 1);
    avm_push_envalue(top + totalActuals + 2);
    avm_push_envalue(topsp);
}
typedef void (*library_func_t)(void);
library_func_t avm_get_library_func(char *id)
{
}
void avm_call_lib_func(char *id)
{
    library_func_t f = avm_get_library_func(id);
    if (!f)
    {
        //avm error
        execution_finished = 1;
    }
    else
    {
        topsp = top;
        totalActuals = 0;
        (*f)();
        if (!execution_finished)
        {
            execute_funcexit(NULL);
        }
    }
}

void execute_call(instruction *instr)
{
    avm_memcell *func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    avm_callsaveenviroment();
    switch (func->type)
    {
    case userfunc_m:
    {
        pc = func->data.funVal;
        assert(pc < AVM_ENDING_PC);
        assert(code[pc].opcode == funcenter_v);
        break;
    }
    case string_m:
        avm_call_lib_func(func->data.strVal);
    case libfunc_m:
        avm_call_lib_func(func->data.libfuncVal);
    default:
    {
        //avm error
        execution_finished = 1;
    }
    }
}
unsigned avm_get_envvalue(unsigned i)
{
    assert(stack[i].type == number_m);
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].data.numVal == (double)val);
    return val;
}
userfunc *avm_get_func_info(unsigned pc)
{
    assert(pc < total_user_funcs);
    return &user_funcs[pc];
}
void execute_pusharg(instruction *instr)
{
    avm_memcell *arg = avm_translate_operand(&instr->arg1, &ax);
    assert(arg);
    avm_assign_v2(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}
void execute_funcexit(instruction *instr)
{
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    while (++oldTop <= top)
    {
        avm_memcell_clear(&stack[oldTop]);
    }
}
void execute_funcenter(instruction *instr)
{
    avm_memcell *func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == func->data.funVal);

    /* callee actions here */
    totalActuals = 0;
    userfunc *func_info = avm_get_func_info(pc);
    topsp = top;
    top = top - func_info->localSize;
}
