#include "quads.h"

quad *quads = NULL;
unsigned total = 0;
unsigned int curr_quad = 0;
int temp_counter = 0;
int found_compile_error = 0;
#define width 20
#define EQUALS_PRINT 125

SymbolTable *symbolTable;
void print_quad_analytic(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned curr_no, unsigned label, unsigned line, FILE *quad_file)
{
    char *opcode_str;

    if (quad_file == NULL)
    {
        perror("Error opening quads file.");
        return;
    }

    fprintf(quad_file, "#%-*u", width, curr_no);
    opcode_str = opcode_to_string(op);
    fprintf(quad_file, "%-*s", width, opcode_str);

    if (result != NULL)
    {
        if (!print_by_type(result, quad_file))
        {
            if (result->sym != NULL && result->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%-*s\t", width, result->sym->value.varVal->name);
            }
            else if (result->sym != NULL)
            {

                fprintf(quad_file, "%-*s\t", width, result->sym->value.funcVal->name);
            }
        }
    }
    else
    {
        fprintf(quad_file, "%-*s", width, "");
    }
    if (arg1 != NULL)
    {

        if (!print_by_type(arg1, quad_file))
        {

            if (arg1->sym != NULL && arg1->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%-*s", width, arg1->sym->value.varVal->name);
            }
            else if (arg1->sym != NULL)
            {

                fprintf(quad_file, "%-*s", width, arg1->sym->value.funcVal->name);
            }
        }
    }
    else
    {
        fprintf(quad_file, "%-*s", width, "");
    }
    if (arg2 != NULL)
    {
        if (!print_by_type(arg2, quad_file))
        {
            if (arg2->sym != NULL && arg2->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%-*s", width, arg2->sym->value.varVal->name);
            }
            else if (arg2->sym != NULL)
            {
                fprintf(quad_file, "%-*s\t", width, arg2->sym->value.funcVal->name);
            }
        }
    }
    else
    {
        fprintf(quad_file, "%-*s", width, "");
    }

    if (label != 0)
    {
        fprintf(quad_file, "%-*u", width, label);
    }
    else
    {
        fprintf(quad_file, "%-*s", width, "");
    }
    fprintf(quad_file, "%-*d\n", width, line);
    generate_eq_eq(quad_file, EQUALS_PRINT);
}

void print_quad_analytic_2nd_try(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned curr_no, unsigned label, unsigned line, FILE *quad_file)
{
    char *opcode_str;

    if (quad_file == NULL)
    {
        perror("Error opening quads file.");
        return;
    }

    fprintf(quad_file, "#%u\t", curr_no);
    opcode_str = opcode_to_string(op);
    
    fprintf(quad_file, "<opcode , ");
    fprintf(quad_file, "%s>\t", opcode_str);

    fprintf(quad_file, "<result , ");
    if (result != NULL)
    {
        if (!print_by_type(result, quad_file))
        {
            if (result->sym != NULL && result->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%s >\t", result->sym->value.varVal->name);
            }
            else if (result->sym != NULL)
            {

                fprintf(quad_file, "%s >\t", result->sym->value.funcVal->name);
            }
        }
    }
    else
    {
        fprintf(quad_file, "%s", ">\t");
    }
    fprintf(quad_file, "<arg1 , ");
    if (arg1 != NULL)
    {

        if (!print_by_type(arg1, quad_file))
        {

            if (arg1->sym != NULL && arg1->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%s >\t", arg1->sym->value.varVal->name);
            }
            else if (arg1->sym != NULL)
            {

                fprintf(quad_file, "%s >\t", arg1->sym->value.funcVal->name);
            }
        }
    }
    else
    {
        fprintf(quad_file, "%s", ">\t");
    }
    fprintf(quad_file, "<arg2 , ");
    if (arg2 != NULL)
    {
        if (!print_by_type(arg2, quad_file))
        {
            if (arg2->sym != NULL && arg2->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%s>\t", arg2->sym->value.varVal->name);
            }
            else if (arg2->sym != NULL)
            {
                fprintf(quad_file, "%s>\t", arg2->sym->value.funcVal->name);
            }
        }
    }
    else
    {
        fprintf(quad_file, "%s", ">\t");
    }
    fprintf(quad_file, "<label , ");

    if (label != 0)
    {    
        fprintf(quad_file, "%u>\t", label);
    }
    else
    {
        fprintf(quad_file, "%s>\t", "");
    }
    fprintf(quad_file, "<line , ");
    fprintf(quad_file, "%d>\n", line);
    generate_eq_eq(quad_file, EQUALS_PRINT);
}

