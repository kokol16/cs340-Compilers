#include "../quads/quads.h"
#include "../vm_instructions_common.h"

typedef struct incomplete_jump
{
    unsigned instr_no;            //the jump instruction number
    unsigned iaddress;            //the i-code jump-target address
    struct incomplete_jump *next; //linked list
} incomplete_jump;

extern incomplete_jump *ij_head;

extern unsigned ij_total;
instruction *instructions;
extern unsigned curr_instr;
void expand_instr();
void add_incomplete_jump(unsigned intr_no, unsigned iaddress);

double *num_consts;
extern unsigned total_num_consts;
char **string_consts;
extern unsigned total_string_consts;
char **named_lib_funcs;
extern unsigned total_named_lib_funcs;
struct userfunc *user_funcs;
extern unsigned total_user_funcs;

#define EXPAND_SIZE 1024

#define CURR_SIZE (total * sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(quad) + CURR_SIZE)

unsigned consts_new_number(double number);
unsigned consts_new_string(char *str);
unsigned libfuncs_new_used(const char *s);
unsigned userfuncs_new_func(SymbolTableEntry *sym);
void make_operand(expr *e, vmarg *arg);
void generate(vmopcode opcode, quad *quad);

void expand_incomplete_instr();
void emit_instr(instruction t);
void make_retvaloperand(vmarg *arg);

typedef struct func_stack
{
    SymbolTableEntry *sym;
    struct func_stack *next;
} func_stack;

extern struct func_stack *func_stack_root;

void generate_ADD(quad *quad);
void generate_SUB(quad *quad);
void generate_MUL(quad *quad);
void generate_DIV(quad *quad);
void generate_MOD(quad *quad);
void generate_NEWTABLE(quad *quad);
void generate_TABLEGETELEM(quad *quad);
void generate_TABLESETELEM(quad *quad);
void generate_ASSIGN(quad *quad);

void generate_NOP();
void generate_relational(vmopcode op, quad *quad);

void reset_operand(vmarg *arg);

void generate_NOT(quad *quad);
void generate_AND(quad *quad);

void generate_JUMP(quad *quad);
void generate_IF_EQ(quad *quad);
void generate_IF_NOTEQ(quad *quad);
void generate_IF_GREATER(quad *quad);
void generate_IF_GREATEREQ(quad *quad);
void generate_IF_LESS(quad *quad);
void generate_IF_LESSEQ(quad *quad);

void generate_OR(quad *quad);

void generate_PARAM(quad *quad);
void generate_CALL(quad *quad);
void generate_GETRETVAL(quad *quad);
void expand_incomplete_instr();
void expand_num_consts();
void expand_string_consts();
void expand_named_lib_funcs();
void expand_user_funcs();
void generate_funcend(quad *quad);
void generate_return(quad *quad);
void generate_funcstart(quad *quad);
void generate_UMINUS(quad *quad);

void append_ret_list(return_list **head, unsigned address);
unsigned user_funcs_add(const char *id, unsigned tadress, unsigned total_locals);

typedef void (*generator_func_t)(quad *);

extern generator_func_t generators[];
void print_instructions(FILE *instr_file);
int print_by_type_vmarg(vmarg *_instr, FILE *instr_file);
char *vm_opcode_to_string(vmopcode op);
void patch_incomplete_jumps();
void reset_instruction(instruction *t);
