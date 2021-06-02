#pragma once
#include "../../vm_instructions_common.h"
#include "../vm.h"

extern void execute_assign(instruction *);
extern void execute_nop(instruction *);
extern void execute_and(instruction *);
extern void execute_or(instruction *);
extern void execute_not(instruction *);
extern void execute_return(instruction *);
extern void execute_get_ret_val(instruction *);
extern void execute_jump(instruction *);





