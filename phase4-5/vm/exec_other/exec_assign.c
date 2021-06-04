
#include "exec_other.h"
#include <assert.h>
unsigned char execution_finished ;
unsigned pc;
unsigned currLine ;
unsigned codeSize ;
instruction *code ;

unsigned totalActuals ;
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




void avm_assign(avm_memcell *lv, avm_memcell *rv)
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

void execute_assign(instruction *instr)
{
    fprintf(stderr,"execute assign\n");

    avm_memcell *lv = avm_translate_operand(&instr->result, (avm_memcell *)0);
    avm_memcell *rv = avm_translate_operand(&instr->arg1, &ax);
    assert(lv && (&stack[AVM_STACK_SIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    assert(rv); //should do similar assertion tests here
    avm_assign(lv, rv);
}
