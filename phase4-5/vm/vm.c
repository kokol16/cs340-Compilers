#include "vm.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../general_functions/lib.h"
#define MAGIC_NUMBER 340200501

unsigned char execution_finished = 0;
unsigned pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;
instruction *code = NULL;

unsigned totalActuals = 0;
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

unsigned curr_instr;
instruction *instructions;

typedef void (*execute_func_t)(instruction *);
execute_func_t executeFuncs[] = {
    execute_assign,       //0
    execute_mul,          //1
    execute_uminus,       //2
    execute_add,          //3
    execute_sub,          //4
    execute_div,          //5
    execute_mod,          //6
    execute_and,          //7
    execute_or,           //8
    execute_not,          //9
    execute_jeq,          //10
    execute_jne,          //11
    execute_jle,          //12
    execute_jgt,          //13
    execute_jlt,          //14
    execute_jgt,          //15
    execute_call,         //16
    execute_pusharg,      //17
    execute_return,       //18
    execute_get_ret_val,  //19
    execute_funcenter,    //20
    execute_funcexit,     //21
    execute_newtable,     //22
    execute_tablegetelem, //23
    execute_tablesetelem, //24
    execute_jump,         //25
    execute_nop,          //26

};

avm_memcell *avm_translate_operand(vmarg *arg, avm_memcell *reg)
{
    switch (arg->type)
    {
    case global_a:
        return &stack[AVM_STACK_SIZE - 1 - arg->val];
    case local_a:
        return &stack[topsp - arg->val];
    case formal_a:
        return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
    case retval_a:
        return &retval;
    case number_a:
    {
        reg->type = number_m;
        reg->data.numVal = consts_number[arg->val];
        return reg;
    }
    case string_a:
    {
        reg->type = string_m;
        reg->data.strVal = strdup(consts_string[arg->val]);
        return reg;
    }
    case bool_a:
    {
        reg->type = bool_m;
        reg->data.boolVal = arg->val;
        return reg;
    }
    case nil_a:
    {
        reg->type = nil_m;
        return reg;
    }
    case userfunc_a:
    {
        reg->type = userfunc_m;
        reg->data.funVal = arg->val;
        return reg;
    }
    case libfunc_a:
    {
        reg->type = libfunc_m;
        reg->data.libfuncVal = lib_funcs[arg->val];
        return reg;
    }
    default:
        assert(0);
    }
}

