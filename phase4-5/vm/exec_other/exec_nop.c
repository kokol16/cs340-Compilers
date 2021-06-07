#include "exec_other.h"
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

void execute_nop(instruction *instr) {}

void execute_and(instruction *instr) {}

void execute_or(instruction *instr) {}

void execute_not(instruction *instr) {}

void execute_return(instruction *instr) {}

void execute_get_ret_val(instruction *instr) {}

void execute_jump(instruction *instr)
{
    pc = instr->result.val ;
    fprintf(stderr, "jump to %u\n", pc);
}