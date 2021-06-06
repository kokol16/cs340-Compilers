#include "exec_arith.h"
#include <assert.h>
#include "../vm.h"

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

typedef double (*arithmetic_func_t)(double x, double y);
double add_impl(double x, double y)
{
    return x + y;
}
double sub_impl(double x, double y)
{
    return x - y;
}
double mul_impl(double x, double y)
{
    return x * y;
}
double div_impl(double x, double y)
{
    if (y != 0)
    {
        return x / y;
    }
    else
    {
        //error division with 0
    }
}
double mod_impl(double x, double y)
{
    if (y != 0)
    {
        return ((unsigned)x) % ((unsigned)y);
    }
    else
    {
        //error mod with 0
    }
}
arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl};

void execute_arithmetic(instruction *instr)
{

    fprintf(stderr, "popaaaaa\n");
    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);

    assert(lv && (&stack[AVM_STACK_SIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    //assert(rv1 && rv2);
    if (rv1 && rv1->type != number_m || rv2 && rv2->type != number_m)
    {
        avm_error("error not a number in arithmetic\n", NULL, NULL);
        //error not a number in arithmetic
        execution_finished = 1;
    }
    else
    {
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
        avm_memcell_clear(lv);
        lv->type = number_m;
        if (rv1 == NULL)
        {
            lv->data.numVal = (*op)(1, rv2->data.numVal);

        }
        else if (rv2 == NULL)
        {
            lv->data.numVal = (*op)(rv1->data.numVal, 1);

        }
        else
        {
            lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
        }
    }
}
