#include "quads.h"

quad *quads = NULL;
unsigned total = 0;
unsigned int curr_quad = 0;
int temp_counter = 0;
char *newtempname()
{
    char *tmp_name;
    int counter_str_size;
    counter_str_size = snprintf(NULL, 0, "%u", temp_counter);
    tmp_name = malloc(sizeof(char) * (counter_str_size + 2));
    memcpy(tmp_name, "t", 1);
    snprintf(tmp_name + 1, counter_str_size + 1, "%u", temp_counter);
}
void resettemp()
{
    temp_counter = 0;
}
int new_temp(SymbolTable *symbolTable)
{
    char *name = newtempname();
    SymbolTableEntry *bucket;
    Variable *var;
    if (temp_counter == 0)
    {
        find_bucket_by_scope_and_name(symbolTable, name, scope);
    }
    else
    {
        var = create_var(name, scope, yylineno);
        if (scope != 0)
            bucket = create_bucket_var(1, var, LOCAL);
        else
            bucket = create_bucket_var(1, var, GLOBAL);
        symbolTable_insert(symbolTable, bucket);
    }

    ++temp_counter;

    /* sym = lookup(name, currscope());
    if sym
        = nil then return newsymbol(name);
    else
        return sym;
        */
}
expr *lvalue_expr(SymbolTableEntry *bucket)
{
    assert(bucket);
    expr *_expr = malloc(sizeof(expr));
    memset(_expr, 0, sizeof(expr));
    _expr->next = NULL;
    _expr->sym = bucket;
    switch (bucket->type)
    {
    case GLOBAL:
        _expr->type = var_e;
        break;
    case LOCAL:
        _expr->type = var_e;
        break;
    case FORMAL:
        _expr->type = var_e;
        break;
    case LIBFUNC:
        _expr->type = libraryfunc_e;
        break;
    case USERFUNC:
        _expr->type = programfunc_e;
        break;
    default:
        assert(0);
    }
    return _expr;
}

void expand()
{
    assert(total == curr_quad);
    quad *_quad;
    _quad = malloc(NEW_SIZE);
    if (_quad)
    {
        memcpy(_quad, quads, CURR_SIZE);
        free(quads);
    }
    quads = _quad;
    total += EXPAND_SIZE;
}
void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line)
{
    quad *_quad;
    if (curr_quad == total)
    {
        expand();
    }
    _quad = quads + curr_quad++;
    _quad->arg1 = arg1;
    _quad->arg2 = arg2;
    _quad->result = result;
    _quad->label = label;
    _quad->line = line;
    print_quad(op, arg1, arg2, result, label, line);
}

unsigned next_quad_label()
{
    return curr_quad;
}
void patch_label(unsigned int quad_no, unsigned label)
{
    assert(quad_no < curr_quad);
    quads[quad_no].label = label;
}

void print_quad(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned label, unsigned line)
{
    char *opcode_str;
    FILE *quad_file = fopen("quads.txt", "a+");
    if (quad_file == NULL)
    {
        perror("Error opening quads file.");
        return;
    }
    fprintf(quad_file, "%u:\t", label);
    opcode_str = opcode_to_string(op);
    fprintf(quad_file, "%s ", opcode_str);
    if (arg1->type == programfunc_e)
    {
        fprintf(quad_file, "%s\n", arg1->sym->value.funcVal->name);
    }
    fclose(quad_file);
}

char *opcode_to_string(iopcode op)
{
    switch (op)
    {
    case funcstart:
        return "FUNCSTART";
    case funcend:
        return "FUNCEND";
    case add:
        return "ADD";

    case mul:
        return "MUL";
    case uminus:
        return "UMINUS";
    case sub:
        return "SUB";
    case _div:
        return "DIV";
    case mod:
        return "MOD";
    case and:
        return "AND";
    case or:
        return "OR";
    case not:
        return "NOT";
    case if_eq:
        return "IF_EQUALS";
    case if_noteq:
        return "IF_NOT_EQUALS";
    case if_lesseq:
        return "IF_LESS_OR_EQUAL";
    case if_greatereq:
        return "IF_GREATER_OR_EQUAL";
    case if_less:
        return "IF_LESS";
    case if_greater:
        return "IF_GREATER";
    case call:
        return "CALL";
    case param:
        return "PARAM";
    case ret:
        return "RETURN";
    case getretval:
        return "GET_RETURN_VALUE";
    case tablecreate:
        return "TABLE_CREATE";
    case tablegetelem:
        return "TABLE_GET_ELEMENT";
    case tablesetelem:
        return "TABLE_SET_ELEMENT";
    }
}