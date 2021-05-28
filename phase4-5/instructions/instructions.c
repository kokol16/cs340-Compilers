#include "instrtuctions.h"
#include <stdlib.h>
#include <string.h>

void make_numberoperand(vmarg *arg, unsigned val)
{
    arg->val = consts_new_number(val);
    arg->type = number_a;
}

void make_booloperand(vmarg *arg, unsigned val)
{
    arg->val = val;
    arg->type = bool_a;
}
unsigned nextinstructionlabel()
{
    return curr_instr;
}

void add_incomplete_jump(unsigned _intr_no, unsigned iaddress)
{
    incomplete_jump *ij, *tmp;
    ij = malloc(sizeof(incomplete_jump));
    ij->iaddress = iaddress;
    ij->instr_no = _intr_no;
    tmp = ij_head;
    ij_total++;
    if (ij_head == NULL)
    {
        ij_head = ij;
        return;
    }
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = ij;
}

void emit_instr(instruction t)
{
    if (curr_instr == 0 || curr_instr % EXPAND_SIZE == 0)
        expand_incomplete_instr();
    instructions[curr_instr++] = t;
}

void generate(vmopcode opcode, quad quad)
{
    instruction t;
    t.opcode = opcode;
    make_operand(quad.arg1, &t.arg1);
    make_operand(quad.arg2, &t.arg2);
    make_operand(quad.result, &t.result);
    quad.taddress = curr_instr;
    emit_instr(t);
}

void generate_ADD(quad quad)
{
    generate(add_v, quad);
}
void generate_SUB(quad quad)
{
    generate(sub_v, quad);
}
void generate_MUL(quad quad)
{
    generate(mul_v, quad);
}
void generate_DIV(quad quad)
{
    generate(div_v, quad);
}
void generate_MOD(quad quad)
{
    generate(mod_v, quad);
}
void generate_NEWTABLE(quad quad)
{
    generate(newtable_v, quad);
}
void generate_TABLEGETELEM(quad quad)
{
    generate(tablegetelem_v, quad);
}
void generate_TABLESETELEM(quad quad)
{
    generate(tablesetelem_v, quad);
}
void generate_ASSIGN(quad quad)
{
    generate(assign_v, quad);
}

void generate_NOP()
{
    instruction t;
    t.opcode = nop_v;
    emit_instr(t);
}
void generate_relational(vmopcode op, quad quad)
{
    instruction t;
    t.opcode = op;
    make_operand(quad.arg1, &t.arg1);
    make_operand(quad.arg2, &t.arg2);
    t.result.type = label_a;
    if (quad.label < curr_quad)
    {
        t.result.val = quads[quad.label].taddress;
    }
    else
    {
        add_incomplete_jump(curr_instr, quad.label);
    }
    quad.taddress = curr_instr;
    emit_instr(t);
}

void reset_operand(vmarg *arg)
{
    arg->val = 0;
    arg->type = 0;
}

void generate_NOT(quad quad)
{
    quad.taddress = nextinstructionlabel();
    instruction t;
    t.opcode = jeq_v;
    make_operand(quad.arg1, &t.arg1);
    make_booloperand(&t.arg2, 0);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 3;
    emit_instr(t);
    t.opcode = assign_v;
    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(quad.result, &t.result);
    emit_instr(t);
    t.opcode = jump_v;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 2;
    emit_instr(t);
    t.opcode = assign_v;
    make_booloperand(&t.arg1, 1);
    reset_operand(&t.arg2);
    make_operand(quad.result, &t.result);
    emit_instr(t);
}

void generate_JUMP(quad quad) { generate_relational(jump_v, quad); }
void generate_IF_EQ(quad quad) { generate_relational(jeq_v, quad); }
void generate_IF_NOTEQ(quad quad) { generate_relational(jne_v, quad); }
void generate_IF_GREATER(quad quad) { generate_relational(jgt_v, quad); }
void generate_IF_GREATEREQ(quad quad) { generate_relational(jge_v, quad); }
void generate_IF_LESS(quad quad) { generate_relational(jlt_v, quad); }
void generate_IF_LESSEQ(quad quad) { generate_relational(jle_v, quad); }

void generate_OR(quad quad)
{
    quad.taddress = nextinstructionlabel();
    instruction t;
    t.opcode = jeq_v;
    make_operand(quad.arg1, &t.arg1);
    make_booloperand(&t.arg2, 1);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 4;
    emit_instr(t);
    make_operand(quad.arg2, &t.arg1);
    t.result.val = nextinstructionlabel() + 3;
    emit_instr(t);
    t.opcode = jump;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 2;
    emit_instr(t);
    t.opcode = assign;
    make_booloperand(&t.arg1, 1);
    reset_operand(&t.arg2);
    make_operand(quad.result, &t.result);
    emit_instr(t);
}

