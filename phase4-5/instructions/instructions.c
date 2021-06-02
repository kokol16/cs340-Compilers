#include "instrtuctions.h"
incomplete_jump *ij_head = {0};
unsigned ij_total = 0;
unsigned curr_instr = 0;
unsigned total_num_consts = 0;
unsigned total_string_consts = 0;
unsigned total_named_lib_funcs = 0;
unsigned total_user_funcs = 0;
char *vmarg_str[] = {
    "label_a",
    "global_a",
    "formal_a",
    "local_a",
    "number_a",
    "string_a",
    "bool_a",
    "nil_a",
    "userfunc_a",
    "libfunc_a",
    "retval_a"};

generator_func_t generators[] = {
    generate_ASSIGN,       //0
    generate_MUL,          //1
    generate_UMINUS,       //2
    generate_ADD,          //3
    generate_SUB,          //4
    generate_DIV,          //5
    generate_MOD,          //6
    generate_AND,          //7
    generate_OR,           //8
    generate_NOT,          //9
    generate_IF_EQ,        //10
    generate_IF_NOTEQ,     //11
    generate_IF_LESSEQ,    //12
    generate_IF_GREATEREQ, //13
    generate_IF_LESS,      //14
    generate_IF_GREATER,   //15
    generate_CALL,         //16
    generate_PARAM,        //17
    generate_return,       //18
    generate_GETRETVAL,    //19
    generate_funcstart,    //20
    generate_funcend,      //21
    generate_NEWTABLE,     //22
    generate_TABLEGETELEM, //23
    generate_TABLESETELEM, //24
    generate_JUMP,         //25
    generate_NOP,          //26

};

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
    fprintf(stderr, "add to jump list\n");
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
    if (curr_instr == 0)
    {
        fprintf(stderr, "alloc instructions\n");

        instructions = malloc(sizeof(instruction) * EXPAND_SIZE);
    }
    else if (curr_instr % EXPAND_SIZE == 0)
        expand_incomplete_instr();
    instructions[curr_instr++] = t;
}

void reset_instruction(instruction *t)
{
    t->arg1.type = -1;
    t->arg2.type = -1;
    t->result.type = -1;
}
void generate(vmopcode opcode, quad *quad)
{
    //fprintf(stderr, "generate\n");
    instruction t = {0};
    reset_instruction(&t);
    t.srcLine=quad->line;

    t.opcode = opcode;
    if (quad->arg1 != NULL)
        make_operand(quad->arg1, &t.arg1);
    if (quad->arg2 != NULL)
        make_operand(quad->arg2, &t.arg2);
    if (quad->result != NULL)
        make_operand(quad->result, &t.result);

    quad->taddress = curr_instr;
    emit_instr(t);
}

void generate_ADD(quad *quad)
{
    generate(add_v, quad);
}
void generate_SUB(quad *quad)
{
    generate(sub_v, quad);
}
void generate_MUL(quad *quad)
{
    generate(mul_v, quad);
}
void generate_UMINUS(quad *quad)
{

    generate(mul_v, quad);
}
void generate_DIV(quad *quad)
{
    generate(div_v, quad);
}
void generate_MOD(quad *quad)
{
    generate(mod_v, quad);
}
void generate_NEWTABLE(quad *quad)
{
    generate(newtable_v, quad);
}
void generate_TABLEGETELEM(quad *quad)
{
    generate(tablegetelem_v, quad);
}
void generate_TABLESETELEM(quad *quad)
{
    generate(tablesetelem_v, quad);
}
void generate_ASSIGN(quad *quad)
{
    //fprintf(stderr, "generate assingn\n");
    generate(assign_v, quad);
}

void generate_NOP(quad *quad)
{
    instruction t;
    reset_instruction(&t);
    t.opcode = nop_v;
    t.srcLine=quad->line;
    emit_instr(t);
}
void generate_relational(vmopcode op, quad *quad)
{
    //fprintf(stderr, "generate_relational\n");
    instruction t;
    reset_instruction(&t);
    t.srcLine=quad->line;

    t.opcode = op;
    make_operand(quad->arg1, &t.arg1);
    make_operand(quad->arg2, &t.arg2);
    t.result.type = label_a;
    if (quad->label < curr_quad)
    {
        fprintf(stderr, "tadress for result %u\n", quads[quad->label].taddress);
        //quads[quad->label].taddress;
        t.result.val = quad->label;
    }
    else
    {
        fprintf(stderr, "patch incomplete jump\n");
        add_incomplete_jump(curr_instr, quad->label);
        //patch_incomplete_jumps();
    }
    quad->taddress = nextinstructionlabel();
    emit_instr(t);
}