void generate_eq_eq(FILE *quad_file, unsigned numb_of_eq)
{
    unsigned i = 0;
    for (i = 0; i < numb_of_eq; i++)
    {
        fprintf(quad_file, "=");
    }
    fprintf(quad_file, "\n");
}
void print_quads(FILE *quad_file)
{
    unsigned i = 1;
    /*fprintf(quad_file, "%-*s", width, "#QUAD");
    fprintf(quad_file, "%-*s", width, "opcode");
    fprintf(quad_file, "%-*s", width, "result");
    fprintf(quad_file, "%-*s", width, "arg1");
    fprintf(quad_file, "%-*s", width, "arg2");
    fprintf(quad_file, "%-*s", width, "label");
    fprintf(quad_file, "%-*s\n", width, "line");
    generate_eq_eq(quad_file, EQUALS_PRINT);*/

    while (i < curr_quad)
    {
        //if(quads[i].op==jump && quads[i].label==0) quads[i].label=1;
        //print_quad(quads[i].op, quads[i].arg1, quads[i].arg2, quads[i].result, quads[i].quad_no, quads[i].label, quads[i].line, quad_file);

        //print_quad_analytic(quads[i].op, quads[i].arg1, quads[i].arg2, quads[i].result, quads[i].quad_no, quads[i].label, quads[i].line, quad_file);
        print_quad_analytic_2nd_try(quads[i].op, quads[i].arg1, quads[i].arg2, quads[i].result, quads[i].quad_no, quads[i].label, quads[i].line, quad_file);

        i++;
    }
}
void make_truth_list(expr *s)
{
    s->truelist = 0;
    s->falselist = 0;
}

void make_stmt(stmt_t *s)
{
    s->breaklist = 0;
    s->contlist = 0;
}
void print_list(int list)
{
    while (list != 0 && list < curr_quad)
    {
        int next = quads[list].label;
        //fprintf(stderr, "%d-->", list);
        list = next;
    }
    //fprintf(stderr, "\n");
}
int newlist(int i)
{
    quads[i].label = 0;
    return i;
}

int mergelist(int l1, int l2)
{
    if (!l1)
        return l2;
    else if (!l2)
        return l1;
    else
    {
        int i = l1;
        while (quads[i].label)
        {
            i = quads[i].label;
        }

        quads[i].label = l2;
        return l1;
    }
}
void patchlist(int list, int label)
{
    //fprintf(stderr, "starting from %d\n", list);

    while (list != 0 && list < curr_quad)
    {
        int next = quads[list].label;
        quads[list].label = label;
        //fprintf(stderr, "%d-->", list);
        list = next;
    }
    //fprintf(stderr, "\n");
}

unsigned next_quad(void) { return curr_quad; }
void check_arith(expr *e, const char *context)
{
    if (e->type == constbool_e ||
        e->type == conststring_e ||
        e->type == nil_e ||
        e->type == newtable_e ||
        e->type == programfunc_e ||
        e->type == libraryfunc_e ||
        e->type == boolexpr_e)
    {
        fprintf(stderr, "Illegal expr used in %s\n", context);
        found_compile_error = 1;
    }
}
void print_indexed_list(indexed *head)
{
    indexed *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->left != NULL)
        {

            if (!print_by_type(tmp->left, stderr))
            {
                if (is_function(tmp->left->sym))
                {
                    if (tmp->left->sym != NULL && tmp->left->sym->value.varVal != NULL)

                        fprintf(stderr, "%s", tmp->left->sym->value.funcVal->name);
                }
                else
                {
                    if (tmp->left->sym != NULL && tmp->left->sym->value.varVal != NULL)

                        fprintf(stderr, "%s", tmp->left->sym->value.varVal->name);
                }
            }
        }
        if (tmp->right != NULL)
        {
            if (!print_by_type(tmp->right, stderr))
            {
                if (is_function(tmp->right->sym))
                {
                    if (tmp->right->sym != NULL && tmp->right->sym->value.varVal != NULL)
                        fprintf(stderr, " : %s\n", tmp->right->sym->value.varVal->name);
                }
                else
                {
                    if (tmp->right->sym != NULL && tmp->right->sym->value.varVal != NULL)
                        fprintf(stderr, " : %s\n", tmp->right->sym->value.varVal->name);
                }
            }
        }

        tmp = tmp->next;
    }
}

