
#include "exec_tables.h"
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

void avm_assign_v3(avm_memcell *lv, avm_memcell *rv)
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
void execute_newtable(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(&instr->result, NULL);
    assert(lv && (&stack[AVM_STACK_SIZE - 1] >= lv && lv > &stack[top] || lv == &retval));
    avm_memcell_clear(lv);
    lv->type = table_m;
    lv->data.tableVal = avm_table_new();
    avm_table_inc_ref_counter(lv->data.tableVal);
}
avm_memcell *avm_tablegetelement(avm_table *table, avm_memcell *index)
{
    avm_table_get(table, index);
}
void execute_tablegetelem(instruction *instr)
{
    avm_memcell *lv = avm_translate_operand(&instr->result, NULL);
    avm_memcell *t = avm_translate_operand(&instr->arg1, NULL);
    avm_memcell *i = avm_translate_operand(&instr->arg2, &ax);
    assert(lv && &stack[AVM_STACK_SIZE - 1] >= lv && lv > &stack[top]);
    assert(t && &stack[AVM_STACK_SIZE - 1] >= t && t > &stack[top]);
    assert(i);
    avm_memcell_clear(lv);
    lv->type = nil_m;
    if (t->type != table_m)
    {
        //avm error
    }
    else
    {
        avm_memcell *content = avm_tablegetelement(t->data.tableVal, i);
        if (content)
        {
            avm_assign_v3(lv, content);
        }
        else
        {
            //avm error
        }
    }
}
avm_memcell *avm_tablesetelement(avm_table *table, avm_memcell *index, avm_memcell *content)
{
    avm_table_insert(table, index, content);
}
void execute_tablesetelem(instruction *instr)
{
    avm_memcell *t = avm_translate_operand(&instr->result, NULL);
    avm_memcell *i = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell *c = avm_translate_operand(&instr->arg2, &bx);

    assert(t && &stack[AVM_STACK_SIZE - 1] >= t && t > &stack[top]);
    assert(i && c);
    if (t->type != table_m)
    {
        //avm error
    }
    else
    {
        avm_tablesetelement(t->data.tableVal, i, c);
    }
}