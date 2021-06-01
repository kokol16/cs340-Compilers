#include "vm.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
void avm_ini_stack(void)
{
    unsigned i = 0;
    for (i = 0; i < AVM_STACK_SIZE; ++i)
    {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
}

void avm_table_inc_ref_counter(avm_table *t)
{
    ++t->refCounter;
}
void avm_table_dec_ref_counter(avm_table *t)
{
    assert(t->refCounter > 0);
    if (!--t->refCounter)
    {
        avm_table_destroy(t);
    }
}
void avm_table_buckets_init(avm_table_bucket **p)
{
    unsigned i = 0;
    for (i = 0; i < AVM_TABLE_SIZE; ++i)
    {
        p[i] = (avm_table_bucket *)0;
    }
}

avm_table *avm_table_new()
{
    avm_table *t = malloc(sizeof(avm_table));
    AVM_WIPEOUT(t);
    t->refCounter = t->total = 0;
    avm_table_buckets_init(t->num_indexed);
    avm_table_buckets_init(t->bool_indexed);
    avm_table_buckets_init(t->str_indexed);
    avm_table_buckets_init(t->library_func_indexed);
    avm_table_buckets_init(t->user_func_indexed);
    return t;
}
void avm_memcell_clear(avm_memcell *m)
{
}
void avm_table_buckets_destroy(avm_table_bucket **p)
{
    unsigned i = 0;
    for (i = 0; i < AVM_TABLE_SIZE; ++i, ++p)
    {
        for (avm_table_bucket *b = *p; b;)
        {
            avm_table_bucket *del = b;
            b = b->next;
            avm_memcell_clear(&del->key);
            avm_memcell_clear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket *)0;
    }
}
void avm_table_destroy(avm_table *t)
{
    avm_table_buckets_destroy(t->str_indexed);
    avm_table_buckets_destroy(t->bool_indexed);
    avm_table_buckets_destroy(t->num_indexed);
    avm_table_buckets_destroy(t->library_func_indexed);
    avm_table_buckets_destroy(t->user_func_indexed);

    free(t);
}

int main()
{
    fprintf(stderr, "===========VM============\n");
    read_binary_file();
}
double *consts_number;
unsigned total_numbers;
char **consts_string;
unsigned total_strings;
unsigned total_user_funcs;
struct userfunc *user_funcs;
char **lib_funcs;
unsigned total_lib_funcs;

unsigned curr_instr;
instruction *instructions;
void read_binary_file()
{
    unsigned magic_number;
    FILE *fp;

    fp = fopen("target_code.abc", "rb"); // r for read, b for binary

    fread(&magic_number, sizeof(magic_number), 1, fp);
    fprintf(stderr, "magic number %u\n", magic_number);
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
        fread(user_funcs[i].id, sizeof(char), size, fp);
        fread(&user_funcs[i].address, sizeof(user_funcs[i].address), 1, fp);
        fread(&user_funcs[i].localSize, sizeof(user_funcs[i].localSize), 1, fp);
        fprintf(stderr, "i=: %d\n", i);

        fprintf(stderr, "id: %s\n", user_funcs[0].id);

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
        print_text_file(instructions[i].opcode, &instructions[i].arg1, &instructions[i].arg2, &instructions[i].result, i + 1, fp2);
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
            fprintf(stderr, "offset  %u\n", arg1->val);

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
void print_text_file(vmopcode op, vmarg *arg1, vmarg *arg2, vmarg *result, unsigned curr_no, FILE *instr_file)
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
    fprintf(instr_file, "\n");
}