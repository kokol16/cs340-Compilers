#include "quads.h"

quad *quads = NULL;
unsigned total = 0;
unsigned int curr_quad = 0;
int temp_counter = 0;

SymbolTable *symbolTable;

void make_stmt(stmt_t *s)
{
    s->breaklist = 0;
    s->contlist = 0;
}
int newlist(int i)
{
    quads[i].label = 0;
    return i;
}

int mergelist(int l1, int l2)
{
    fprintf(stderr, "merge l1:%d l2:%d\n", l1, l2);
    //if(l1>=curr_quad ||l2>=curr_quad ) return 0;
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
            fprintf(stderr, "i : %d\n",i);
        }

        quads[i].label = l2;
        return l1;
    }
}
void patchlist(int list, int label)
{
    fprintf(stderr, "starting from index : %d\n",list);
   
    while (list!=0 && list<curr_quad)
    {
        int next = quads[list].label;
        fprintf(stderr, "%d-->", list);
        quads[list].label = label;
        list = next;
    }
    fprintf(stderr, "\n");
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
        fprintf(stderr, "Illegal expr used in %s! ", context);
}
void print_indexed_list(indexed *head)
{
    indexed *tmp = head;
    while (tmp != NULL)
    {
        if (!print_by_type(tmp->left, stderr))
        {
            fprintf(stderr, "%s", tmp->left->sym->value.varVal->name);
        }
        if (!print_by_type(tmp->right, stderr))
        {
            fprintf(stderr, " : %s\n", tmp->right->sym->value.varVal->name);
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
    _quad = malloc(NEW_SIZE);
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
    _quad->quad_no = quad_no + 1;

    if (label == 0 && (op == if_eq || if_greater == op || if_greatereq == op || if_less == op || if_lesseq == op || if_noteq == op))
    {
        fprintf(stderr, "making label 1\n");
        _quad->label = 1;
    }
    else
    {
        if (label != 0)
            _quad->label = label + 1;
    }
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
    if (arg1 != NULL)
    {
        if (!print_by_type(arg1, quad_file))
        {
            if (arg1->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%s\t", arg1->sym->value.varVal->name);
            }
            else
            {
                fprintf(quad_file, "%s\t", arg1->sym->value.funcVal->name);
            }
        }
    }
    if (arg2 != NULL)
    {
        if (!print_by_type(arg2, quad_file))
        {
            if (arg2->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%s\t", arg2->sym->value.varVal->name);
            }
            else
            {
                fprintf(quad_file, "%s\t", arg2->sym->value.funcVal->name);
            }
        }
    }
    if (result != NULL)
    {
        if (!print_by_type(result, quad_file))
        {
            if (result->sym->value.varVal != NULL)
            {
                fprintf(quad_file, "%s\t", result->sym->value.varVal->name);
            }
            else
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

    /* if (op == assign)
    {

        //else
        {
            if (!print_by_type(arg1, quad_file))
            {
                fprintf(quad_file, "%s\t", arg1->sym->value.varVal->name);
            }
            if (!print_by_type(result, quad_file))
            {
                fprintf(quad_file, "%s\t", result->sym->value.varVal->name);
            }
            fprintf(quad_file, "\n");
        }
    }
    else if (op == param)
    {
        fprintf(quad_file, "%s\n", arg1->sym->value.varVal->name);
    }
    else if (op == call)
    {
        fprintf(quad_file, "%s\n", arg1->sym->value.varVal->name);
    }
    else if (op == getretval)
    {
        fprintf(quad_file, "%s\n", result->sym->value.varVal->name);
    }
    else if (op == tablecreate)
    {
        if (!print_by_type(arg1, quad_file))
        {
            fprintf(quad_file, "%s\n", arg1->sym->value.varVal->name);
        }
    }
    else if (op == tablesetelem)
    {
        fprintf(quad_file, "%s\t", arg1->sym->value.varVal->name);
        if (!print_by_type(arg2, quad_file))
        {

            fprintf(quad_file, "%s\t", arg2->sym->value.varVal->name);
        }

        if (!print_by_type(result, quad_file))
        {
            fprintf(quad_file, "%s\t", result->sym->value.varVal->name);
        }
        fprintf(quad_file, "\n");
    }*/
}
int print_by_type(expr *_expr, FILE *quad_file)
{
    if (_expr->type == constbool_e)
    {
        fprintf(quad_file, "%u\t", _expr->boolConst);
        return 1;
    }
    else if (_expr->type == constint_e)
    {

        fprintf(quad_file, "%d\t", _expr->intConst);
        return 1;
    }
    else if (_expr->type == constdouble_e)
    {
        fprintf(quad_file, "%f\t", _expr->doubleConst);
        return 1;
    }
    else if (_expr->type == conststring_e)
    {
        fprintf(quad_file, "%s\t", _expr->strConst);
        return 1;
    }
    else if (_expr->type == nil_e)
    {
        fprintf(quad_file, "%s\t", "nil");
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
        return "GET_RETURN_VALUE";
    case tablecreate:
        return "TABLE_CREATE";
    case tablegetelem:
        return "TABLE_GET_ELEMENT";
    case tablesetelem:
        return "TABLE_SET_ELEMENT";
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

int push_elist(expr **elist_entry, expr *entry)
{
    // if(entry==NULL) {return 0;}
    /*entry->next = NULL;
    if (  entry==NULL )
    {
        fprintf(stderr, "create head\n");
        elist_ptr = entry;

        print_elist(*elist_entry);
        return 1;
    }*/

    // entry->next = elist_ptr;
    //elist_ptr = entry;

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
/*expr *  top_elist(expr * elist_head)
{
    if (elist_head != NULL)
    {
        return elist_head;
    }
    else
    {
        return -1;
    }
}*/