void reset_operand(vmarg *arg)
{
    arg->val = 0;
    arg->type = -1;
}

void generate_NOT(quad *quad)
{
    quad->taddress = nextinstructionlabel();
    instruction t;
    reset_instruction(&t);
    t.srcLine=quad->line;

    t.opcode = jeq_v;
    make_operand(quad->arg1, &t.arg1);
    make_booloperand(&t.arg2, 0);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 3;
    emit_instr(t);
    t.opcode = assign_v;
    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(quad->result, &t.result);
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
    make_operand(quad->result, &t.result);
    emit_instr(t);
}

void generate_JUMP(quad *quad) { generate_relational(jump_v, quad); }
void generate_IF_EQ(quad *quad) { generate_relational(jeq_v, quad); }
void generate_IF_NOTEQ(quad *quad) { generate_relational(jne_v, quad); }
void generate_IF_GREATER(quad *quad) { generate_relational(jgt_v, quad); }
void generate_IF_GREATEREQ(quad *quad) { generate_relational(jge_v, quad); }
void generate_IF_LESS(quad *quad) { generate_relational(jlt_v, quad); }
void generate_IF_LESSEQ(quad *quad) { generate_relational(jle_v, quad); }

void generate_OR(quad *quad)
{
    quad->taddress = nextinstructionlabel();
    instruction t;
    reset_instruction(&t);
    t.srcLine=quad->line;

    t.opcode = jeq_v;
    make_operand(quad->arg1, &t.arg1);
    make_booloperand(&t.arg2, 1);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 4;
    emit_instr(t);
    make_operand(quad->arg2, &t.arg1);
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
    make_operand(quad->result, &t.result);
    emit_instr(t);
}
void generate_AND(quad *quad)
{
    quad->taddress = nextinstructionlabel();
    instruction t;
    reset_instruction(&t);
    t.srcLine=quad->line;

    t.opcode = jeq_v;
    make_operand(quad->arg1, &t.arg1);
    make_booloperand(&t.arg2, 0);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 4;
    emit_instr(t);
    make_operand(quad->arg2, &t.arg1);
    t.result.val = nextinstructionlabel() + 3;
    emit_instr(t);
    t.opcode = jump;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 2;
    emit_instr(t);
    t.opcode = assign;
    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(quad->result, &t.result);
    emit_instr(t);
}

void generate_PARAM(quad *quad)
{
    quad->taddress = nextinstructionlabel();
    instruction t;
    reset_instruction(&t);
    t.srcLine=quad->line;

    t.opcode = pusharg_v;
    make_operand(quad->arg1, &t.arg1);
    emit_instr(t);
}
void generate_CALL(quad *quad)
{
    quad->taddress = nextinstructionlabel();
    instruction t;
    reset_instruction(&t);
    t.srcLine=quad->line;

    t.opcode = call_v;
    make_operand(quad->arg1, &t.arg1);
    emit_instr(t);
}
void generate_GETRETVAL(quad *quad)
{
    quad->taddress = nextinstructionlabel();
    instruction t;
    reset_instruction(&t);
    t.srcLine=quad->line;

    t.opcode = assign_v;
    make_operand(quad->result, &t.result);
    make_retvaloperand(&t.arg1);
    emit_instr(t);
}
void expand_incomplete_instr()
{
    fprintf(stderr, "expand_incomplete_instr\n");
    instructions = realloc(instructions, EXPAND_SIZE * sizeof(instructions));
}
void expand_num_consts()
{
    fprintf(stderr, "expand_num_consts\n");
    num_consts = realloc(num_consts, EXPAND_SIZE * sizeof(double));
    //assert(total_num_consts == curr_quad);

    /*fprintf(stderr,"expand_num_consts\n");
    double *_num_consts;
    _num_consts = malloc(EXPAND_SIZE * sizeof(_num_consts) + total_num_consts);

    memset(_num_consts, 0, sizeof(_num_consts));

    if (num_consts)
    {
        memcpy(_num_consts, num_consts, total_num_consts * sizeof(num_consts));
        free(num_consts);
    }
    num_consts = _num_consts;*/
    //total_num_consts += EXPAND_SIZE;
}
void expand_string_consts()
{
    //assert(total_num_consts == curr_quad);
    string_consts = realloc(string_consts, sizeof(*string_consts) * (total_string_consts + EXPAND_SIZE));
    //total_string_consts += EXPAND_SIZE;
}
void expand_named_lib_funcs()
{
    named_lib_funcs = realloc(named_lib_funcs, sizeof(*named_lib_funcs) * (total_named_lib_funcs + EXPAND_SIZE));
    // total_named_lib_funcs += EXPAND_SIZE;
}
void expand_user_funcs()
{
    user_funcs = realloc(user_funcs, EXPAND_SIZE * sizeof(userfunc));
    //assert(total_num_consts == curr_quad);
    /* userfunc *_user_funcs;
    _user_funcs = malloc(EXPAND_SIZE * sizeof(_user_funcs) + total_user_funcs);
    memset(_user_funcs, 0, sizeof(user_funcs));
    if (user_funcs)
    {
        memcpy(_user_funcs, user_funcs, total_user_funcs * sizeof(user_funcs));
        free(user_funcs);
    }
    user_funcs = _user_funcs;*/
    //total_user_funcs += EXPAND_SIZE;
}

