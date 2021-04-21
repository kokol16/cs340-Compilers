#include"quads.h"
void expand()
{
    assert(total==curr_quad);
    quad * _quad;
    _quad=malloc(NEW_SIZE);
    if(_quad)
    {
        memcpy(_quad,quads,CURR_SIZE);
        free(quads);
    }
    quads= _quad;
    total+=EXPAND_SIZE;
}
void emit(iopcode op , expr * arg1 ,expr * arg2 , expr * result ,unsigned label ,unsigned line  )
{
    quad * _quad ;
    if(curr_quad == total)
    {
        expand();
    }
    _quad=quads+curr_quad++;
    _quad->arg1=arg1;
    _quad->arg2=arg2;
    _quad->result=result;
    _quad->label=label;
    _quad->line=line;
    
}