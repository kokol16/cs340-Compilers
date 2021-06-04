#pragma once 
#include "../../vm_instructions_common.h"

void execute_call(instruction *);
void execute_pusharg(instruction *);
void execute_funcexit(instruction *);
void execute_funcenter(instruction *);
void libfunc_print();
void libfunc_typeof();
typedef void (*library_func_t)(void);

void avm_registerlibfunc(char *id, library_func_t addr);

typedef struct map_lib_funcs
{
    char *id;
    library_func_t func;
    struct map_lib_funcs *next;

} map_lib_funcs;
extern struct map_lib_funcs *root_lib_funcs;