void make_operand(expr *e, vmarg *arg)
{
    if (e == NULL)
    {
        //fprintf(stderr, "NULL IN MAKE_OPERNAD\n");
        arg->type = -1;
        arg->val = 0;
        return;
    }
    if (e->sym && e->sym->value.varVal)
        fprintf(stderr, "%s ",
                e->sym->value.varVal->name);
    fprintf(stderr, "e->type: %d\n", e->type);

    switch (e->type)
    {
    case var_e:
    case assignexpr_e:
    case tableitem_e:
    case arithexpr_e:
    case boolexpr_e:
    case newtable_e:
    {
        //fprintf(stderr, "vars,etc...\n");

        assert(e->sym);
        arg->name = e->sym->value.varVal->name;
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
        break;
    }
    case constbool_e:
    {
        //fprintf(stderr, "const bool\n");

        arg->val = e->boolConst;
        arg->type = bool_a;
        break;
    }
    case conststring_e:
    {
        //fprintf(stderr, "const str\n");

        arg->val = consts_new_string(e->strConst);
        arg->type = string_a;
        break;
    }
    case constdouble_e:
    {
        //fprintf(stderr, "const dobule\n");
        arg->val = consts_new_number(e->doubleConst);
        arg->type = number_a;
        break;
    }
    case nil_e:
        arg->type = nil_a;
        break;
    case programfunc_e:
    {
        arg->type = userfunc_a;
        arg->name = strdup(e->sym->value.funcVal->name);
        fprintf(stderr, "program func\n");
        arg->val = userfuncs_new_func(e->sym);
        //fprintf(stderr, "arg->val: %d\n", arg->val);
        break;
        //another way exists
    }
    case libraryfunc_e:
    {
        arg->type = libfunc_a;
        arg->name = e->sym->value.funcVal->name;
        arg->val = libfuncs_new_used(e->sym->value.funcVal->name);
        break;
    }

    default:
        arg->type = -1;
        break;
        //assert(0);
    }
}

unsigned consts_new_number(double number)
{
    fprintf(stderr, "consts_new_number\n");

    if (total_num_consts == 0)
    {
        fprintf(stderr, "alloc num_consts\n");
        num_consts = malloc(sizeof(double) * EXPAND_SIZE);
    }
    else if (total_num_consts % EXPAND_SIZE == 0)
    {
        expand_num_consts();
    }

    num_consts[total_num_consts++] = number;
    //fprintf(stderr, "END OF consts_new_number\n");

    return total_num_consts - 1;
}

unsigned consts_new_string(char *str)
{
    fprintf(stderr, "consts_new_string\n");
    if (total_string_consts == 0)
    {
        string_consts = malloc(sizeof(char) * EXPAND_SIZE);
    }
    if (total_num_consts % EXPAND_SIZE == 0)
        expand_string_consts();
    string_consts[total_string_consts++] = strdup(str);
    return total_string_consts - 1;
}

unsigned libfuncs_new_used(const char *s)
{
    if (total_named_lib_funcs == 0)
    {
        named_lib_funcs = malloc(sizeof(char) * EXPAND_SIZE);
    }
    else if (total_named_lib_funcs % EXPAND_SIZE == 0)
        expand_named_lib_funcs();
    named_lib_funcs[total_named_lib_funcs++] = strdup(s);
    return total_named_lib_funcs - 1;
}