void generate_PARAM(quad quad)
{
    quad.taddress = nextinstructionlabel();
    instruction t;
    t.opcode = pusharg_v;
    make_operand(quad.arg1, &t.arg1);
    emit_instr(t);
}
void generate_CALL(quad quad)
{
    quad.taddress = nextinstructionlabel();
    instruction t;
    t.opcode = callfunc_v;
    make_operand(quad.arg1, &t.arg1);
    emit_instr(t);
}
void generate_GETRETVAL(quad quad)
{
    quad.taddress = nextinstructionlabel();
    instruction t;
    t.opcode = assign_v;
    make_operand(quad.result, &t.result);
    make_retvaloperand(&t.arg1);
    emit_instr(t);
}
void expand_incomplete_instr()
{
    instructions = realloc(instructions, EXPAND_SIZE * sizeof(instructions));
}
void expand_num_consts()
{
    //assert(total_num_consts == curr_quad);
    double *_num_consts;
    _num_consts = malloc(EXPAND_SIZE * sizeof(_num_consts) + total_num_consts);
    memset(num_consts, 0, sizeof(num_consts));
    if (num_consts)
    {
        memcpy(_num_consts, num_consts, total_num_consts * sizeof(num_consts));
        free(num_consts);
    }
    num_consts = _num_consts;
    total_num_consts += EXPAND_SIZE;
}
void expand_string_consts()
{
    //assert(total_num_consts == curr_quad);
    string_consts = realloc(string_consts, sizeof(*string_consts) * (total_string_consts + EXPAND_SIZE));
    total_string_consts += EXPAND_SIZE;
}
void expand_named_lib_funcs()
{
    named_lib_funcs = realloc(named_lib_funcs, sizeof(*named_lib_funcs) * (total_named_lib_funcs + EXPAND_SIZE));
    total_named_lib_funcs += EXPAND_SIZE;
}
void expand_user_funcs()
{
    //assert(total_num_consts == curr_quad);
    userfunc *_user_funcs;
    _user_funcs = malloc(EXPAND_SIZE * sizeof(_user_funcs) + total_user_funcs);
    memset(user_funcs, 0, sizeof(user_funcs));
    if (user_funcs)
    {
        memcpy(_user_funcs, user_funcs, total_user_funcs * sizeof(user_funcs));
        free(user_funcs);
    }
    user_funcs = _user_funcs;
    total_user_funcs += EXPAND_SIZE;
}

void make_operand(expr *e, vmarg *arg)
{
    switch (e->type)
    {
    case var_e:
    case tableitem_e:
    case arithexpr_e:
    case boolexpr_e:
    case newtable_e:
    {

        assert(e->sym);
        arg->val = e->sym->offset;
        switch (e->sym->space)
        {
        case programvar:
            arg->type = global_a;
            break;
        case functionlocal:
            arg->type = local_a;
            break;
        case formalarg:
            arg->type = formal_a;
            break;

        default:
            assert(0);
        }
    }
    case constbool_e:
    {
        arg->val = e->boolConst;
        arg->type = bool_a;
        break;
    }
    case conststring_e:
    {
        arg->val = consts_new_string(e->strConst);
        arg->type = string_a;
        break;
    }
    case constdouble_e:
    {
        arg->val = consts_new_number(e->doubleConst);
        arg->type = number_a;
    }
    case nil_e:
        arg->type = nil_a;
        break;
    case programfunc_e:
    {
        arg->type = userfunc_a;
        //arg->val = e->sym->;
        //another way exists
    }
    case libraryfunc_e:
    {
        arg->type = libfunc_a;
        arg->val = libfuncs_new_used(e->sym->value.funcVal->name);
        break;
    }
    }
}

unsigned consts_new_number(double number)
{
    if (total_num_consts == 0 || total_num_consts % EXPAND_SIZE == 0)
        expand_num_consts();
    num_consts[total_num_consts++] = number;
    return total_num_consts - 1;
}

unsigned consts_new_string(char *str)
{
    if (total_string_consts == 0 || total_num_consts % EXPAND_SIZE == 0)
        expand_string_consts();
    string_consts[total_string_consts++] = strdup(str);
    return total_string_consts - 1;
}

unsigned libfuncs_new_used(const char *s)
{
    if (total_named_lib_funcs == 0 || total_named_lib_funcs % EXPAND_SIZE == 0)
        expand_named_lib_funcs();
    named_lib_funcs[total_named_lib_funcs++] = strdup(s);
    return total_named_lib_funcs - 1;
}

unsigned userfuncs_new_func(SymbolTableEntry *sym)
{
    if (total_user_funcs == 0 || total_user_funcs % EXPAND_SIZE == 0)
        expand_user_funcs();
    userfunc *_user_func;
    _user_func = malloc(sizeof(userfunc));
    _user_func->id = strdup(sym->value.funcVal->name);

    //user_funcs[total_user_funcs++] = sym->;
    return total_user_funcs - 1;
}

void make_retvaloperand(vmarg *arg)
{
    arg->type = retval_a;
}