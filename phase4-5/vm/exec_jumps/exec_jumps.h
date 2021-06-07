#include "../../vm_instructions_common.h"

#define execute_jge execute_cmp
#define execute_jgt execute_cmp
#define execute_jle execute_cmp
#define execute_jlt execute_cmp



extern char *typeStrings[];

void execute_jeq(instruction *instr);
void execute_jne(instruction *instr);


void execute_cmp(instruction *instr);