unsigned userfuncs_new_func(SymbolTableEntry *sym)
{
    /* if (total_user_funcs == 0)
    {
        user_funcs = malloc(sizeof(userfunc) * EXPAND_SIZE);
    }
    if (total_user_funcs % EXPAND_SIZE == 0)
        expand_user_funcs();*/
    /*userfunc _user_func;
    memset(&_user_func, 0, sizeof(userfunc));
    _user_func.id = strdup(sym->value.funcVal->name);
    user_funcs[total_user_funcs++] = _user_func;*/
    return total_user_funcs - 1;
}

void make_retvaloperand(vmarg *arg)
{
    arg->type = retval_a;
}

struct func_stack *func_stack_root = {0};
SymbolTableEntry *pop_func_start_stack()
{
    SymbolTableEntry *tmp;
    if (func_stack_root == NULL)
    {
        return 0;
    }
    tmp = func_stack_root->sym;
    func_stack_root = func_stack_root->next;
    return tmp;
}

int push_func_start_stack(SymbolTableEntry *entry)
{
    func_stack *stack_entry = malloc(sizeof(func_stack));
    stack_entry->sym = entry;
    stack_entry->next = NULL;
    if (func_stack_root == NULL)
    {
        func_stack_root = stack_entry;
        return 1;
    }

    stack_entry->next = func_stack_root;
    func_stack_root = stack_entry;
    return 1;
}

SymbolTableEntry *top_func_start_stack()
{
    if (func_stack_root != NULL)
    {
        return func_stack_root->sym;
    }
    else
    {
        return NULL;
    }
}

void generate_funcstart(quad *quad)
{

    instruction t;
    memset(&t, 0, sizeof(t));
    reset_instruction(&t);
    t.srcLine=quad->line;

    t.result.type = 0;
    t.opcode = jump_v;
    //make_operand(quad->result, &t.result);
    emit_instr(t);
    SymbolTableEntry *f;
    f = quad->result->sym;
    f->taddress = nextinstructionlabel();
    f->value.funcVal->func_enter_jump = nextinstructionlabel() - 1;
    quad->taddress = nextinstructionlabel();

    //fprintf(stderr, "total locals  : %u\n", f->value.funcVal->total_locals);

    user_funcs_add(f->value.funcVal->name, f->taddress, f->value.funcVal->total_locals);
    push_func_start_stack(f);
    t.opcode = funcenter_v;
    make_operand(quad->result, &t.result);
    emit_instr(t);
}
void generate_return(quad *quad)
{
    quad->taddress = nextinstructionlabel();

    instruction t;
    reset_instruction(&t);
    t.srcLine=quad->line;

    t.opcode = assign_v;
    make_retvaloperand(&t.result);
    make_operand(quad->arg1, &t.arg1);
    emit_instr(t);

    SymbolTableEntry *f = top_func_start_stack();

    if (f && f->value.funcVal != NULL)
    {

        append_ret_list(&f->value.funcVal->returnList, nextinstructionlabel());
    }
    t.opcode = jump_v;

    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    emit_instr(t);
}

void append_ret_list(return_list **head, unsigned address)
{

    return_list *tmp = *head, *entry;
    entry = malloc(sizeof(return_list));
    entry->address = address;
    entry->next = NULL;

    if (*head == NULL)
    {
        *head = entry;

        return;
    }
    while (tmp->next != NULL)
    {

        tmp = tmp->next;
    }
    tmp->next = entry;
}

void backpatch_return_list(return_list *head, unsigned address)
{
    return_list *tmp = head;
    if (head == NULL)
    {

        return;
    }
    while (tmp != NULL)
    {
        fprintf(stderr, "%d--\n", address);

        instructions[tmp->address].result.val = address;
        tmp->address = address;
        tmp = tmp->next;
    }
}
void generate_funcend(quad *quad)
{
    SymbolTableEntry *f;
    f = pop_func_start_stack();
    if (f->value.funcVal != NULL)
        backpatch_return_list(f->value.funcVal->returnList, nextinstructionlabel());
    quad->taddress = nextinstructionlabel();
    instruction t;
    reset_instruction(&t);
    t.srcLine=quad->line;

    t.opcode = funcexit_v;
    make_operand(quad->result, &t.result);
    emit_instr(t);
    //fprintf(stderr,"jump before enter %u\n", f->value.funcVal->func_enter_jump);
    instructions[f->value.funcVal->func_enter_jump].result.val = nextinstructionlabel();
}

