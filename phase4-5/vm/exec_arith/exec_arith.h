#pragma once

#include "../../vm_instructions_common.h"


#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic
#define execute_uminus execute_arithmetic



void execute_arithmetic(instruction *instr);
/*
void execute_add(instruction *);
void execute_sub(instruction *);
void execute_mul(instruction *);
void execute_div(instruction *);
void execute_mod(instruction *);
void execute_uminus(instruction *);*/