void avm_ini_stack(void)
{
    unsigned i = 0;
    for (i = 0; i < AVM_STACK_SIZE; ++i)
    {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

int main()
{
    fprintf(stderr, "===========VM============\n");
    read_binary_file();
}

void read_binary_file()
{
    unsigned magic_number;
    FILE *fp;

    fp = fopen("target_code.abc", "rb"); // r for read, b for binary

    fread(&magic_number, sizeof(magic_number), 1, fp);
    fprintf(stderr, "magic number %u\n", magic_number);
    if (MAGIC_NUMBER != magic_number)
        return;
    fread(&total_numbers, sizeof(total_numbers), 1, fp);
    fprintf(stderr, "total number %u\n", total_numbers);

    consts_number = malloc(sizeof(double) * total_numbers);

    fread(consts_number, sizeof(double), total_numbers, fp);

    fread(&total_strings, sizeof(total_strings), 1, fp);

    fprintf(stderr, "total string %u\n", total_strings);

    consts_string = malloc(sizeof(char) * total_strings);
    int i = 0;
    int size = 0;

    //10 5 "lala" 6 "ofsafdf"
    for (i = 0; i < total_strings; i++)
    {
        fread(&size, sizeof(size), 1, fp);
        consts_string[i] = malloc(sizeof(char) * size);
        fread(consts_string[i], sizeof(char), size, fp);
    }

    fread(&total_user_funcs, sizeof(total_user_funcs), 1, fp);

    fprintf(stderr, "total user funcs %u\n", total_user_funcs);

    user_funcs = malloc(sizeof(struct userfunc *) * total_user_funcs);

    //functions
    for (i = 0; i < total_user_funcs; i++)
    {
        size = 0;
        fread(&size, sizeof(size), 1, fp);

        user_funcs[i].id = malloc(sizeof(char) * size);
        char *str;
        fread(str, sizeof(char), size, fp);
        user_funcs[i].id = strdup(str);
        fread(&user_funcs[i].address, sizeof(user_funcs[i].address), 1, fp);
        fread(&user_funcs[i].localSize, sizeof(user_funcs[i].localSize), 1, fp);

        /*fprintf(stderr, "=========\n");
        fprintf(stderr, "id: %s\n", user_funcs[i].id);
        fprintf(stderr, "localsize: %u\n", user_funcs[i].localSize);
        fprintf(stderr, "adress: %u\n", user_funcs[i].address);
        fprintf(stderr, "=========\n");*/
    }
    fprintf(stderr, "%s\n", user_funcs[0].id);

    for (i = 0; i < total_user_funcs; i++)
    {
        fprintf(stderr, "%s\n", user_funcs[i].id);
    }
    //10 5 "lala" 6 "ofsafdf"

    fread(&total_lib_funcs, sizeof(total_lib_funcs), 1, fp);
    fprintf(stderr, "total lib funcs  %u\n", total_lib_funcs);

    lib_funcs = malloc(sizeof(char) * total_lib_funcs);
    for (i = 0; i < total_lib_funcs; i++)
    {
        fread(&size, sizeof(size), 1, fp);
        lib_funcs[i] = malloc(sizeof(char) * size);
        fread(lib_funcs[i], sizeof(char), size, fp);
    }

    //instructions
    fread(&curr_instr, sizeof(curr_instr), 1, fp);
    instructions = malloc(sizeof(instruction) * curr_instr);
    FILE *fp2;
    fp2 = fopen("test_vm_instructions", "w+");
    for (i = 0; i < curr_instr; i++)
    {
        fread(&instructions[i].opcode, sizeof(vmopcode), 1, fp);

        fread(&instructions[i].result.type, sizeof(vmarg), 1, fp);
        fread(&instructions[i].result.val, sizeof(unsigned), 1, fp);

        fread(&instructions[i].arg1.type, sizeof(vmarg), 1, fp);
        fread(&instructions[i].arg1.val, sizeof(unsigned), 1, fp);

        fread(&instructions[i].arg2.type, sizeof(vmarg), 1, fp);
        fread(&instructions[i].arg2.val, sizeof(unsigned), 1, fp);
        print_text_file(instructions[i].opcode, &instructions[i].arg1, &instructions[i].arg2, &instructions[i].result, i + 1, fp2, instructions[i].srcLine);
    }

    for (i = 0; i < total_lib_funcs; i++)
    {
        fprintf(stderr, "%s\n", lib_funcs[i]);
    }
    for (i = 0; i < total_user_funcs; i++)
    {
        fprintf(stderr, "%s\n", user_funcs[i].id);
    }

    for (i = 0; i < total_strings; i++)
    {
        fprintf(stderr, "%s\n", consts_string[i]);
    }
    code = instructions;

    fclose(fp);
    fclose(fp2);
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

void print_vmarg_text(vmarg *arg1, FILE *instr_file)
{
    fprintf(instr_file, "type: %u", arg1->type);

    if (arg1->type < 10 && arg1->type >= 0)
        fprintf(instr_file, "(%s), ", vmarg_str[arg1->type]);

    fprintf(instr_file, " val: %u", arg1->val);
    if (arg1->type != 0)
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
            fprintf(instr_file, ":%f\t", consts_number[arg1->val]);
        }
        else if (arg1->type == string_a)
        {
            fprintf(instr_file, ":\"%s\"\t", consts_string[arg1->val]);
        }
        else if (arg1->type == userfunc_a)
        {
            // fprintf(stderr, "offset  %u\n", arg1->val);

            //if (arg1->val < total_user_funcs)
            fprintf(instr_file, ":\"%s\"\t", user_funcs[arg1->val].id);
        }
        else if (arg1->type == libfunc_a)
        {
            fprintf(instr_file, ":%s\t", lib_funcs[arg1->val]);
        }
        else if (arg1->type == nil_a)
        {
            fprintf(instr_file, ":%s\t", "nil");
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

void execute_cycle()
{
    if (execution_finished)
        return;
    else if (pc == AVM_ENDING_PC)
    {
        execution_finished = 1;
        return;
    }
    else
    {
        assert(pc < AVM_ENDING_PC);
        instruction *instr = code + pc;
        assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        if (instr->srcLine)
        {
            currLine = instr->srcLine;
        }
        unsigned oldPC = pc;
        (*executeFuncs[instr->opcode])(instr);
        if (pc == oldPC)
        {
            ++pc;
        }
    }
}

void avm_error(char *message, char *arg1, char *arg2)
{
    print_Red();
    if (arg2 != NULL)
    {
        fprintf(stderr, message, arg1, arg2);
    }
    else if (arg1 != NULL)
    {
        fprintf(stderr, message, arg1);
    }
    else
    {
        fprintf(stderr, message);
    }
    reset_Red();
    execution_finished = 1;
}

void avm_warning(char *message, char *arg1, char *arg2)
{
    print_Yellow();
    if (arg2 != NULL)
    {
        fprintf(stderr, message, arg1, arg2);
    }
    else if (arg1 != NULL)
    {
        fprintf(stderr, message, arg1);
    }
    else
    {
        fprintf(stderr, message);
    }
    reset_Yellow();
}