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

typedef unsigned char (*cmp_func)(double x, double y);

typedef unsigned char (*check_equality)(avm_memcell *m1, avm_memcell *m2);

unsigned char numbereq_check(avm_memcell *m1, avm_memcell *m2)
{
    fprintf(stderr, "numbereq_check %f == %f\n", m1->data.numVal, m2->data.numVal);

    return m1->data.numVal == m2->data.numVal;
}
unsigned char stringeq_check(avm_memcell *m1, avm_memcell *m2)
{
    return strcmp(m1->data.strVal, m2->data.strVal) == 0;
}

unsigned char booleq_check(avm_memcell *m1, avm_memcell *m2)
{

    return m1->data.boolVal == m2->data.boolVal;
}
unsigned char tableeq_check(avm_memcell *m1, avm_memcell *m2)
{

    return 1;
}
unsigned char user_funceq_check(avm_memcell *m1, avm_memcell *m2)
{
    return strcmp(user_funcs[m1->data.funVal].id, user_funcs[m2->data.funVal].id) == 0;
}
unsigned char lib_funceq_check(avm_memcell *m1, avm_memcell *m2)
{
    return strcmp(m1->data.libfuncVal, m2->data.libfuncVal) == 0;
}

check_equality equalityFuncs[] = {
    numbereq_check,
    stringeq_check,
    booleq_check,
    tableeq_check,
    user_funceq_check,
    lib_funceq_check

};

unsigned char jge_impl(double x, double y)
{
    return x >= y;
}
unsigned char jgt_impl(double x, double y)
{
    return x > y;
}
unsigned char jle_impl(double x, double y)
{
    return x <= y;
}
unsigned char jlt_impl(double x, double y)
{

    return x < y;
}

cmp_func comparisonFuncs[] = {
    jle_impl,
    jge_impl,
    jlt_impl,
    jgt_impl,

};

void execute_cmp(instruction *instr)
{
    unsigned char result = 0;
    //avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);
    //assert(lv );
    //assert( (&stack[AVM_STACK_SIZE - 1] >= lv && lv > &stack[top] || lv == &retval));

    assert(rv1 && rv2);
    if (rv1->type != number_m || rv2->type != number_m)
    {
        //error not a number in arithmetic
        execution_finished = 1;
    }
    else
    {
        fprintf(stderr, "aferesi %d\n", instr->opcode - jle_v);
        result = comparisonFuncs[instr->opcode - jle_v](rv1->data.numVal, rv2->data.numVal);

        //avm_memcell_clear(lv);
        //lv->type = bool_m;
        //lv->data.boolVal = (*op)(rv1->data.numVal, rv2->data.numVal);
    }
    if (!execution_finished && result == 1)
    {
        pc = instr->result.val;
    }
}

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

void execute_jne(instruction *instr)
{
    assert(instr->result.type == label_a);
    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);
    unsigned char result = 0;
    if (rv1->type == undef_m || rv2->type == undef_m)
    {
        avm_error("undef involed to equality\n", NULL, NULL);
        //avm_error
        execution_finished = 1;
    }
    else if (rv1->type == nil_m || rv2->type == nil_m)
    {
        result = (rv1->type != nil_m) || (rv2->type != nil_m);
    }
    else if (rv1->type == bool_m || rv2->type == bool_m)
    {
        result = (avm_tobool(rv1) != avm_tobool(rv2));
    }
    else if (rv1->type != rv2->type)
    {
        avm_error("%s == %s is illegal\n", typeStrings[rv1->type], typeStrings[rv1->type]);

        //avm_error
    }
    else
    {
        result = !(equalityFuncs[rv1->type](rv1, rv2));
        //dispatching
    }

    if (!execution_finished && result == 1)
    {
        pc = instr->result.val;
    }
}
void execute_jeq(instruction *instr)
{
    assert(instr->result.type == label_a);

    avm_memcell *rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2, &bx);
    unsigned char result = 0;
    if (rv1->type == undef_m || rv2->type == undef_m)
    {
        avm_error("undefined type in jeq\n", NULL, NULL);
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
        avm_error("different types \n", NULL, NULL);
        execution_finished = 1;
    }
    else
    {
        result = equalityFuncs[rv1->type](rv1, rv2);
        //fprintf(stderr, "result is %d\n", result);
    }

    if (!execution_finished && result == 1)
    {

        pc = instr->result.val;
        fprintf(stderr, "pc after if equality %u\n", pc);
    }
}