unsigned user_funcs_add(const char *id, unsigned tadress, unsigned total_locals)
{
    if (total_user_funcs == 0)
    {
        user_funcs = malloc(EXPAND_SIZE * sizeof(userfunc));
    }
    else if (total_user_funcs % EXPAND_SIZE == 0)
        expand_user_funcs();
    // userfunc _user_func;
    // _user_func.id = strdup(id);
    //_user_func.address = tadress;
    //_user_func.localSize = total_locals;
    //user_funcs[total_user_funcs++] = _user_func;

    user_funcs[total_user_funcs].id = strdup(id);
    user_funcs[total_user_funcs].address = tadress;
    user_funcs[total_user_funcs].localSize = total_locals;
    total_user_funcs++;
    //fprintf(stderr, "total locals  : %u\n", user_funcs[total_user_funcs].localSize);

    return total_user_funcs - 1;
}

void patch_incomplete_jumps()
{
    incomplete_jump *tmp = ij_head;
    while (tmp != NULL)
    {
        if (tmp->iaddress == curr_quad)
        {
            instructions[tmp->instr_no].result.val = curr_instr;
        }
        else
        {
            instructions[tmp->instr_no].result.val = quads[tmp->iaddress].taddress;
        }
        fprintf(stderr, "%u->", tmp->instr_no);
        tmp = tmp->next;
    }
    fprintf(stderr, "\n");
}

void print_vmarg_text(vmarg *arg1, FILE *instr_file)
{
    fprintf(instr_file, "type: %u", arg1->type);

    if (arg1->type < 10 && arg1->type >= 0)
        fprintf(instr_file, "(%s), ", vmarg_str[arg1->type]);

    fprintf(instr_file, " val: %u", arg1->val);
    if (arg1->type != 0)
    {

        if (arg1->name != NULL)
        {
            fprintf(instr_file, ":%s", arg1->name);
        }
        else
        {
            if (arg1->type == bool_a)
            {
                if (arg1->val == 1)
                {
                    fprintf(instr_file, ":%s\t", "true");
                }
                else if (arg1->val == 0)

                {

                    fprintf(instr_file, ":%s\t", "false");
                }
            }
            else if (arg1->type == number_a)
            {
                fprintf(instr_file, ":%f\t", num_consts[arg1->val]);
            }
            else if (arg1->type == string_a)
            {
                fprintf(instr_file, ":\"%s\"\t", string_consts[arg1->val]);
            }
            else if (arg1->type == userfunc_a)
            {
                //fprintf(stderr, "offset  %u\n", arg1->val);
                fprintf(instr_file, ":\"%s\"\t", user_funcs[arg1->val].id);
            }
            else if (arg1->type == libfunc_a)
            {
                fprintf(instr_file, ":%s\t", named_lib_funcs[arg1->val]);
            }
            else if (arg1->type == nil_a)
            {
                fprintf(instr_file, ":%s\t", "nil");
            }
        }
    }

    fprintf(instr_file, "\t");
}
void print_text_file(vmopcode op, vmarg *arg1, vmarg *arg2, vmarg *result, unsigned curr_no, FILE *instr_file, unsigned line)
{
    char *opcode_str;

    if (instr_file == NULL)
    {
        perror("Error opening quads file.");
        return;
    }

    fprintf(instr_file, "#%u\t", curr_no);
    opcode_str = vm_opcode_to_string(op);
    fprintf(instr_file, "%s\t", opcode_str);

    if (result->type != -1)
    {

        fprintf(instr_file, "\t result: ");

        print_vmarg_text(result, instr_file);
    }

    if (arg1->type != -1)
    {
        fprintf(instr_file, "\targ1: ");
        print_vmarg_text(arg1, instr_file);
    }

    if (arg2->type != -1)
    {
        fprintf(instr_file, "\targ2: ");

        print_vmarg_text(arg2, instr_file);
    }
    fprintf(instr_file, "line : %u\n", line);

    fprintf(instr_file, "\n");
}

