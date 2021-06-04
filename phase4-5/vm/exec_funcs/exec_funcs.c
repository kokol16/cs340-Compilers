#include "exec_funcs.h"
#include "../vm.h"
#include <assert.h>
#include "../exec_other/exec_other.h"
#include <stdlib.h>

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
unsigned top = AVM_STACK_SIZE-1, topsp = AVM_STACK_SIZE-1;

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
        fprintf(stderr, "top : %u\n", top);
        avm_error("stack overflow\n", NULL, NULL);
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

library_func_t avm_get_library_func(char *id)
{
    map_lib_funcs *tmp = root_lib_funcs;
    while (tmp != NULL)
    {
        if (strcmp(id, tmp->id) == 0)
        {
            return tmp->func;
        }
        tmp = tmp->next;
    }
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
    fprintf(stderr, "execute call\n");
    
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
    fprintf(stderr, "execute_pusharg\n");
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

void lib_func_total_arguments()
{
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcell_clear(&retval);
    if (!p_topsp)
    {
        //avm error
        retval.type = nil_m;
    }
    else
    {
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}
unsigned avm_totalactuals()
{
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}
avm_memcell *avm_getactual(unsigned i)
{
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}
tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring

};

char *number_tostring(avm_memcell *mem)
{
    int str_size;
    char *name;
    str_size = snprintf(NULL, 0, "%f", mem->data.numVal);
    name = malloc(sizeof(char) * (str_size) + 1);
    str_size = snprintf(name, str_size + 1, "%f", mem->data.numVal);

    return name;
}
char *string_tostring(avm_memcell *mem)
{
    return mem->data.strVal;
}
char *bool_tostring(avm_memcell *mem)
{
    return ((mem->data.boolVal == 0) ? "false" : "true");
}
char *table_tostring(avm_memcell *mem)
{
    switch (mem->type)
    {
    case number_m:
        return "nubmer indexed";

    case string_m:
        return "string indexed";

    case bool_m:
        return "boolean indexed";

    case userfunc_m:
        return "user func  indexed";

    case libfunc_m:
        return "lib func  indexed";

    default:
        //avm error???
        break;
    }
}
char *userfunc_tostring(avm_memcell *mem)
{
    return user_funcs[mem->data.funVal].id;
}
char *libfunc_tostring(avm_memcell *mem)
{
    return mem->data.libfuncVal;
}

char *nil_tostring(avm_memcell *mem)
{
    return "nil";
}
char *undef_tostring(avm_memcell *mem)
{
    return "undef";
}

char *avm_tostring(avm_memcell *mem)
{
    assert(mem->type >= 0 && mem->type <= undef_m);
    return (*tostringFuncs[mem->type])(mem);
}

void libfunc_print()
{
    unsigned n = avm_totalactuals();
    fprintf(stderr, "im going to print %u", n);
    for (unsigned i = 0; i < n; i++)
    {
        char *s = avm_tostring(avm_getactual(i));
        puts(s);
        free(s);
    }
}
struct map_lib_funcs *root_lib_funcs = NULL;

void avm_registerlibfunc(char *id, library_func_t addr)
{
    map_lib_funcs *tmp = root_lib_funcs;
    map_lib_funcs *entry = malloc(sizeof(map_lib_funcs));
    entry->id = strdup(id);
    entry->func = addr;
    entry->next = NULL;

    if (root_lib_funcs == NULL)
    {
        root_lib_funcs = entry;

        return;
    }
    else
    {

        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
    }

    tmp->next = entry;
}

void libfunc_typeof()
{
    unsigned n = avm_totalactuals();
    if (n != 1)
    {
        //avm error
    }
    else
    {
        avm_memcell_clear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}