char *newtempname()
{
    char *tmp_name;
    int counter_str_size;
    counter_str_size = snprintf(NULL, 0, "%u", temp_counter);
    tmp_name = malloc(sizeof(char) * (counter_str_size + 3));
    memcpy(tmp_name, "_t", 2);
    snprintf(tmp_name + 2, counter_str_size + 1, "%u", temp_counter);
    return tmp_name;
}
void resettemp()
{
    temp_counter = 0;
}
SymbolTableEntry *new_temp(SymbolTable *symbolTable)
{
    char *name;
    SymbolTableEntry *bucket;
    Variable *var;
    name = newtempname();
    if (temp_counter == 0)
    {
        bucket = find_bucket_by_scope_and_name(symbolTable, name, scope);
        if (bucket == NULL)
        {
            var = create_var(name, scope, yylineno);
            if (scope != 0)
                bucket = create_bucket_var(1, var, LOCAL);
            else
                bucket = create_bucket_var(1, var, GLOBAL);
            symbolTable_insert(symbolTable, bucket);
        }
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
    return bucket;

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
    //fprintf(stderr, "expand()\n");
    _quad = malloc(NEW_SIZE);
    memset(_quad, 0, sizeof(_quad));
    if (_quad)
    {
        memcpy(_quad, quads, CURR_SIZE);
        free(quads);
    }
    quads = _quad;
    total += EXPAND_SIZE;
}
void emit(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned quad_no, unsigned label, unsigned line)
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
    _quad->quad_no = quad_no;

    _quad->label = label;
    _quad->line = line;
    _quad->op = op;

    //print_quad(op, arg1, arg2, result,quad_no, label, line);
}

unsigned next_quad_label()
{
    return curr_quad;
}
void patch_label(unsigned int quad_no, unsigned label)
{
    assert(quad_no < curr_quad);
    //assert(!quads[quad_no].label);
    quads[quad_no].label = label;
}