//opcode,type,offset,value,
void print_instructions_analytics(vmopcode op, vmarg *arg1, vmarg *arg2, vmarg *result, unsigned curr_no, FILE *instr_file)
{
    char *opcode_str;

    if (instr_file == NULL)
    {
        perror("Error opening quads file.");
        return;
    }

    fprintf(instr_file, "#%u\t", curr_no);
    opcode_str = vm_opcode_to_string(op);

    fprintf(instr_file, "<opcode , ");
    fprintf(instr_file, "%s>\t", opcode_str);
    fprintf(instr_file, "<result , ");
    if (!print_by_type_vmarg(result, instr_file))
    {

        fprintf(instr_file, " >\t");
    }

    fprintf(instr_file, "<arg1 , ");

    if (!print_by_type_vmarg(arg1, instr_file))
    {
        fprintf(instr_file, " >\t");
    }
    fprintf(instr_file, "<arg2 , ");

    if (!print_by_type_vmarg(arg2, instr_file))
    {
        fprintf(instr_file, " >\t");
    }
    fprintf(instr_file, "\n");
}

void print_instructions(FILE *instr_file)
{
    fprintf(stderr, "%u\n", curr_instr);
    unsigned i = 1;
    while (i < curr_instr)
    {
        //if(quads[i].op==jump && quads[i].label==0) quads[i].label=1;
        //fprintf(stderr, "opcode:%s\n", vm_opcode_to_string(instructions[i].opcode));
        //print_instructions_analytics(instructions[i].opcode, &instructions[i].arg1, &instructions[i].arg2, &instructions[i].result, i, instr_file);
        print_text_file(instructions[i].opcode, &instructions[i].arg1, &instructions[i].arg2, &instructions[i].result, i, instr_file,instructions[i].srcLine);

        i++;
    }
}
int print_by_type_vmarg(vmarg *_instr, FILE *instr_file)
{
    if (_instr == NULL)
    {
        return 0;
    }
    if (_instr->type == bool_a)
    {
        if (_instr->val == 1)
        {
            fprintf(instr_file, "%s>\t", "true");
        }
        else if (_instr->val == 0)

        {

            fprintf(instr_file, "%s>\t", "false");
        }
    }
    else if (_instr->type == number_a)
    {
        fprintf(instr_file, "%f>\t", num_consts[_instr->val]);
        return 1;
    }
    else if (_instr->type == string_a)
    {
        fprintf(instr_file, "\"%s\">\t", string_consts[_instr->val]);
        return 1;
    }
    else if (_instr->type == userfunc_a)
    {
        //fprintf(stderr, "offset  %u\n", _instr->val);
        fprintf(instr_file, "\"%s\">\t", user_funcs[_instr->val].id);
        return 1;
    }
    else if (_instr->type == libfunc_a)
    {
        fprintf(instr_file, "%s>\t", named_lib_funcs[_instr->val]);
        return 1;
    }
    else if (_instr->type == nil_a)
    {
        fprintf(instr_file, "%s>\t", "nil");
        return 1;
    }
    else if (_instr->type == label_a)
    {
        //fprintf(stderr, "lalal\n");
        fprintf(instr_file, "%u>\t", _instr->val);
        return 1;
    }
    return 0;
}

char *vm_opcode_to_string(vmopcode op)
{
    switch (op)
    {
    case assign_v:
        return "ASSIGN";
    case funcenter_v:
        return "FUNCENTER";
    case funcexit_v:
        return "FUNCEXIT";
    case add_v:
        return "ADD";

    case mul_v:
        return "MUL";

    case sub_v:
        return "SUB";
    case div_v:
        return "DIV";
    case mod_v:
        return "MOD";
    case and_v:
        return "AND";
    case or_v:
        return "OR";
    case not_v:
        return "NOT";
    case jeq_v:
        return "IF_EQUALS";
    case jne_v:
        return "IF_NOT_EQUALS";
    case jle_v:
        return "IF_LESS_OR_EQUAL";
    case jge_v:
        return "IF_GREATER_OR_EQUAL";
    case jlt_v:
        return "IF_LESS";
    case jgt_v:
        return "IF_GREATER";
    case call_v:
        return "CALLFUNC";
    case pusharg_v:
        return "PUSHARG";
    case return_v:
        return "RETURN";
    case newtable_v:
        return "TABLE_CREATE";
    case tablegetelem_v:
        return "TABLE_GET_ELEM";
    case tablesetelem_v:
        return "TABLE_SET_ELEM";
    case jump_v:
        return "JUMP";
    default:
        return "WRONG";
    }
}