void print_quad(iopcode op, expr *arg1, expr *arg2, expr *result, unsigned curr_no, unsigned label, unsigned line, FILE *quad_file)
{
    char *opcode_str;

    if (quad_file == NULL)
    {
        perror("Error opening quads file.");
        return;
    }

    fprintf(quad_file, "%u:\t", curr_no);
    opcode_str = opcode_to_string(op);
    fprintf(quad_file, "%s ", opcode_str);

    //fprintf(stderr, "im in print %s\n",opcode_str);
    if (arg1 != NULL)
    {

        if (!print_by_type(arg1, quad_file))
        {

            if (arg1->sym != NULL && arg1->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%s\t", arg1->sym->value.varVal->name);
            }
            else if (arg1->sym != NULL)
            {

                fprintf(quad_file, "%s\t", arg1->sym->value.funcVal->name);
            }
        }
    }
    if (arg2 != NULL)
    {
        if (!print_by_type(arg2, quad_file))
        {
            if (arg2->sym != NULL && arg2->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%s\t", arg2->sym->value.varVal->name);
            }
            else if (arg2->sym != NULL)
            {
                fprintf(quad_file, "%s\t", arg2->sym->value.funcVal->name);
            }
        }
    }
    if (result != NULL)
    {
        if (!print_by_type(result, quad_file))
        {
            if (result->sym != NULL && result->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%s\t", result->sym->value.varVal->name);
            }
            else if (result->sym != NULL)
            {

                fprintf(quad_file, "%s\t", result->sym->value.funcVal->name);
            }
        }
    }
    if (label != 0)
    {
        fprintf(quad_file, "%u", label);
    }

    fprintf(quad_file, "\n");
}
int print_by_type(expr *_expr, FILE *quad_file)
{
    if (_expr->type == constbool_e)
    {
        if (_expr->boolConst == 0)
        {
            fprintf(quad_file, "%s>\t",  "false");
        }
        else
        {
            fprintf(quad_file, "%s>\t",  "true");
        }
        return 1;
    }
    else if (_expr->type == constint_e)
    {

        fprintf(quad_file, "%d>\t",  _expr->intConst);
        return 1;
    }
    else if (_expr->type == constdouble_e)
    {
        fprintf(quad_file, "%f>\t",  _expr->doubleConst);
        return 1;
    }
    else if (_expr->type == conststring_e)
    {
        fprintf(quad_file, "\"%s\">\t",  _expr->strConst);
        return 1;
    }
    else if (_expr->type == nil_e)
    {
        fprintf(quad_file, "%s>\t",  "nil");
        return 1;
    }
    return 0;
}

char *opcode_to_string(iopcode op)
{
    switch (op)
    {
    case assign:
        return "ASSIGN";
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
        return "GET_RET_VAL";
    case tablecreate:
        return "TABLE_CREATE";
    case tablegetelem:
        return "TABLE_GET_ELEM";
    case tablesetelem:
        return "TABLE_SET_ELEM";
    case jump:
        return "JUMP";
    }
}

expr *new_expr(expr_t type)
{
    expr *e = malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->type = type;
    e->next = NULL;
    return e;
}

expr *new_expr_const_string(char *name)
{
    expr *_expr = malloc(sizeof(expr));
    memset(_expr, 0, sizeof(expr));
    _expr->next = NULL;
    _expr->type = conststring_e;
    _expr->strConst = strdup(name);
    return _expr;
}

expr *new_expr_const_int(int intVal)
{
    expr *_expr = malloc(sizeof(expr));
    memset(_expr, 0, sizeof(expr));
    _expr->next = NULL;
    _expr->type = constint_e;
    _expr->intConst = intVal;
    return _expr;
}

expr *new_expr_const_double(double doubleVal)
{
    expr *_expr = malloc(sizeof(expr));
    memset(_expr, 0, sizeof(expr));
    _expr->next = NULL;
    _expr->type = constdouble_e;
    _expr->doubleConst = doubleVal;
    return _expr;
}

expr *new_expr_const_bool(unsigned char bool)
{
    expr *_expr = malloc(sizeof(expr));
    memset(_expr, 0, sizeof(expr));
    _expr->next = NULL;
    _expr->type = constbool_e;
    _expr->boolConst = !!bool;
    return _expr;
}
expr *new_expr_const_nil()
{
    expr *_expr = malloc(sizeof(expr));
    memset(_expr, 0, sizeof(expr));
    _expr->next = NULL;
    _expr->type = nil_e;
    return _expr;
}

expr *emit_if_table_item(expr *_expr)
{
    //printf("lafslsfda\n");

    if (_expr->type != tableitem_e)
        return _expr;

    expr *result;
    result = new_expr(var_e);
    result->sym = new_temp(symbolTable);
    emit(tablegetelem, _expr, _expr->index, result, curr_quad, 0, yylineno);
    return result;
}

#define elist_ptr (*elist_entry)

unsigned pop_elist(expr **elist_entry)
{
    if (elist_entry == NULL || *elist_entry == NULL)
    {
        return 0;
    }
    elist_ptr = elist_ptr->next;
    return 1;
}

void print_elist(expr *head)
{
    expr *tmp = head;
    while (tmp != NULL)
    {
        fprintf(stderr, "%s\n", tmp->sym->value.varVal->name);
        tmp = tmp->next;
    }
}
