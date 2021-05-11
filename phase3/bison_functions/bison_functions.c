#include "bison_functions.h"

#define lvalue_ptr (*lvalue)
int Came_From_OP = 0;

int check_if_bool_emit(expr **left)
{
    if ((*left) == NULL)
        return 0;

    if ((*left)->type != boolexpr_e)
    {
        (*left)->truelist = newlist(curr_quad);
        (*left)->falselist = newlist(curr_quad + 1);
        emit(if_eq, (*left), new_expr_const_bool(1), NULL, curr_quad, 0, yylineno);
        emit(jump, NULL, NULL, NULL, curr_quad, 0, yylineno);
        return 1;
    }
    return 0;
}
void create_emits_after_bool_op(expr **$3, SymbolTable *symbolTable)
{

    if ((*$3)!=NULL && ( (*$3)->truelist > 0 || (*$3)->falselist > 0 ) )
    {
        int tmp_1, tmp_2;
        tmp_1 = (*$3)->truelist;
        tmp_2 = (*$3)->falselist;
        (*$3) = new_expr(boolexpr_e);
        (*$3)->sym = new_temp(symbolTable);
        (*$3)->truelist = tmp_1;
        (*$3)->falselist = tmp_2;

        //fprintf(stderr,"curr quad %d\n",curr_quad);
        print_list((*$3)->truelist);
        print_list((*$3)->falselist);

        patchlist((*$3)->truelist, curr_quad);
        patchlist((*$3)->falselist, curr_quad + 2);
        //fprintf(stderr, "false list : %d\n", (*$3)->falselist);
        emit(assign, new_expr_const_bool(1), (*$3), NULL, curr_quad, 0, yylineno);
        emit(jump, NULL, NULL, NULL, curr_quad, curr_quad + 2, yylineno);
        emit(assign, new_expr_const_bool(0), (*$3), NULL, curr_quad, 0, yylineno);
        //(*$3)->truelist = 0;
        //(*$3)->falselist = 0;
    }
}

int do_the_arith_operations_double(iopcode opcode, expr *_expr, expr *expr1, expr *expr2)
{

    switch (opcode)
    {
    case add:
        _expr->doubleConst = (double)((expr1->type == constdouble_e) ? expr1->doubleConst : expr1->intConst) + ((expr2->type == constdouble_e) ? expr2->doubleConst : expr2->intConst);
        break;
    case sub:
        _expr->doubleConst = (double)((expr1->type == constdouble_e) ? expr1->doubleConst : expr1->intConst) - ((expr2->type == constdouble_e) ? expr2->doubleConst : expr2->intConst);
        break;
    case mul:
        _expr->doubleConst = (double)((expr1->type == constdouble_e) ? expr1->doubleConst : expr1->intConst) * ((expr2->type == constdouble_e) ? expr2->doubleConst : expr2->intConst);
        break;
    case _div:
        _expr->doubleConst = (double)((expr1->type == constdouble_e) ? expr1->doubleConst : expr1->intConst) / ((expr2->type == constdouble_e) ? expr2->doubleConst : expr2->intConst);
        break;
    case mod:
        //should this be on double const????
        _expr->doubleConst = (int)((int)(expr1->type == constdouble_e) ? expr1->doubleConst : expr1->intConst) % (int)((expr2->type == constdouble_e) ? expr2->doubleConst : expr2->intConst);
        break;
    default:
        return 0;
    }
    return 1;
}
int do_the_arith_operations_int(iopcode opcode, expr *_expr, expr *expr1, expr *expr2)
{
    switch (opcode)
    {
    case add:
        _expr->doubleConst = _expr->intConst = expr1->intConst + expr2->intConst;
        break;
    case sub:
        _expr->doubleConst = _expr->intConst = expr1->intConst - expr2->intConst;
        break;
    case mul:
        _expr->doubleConst = _expr->intConst = expr1->intConst * expr2->intConst;
        break;
    case _div:
        _expr->doubleConst = _expr->intConst = expr1->intConst / expr2->intConst;
        break;
    case mod:
        _expr->doubleConst = _expr->intConst = expr1->intConst % expr2->intConst;
        break;
    default:
        return 0;
    }
    return 1;
}

expr *process_arithm_operation(iopcode opcode, expr *expr1, expr *expr2, SymbolTable *symboltable)
{
    expr *_expr;
    check_arith(expr1, "arithmetic expression ");
    check_arith(expr2, "arithmetic expression ");

    if (expr1->type == constdouble_e && expr2->type == constdouble_e || expr1->type == constdouble_e && expr2->type == constint_e || expr2->type == constdouble_e && expr1->type == constint_e)
        _expr = new_expr(constdouble_e);

    else if (expr1->type == constint_e && expr2->type == constint_e)
        _expr = new_expr(constint_e);
    else
        _expr = new_expr(arithexpr_e);

    if (_expr->type == constdouble_e)
    {
        do_the_arith_operations_double(opcode, _expr, expr1, expr2);
        fprintf(stderr, "%f\n", _expr->doubleConst);
    }
    else if (_expr->type == constint_e)
    {
        do_the_arith_operations_int(opcode, _expr, expr1, expr2);
        fprintf(stderr, "%d\n", _expr->intConst);
    }
    _expr->sym = new_temp(symboltable);

    emit(opcode, expr1, expr2, _expr, curr_quad, 0, yylineno);

    return _expr;
}
expr *process_term_lvalue_plus_plus(expr *lvalue, expr **term, SymbolTable *symboltable)
{

    check_arith(lvalue, "lvalue++");
    *term = new_expr(var_e);
    (*term)->sym = new_temp(symboltable);
    if (lvalue->type == tableitem_e)
    {
        expr *val = emit_if_table_item(lvalue);
        emit(assign, val, NULL, *term, curr_quad, 0, yylineno);
        emit(add, val, new_expr_const_int(1), val, curr_quad, 0, yylineno);
        emit(tablesetelem, lvalue, lvalue->index, val, curr_quad, 0, yylineno);
    }
    else
    {
        emit(assign, lvalue, NULL, *term, curr_quad, 0, yylineno);
        emit(add, lvalue, new_expr_const_int(1), lvalue, curr_quad, 0, yylineno);
    }
}
expr *process_term_plus_plus_lvalue(expr *lvalue, expr **term, SymbolTable *symboltable)
{
    check_arith(lvalue, "++lvalue");
    if (lvalue->type == tableitem_e)
    {
        *term = emit_if_table_item(lvalue);
        emit(add, *term, new_expr_const_int(1), *term, curr_quad, 0, yylineno);
        emit(tablesetelem, lvalue, lvalue->index, *term, curr_quad, 0, yylineno);
    }
    else
    {
        emit(add, lvalue, new_expr_const_int(1), lvalue, curr_quad, 0, yylineno);
        *term = new_expr(arithexpr_e);
        (*term)->sym = new_temp(symboltable);
        emit(assign, lvalue, NULL, *term, curr_quad, 0, yylineno);
    }
}
expr *process_term_lvalue_minus_minus(expr *lvalue, expr **term, SymbolTable *symboltable)
{

    check_arith(lvalue, "lvalue--");
    *term = new_expr(var_e);
    (*term)->sym = new_temp(symboltable);
    if (lvalue->type == tableitem_e)
    {
        expr *val = emit_if_table_item(lvalue);
        emit(assign, val, NULL, *term, curr_quad, 0, yylineno);
        emit(sub, val, new_expr_const_int(1), val, curr_quad, 0, yylineno);
        emit(tablesetelem, lvalue, lvalue->index, val, curr_quad, 0, yylineno);
    }
    else
    {
        emit(assign, lvalue, NULL, *term, curr_quad, 0, yylineno);
        emit(sub, lvalue, new_expr_const_int(1), lvalue, curr_quad, 0, yylineno);
    }
}
expr *process_term_minus_minus_lvalue(expr *lvalue, expr **term, SymbolTable *symboltable)
{

    check_arith(lvalue, "--lvalue");
    if (lvalue->type == tableitem_e)
    {
        *term = emit_if_table_item(lvalue);
        emit(sub, *term, new_expr_const_int(1), *term, curr_quad, 0, yylineno);
        emit(tablesetelem, lvalue, lvalue->index, *term, curr_quad, 0, yylineno);
    }
    else
    {
        emit(sub, lvalue, new_expr_const_int(1), lvalue, curr_quad, 0, yylineno);
        *term = new_expr(arithexpr_e);
        (*term)->sym = new_temp(symboltable);
        emit(assign, lvalue, NULL, *term, curr_quad, 0, yylineno);
    }
}
expr *process_table_indexed(indexed *objects_list, SymbolTable *symboltable)
{
    expr *_expr;
    indexed *tmp;
    _expr = new_expr(newtable_e);
    _expr->sym = new_temp(symboltable);
    emit(tablecreate, _expr, NULL, NULL, curr_quad, 0, yylineno);
    fprintf(stderr, "lalal\n");
    tmp = objects_list;
    while (tmp != NULL)
    {
        emit(tablesetelem, _expr, tmp->left, tmp->right, curr_quad, 0, yylineno);
        tmp = tmp->next;
    }
    print_indexed_list(objects_list);
    return _expr;
}

expr *process_array_elist(expr *head, SymbolTable *symboltable)
{
    expr *tmp = head;
    expr *t = new_expr(newtable_e);
    int i = 0;
    t->sym = new_temp(symboltable);
    emit(tablecreate, t, NULL, NULL, curr_quad, 0, yylineno);
    while (tmp != NULL)
    {
        emit(tablesetelem, t, new_expr_const_int(i++), tmp, curr_quad, 0, yylineno);
        tmp = tmp->next;
    }
    return t;
}
void link_list(expr *head)
{
    expr *tmp = head, *prev = NULL;
    if (head == NULL)
        return;
    head->prev = NULL;
    tmp->prev = NULL;
    while (tmp->next != NULL)
    {
        prev = tmp;
        tmp = tmp->next;
        tmp->prev = prev;
    }
    head->tail = tmp;
}

void print_reverse(expr *head)
{
    if (head == NULL)
        return;
    expr *tmp = head->tail;
    while (tmp != NULL)
    {
        fprintf(stderr, "%s\n", tmp->sym->value.varVal->name);
        tmp = tmp->prev;
    }
}
void print_expr_list(expr *head)
{
    if (head == NULL)
        return;
    expr *tmp = head;
    while (tmp != NULL)
    {
        fprintf(stderr, "%s\n", tmp->sym->value.varVal->name);
        tmp = tmp->next;
    }
}
expr *make_call(expr *lvalue, expr *reverse_list, SymbolTable *symboltable)
{
    expr *tmp = reverse_list, *res;
    expr *func = emit_if_table_item(lvalue);
    print_expr_list(reverse_list);

    link_list(reverse_list);

    //print_reverse(tmp);
    if (reverse_list != NULL)
        tmp = reverse_list->tail;
    while (tmp != NULL)
    {
        emit(param, tmp, NULL, NULL, curr_quad, 0, yylineno);
        tmp = tmp->prev;
    }
    emit(call, func, NULL, NULL, curr_quad, 0, yylineno);
    res = new_expr(var_e);
    res->sym = new_temp(symboltable);
    emit(getretval, NULL, NULL, res, curr_quad, 0, yylineno);
    return res;
}
expr *process_elist_element(expr **head, expr *new_elist)
{
    //fprintf(stderr, "process_elist_element\n");

    //push_elist(head, NULL);
}
expr *process_elists_element(expr **head, expr *new_elist)
{
    //fprintf(stderr, "process_elists_element\n");

    //push_elist(head, new_elist);
    //print_elist(new_elist);
}

expr *member_item(expr *lvalue, char *name)
{
    expr *_expr;
    lvalue = emit_if_table_item(lvalue);
    _expr = new_expr(tableitem_e);
    //chech lvalue->sym is NULL?
    if (lvalue->sym != NULL)
        _expr->sym = lvalue->sym;
    _expr->index = new_expr_const_string(name);
    return _expr;
}
void process_local_id(SymbolTable *symbolTable, char *id_name, expr **lvalue)
{

    SymbolTableEntry *bucket;
    Variable *var;
    var = create_var(id_name, scope, yylineno);
    if (scope != 0)
        bucket = create_bucket_var(1, var, LOCAL);
    else
        bucket = create_bucket_var(1, var, GLOBAL);
    if (symbolTable_lookup_exists_exact_scope(symbolTable, scope, (const char *)id_name) == 0)
    {
        if (is_library_func(symbolTable, (const char *)id_name))
        {
            print_error(NULL, yylineno, "ERROR : conflict with library function");
            //*lvalue = NULL;
        }
        else
        {
            symbolTable_insert(symbolTable, bucket);
            bucket->space = curr_scope_space();
            bucket->offset = curr_scope_offset();
            in_current_scope_offset();
        }
    }
    else
    {
        bucket = find_bucket_by_scope_and_name(symbolTable, id_name, scope);
        bucket->space = curr_scope_space();
        bucket->offset = curr_scope_offset();
        in_current_scope_offset();
    }
    lvalue_ptr = lvalue_expr(bucket);
}
void process_id(SymbolTable *symbolTable, char *id_name, expr **lvalue)
{
    SymbolTableEntry *bucket;
    Variable *var;

    bucket = symbolTable_lookup_scopeless(symbolTable, id_name);
    if (bucket == NULL)
    {

        var = create_var(id_name, scope, yylineno);
        if (scope != 0)
            bucket = create_bucket_var(1, var, LOCAL);
        else
            bucket = create_bucket_var(1, var, GLOBAL);

        symbolTable_insert(symbolTable, bucket);
        bucket->space = curr_scope_space();
        bucket->offset = curr_scope_offset();
        in_current_scope_offset();
    }
    lvalue_ptr = lvalue_expr(bucket);
}

void process_assign(SymbolTable *symbolTable, expr **lvalue, expr **assign_expr, expr *_expr)
{
    if (lvalue == NULL)
    {
        return;
    }
    if (is_function(lvalue_ptr->sym))
    {

        print_error(NULL, yylineno, "ERROR : assign to function");

        *lvalue = NULL;
        return;
    }

    if (check_access(symbolTable, &lvalue_ptr->sym))
    {
        if (lvalue_ptr->type == tableitem_e)
        {
            emit(tablesetelem, lvalue_ptr, lvalue_ptr->index, _expr, curr_quad, 0, yylineno);
            *assign_expr = emit_if_table_item(lvalue_ptr);
            (*assign_expr)->type = assignexpr_e;
        }
        else
        {
            emit(assign, _expr, NULL, lvalue_ptr, curr_quad, 0, yylineno);
            *assign_expr = new_expr(assignexpr_e);
            (*assign_expr)->sym = new_temp(symbolTable);
            emit(assign, lvalue_ptr, NULL, *assign_expr, curr_quad, 0, yylineno);
        }
    }
}

void process_callsuffix(SymbolTable *symbolTable, expr **lvalue)
{
    check_access(symbolTable, &lvalue_ptr->sym);
}
void process_primary(SymbolTable *symbolTable, expr **lvalue)
{

    if (check_access(symbolTable, &lvalue_ptr->sym))
    {
        lvalue_ptr = emit_if_table_item(lvalue_ptr);
        return;
    }
    lvalue_ptr = NULL; //??
}

void process_plus_plus(SymbolTable *symbolTable, expr **lvalue)
{
    if (is_function(lvalue_ptr->sym))
    {

        print_error(NULL, yylineno, "ERROR : ++ to function");

        //*lvalue = NULL;
        return;
    }
    check_access(symbolTable, &lvalue_ptr->sym);
}
void process_minus_minus(SymbolTable *symbolTable, expr **lvalue)
{
    if (is_function(lvalue_ptr->sym))
    {

        print_error(NULL, yylineno, "ERROR : -- to function");

        //*lvalue = NULL;
        return;
    }
    check_access(symbolTable, &lvalue_ptr->sym);
}

short check_access(SymbolTable *symbolTable, SymbolTableEntry **lvalue)
{
    if (*lvalue == NULL || lvalue == NULL)
    {
        return 0;
    }
    const char *id_name;
    id_name = ((*lvalue)->value.varVal != NULL) ? (*lvalue)->value.varVal->name : (*lvalue)->value.funcVal->name;
    if ((*lvalue)->value.varVal != NULL && (*lvalue)->value.varVal->scope == scope || (*lvalue)->value.varVal != NULL && (*lvalue)->value.varVal->scope == scope)
    {
        //all good
    }
    else if (!is_function(*lvalue) && (*lvalue)->value.varVal->scope == 0)
    {
        //tipota
    }
    else if (iam_in_function <= 0) //i have access
    {
    }
    else
    {
        SymbolTableEntry *func_entry = top(functions_stack);
        if (is_function(*lvalue) || (*lvalue)->value.varVal->scope == 0 ||
            func_entry != NULL && (*lvalue)->value.varVal->scope > func_entry->value.funcVal->scope)
        {
        }
        else
        {

            print_error(id_name, yylineno, "ERROR : no access to variable");
            *lvalue = NULL;
            return 0;
        }
    }
    return 1;
}

void reset_formal_arg_offset()
{
    formal_arg_offset = 0;
}
expr *process_funcdef(expr *func_prefix, unsigned total_locals)
{
    exit_scope_space();
    printf("scope space : %u\n", curr_scope_space());
    printf("total locals  : %u\n", total_locals);
    if (func_prefix->sym != NULL)
        func_prefix->sym->value.funcVal->total_locals = total_locals;
    unsigned offset = pop_scope_offset_stack();
    //printf("lala2\n");
    restore_curr_scope_offset(offset);
    emit(funcend, func_prefix, NULL, NULL, curr_quad, 0, yylineno);
    return func_prefix;
}

expr *process_function_prefix(SymbolTable *symbolTable, char *func_name)
{
    expr *_expr;
    Function *func;
    SymbolTableEntry *bucket;

    func = create_func(func_name, scope, yylineno);
    bucket = create_bucket_func(1, func, USERFUNC);
    if (bucket->value.funcVal != NULL)
        bucket->value.funcVal->iadress = curr_quad;
    _expr = lvalue_expr(bucket);
    emit(funcstart, _expr, NULL, NULL, curr_quad, 0, yylineno);
    push_scope_offset_stack(curr_scope_offset());
    enter_scope_space();
    reset_formal_arg_offset();
    short status = symbolTable_lookup_exists_exact_scope(symbolTable, scope, func_name);

    if (is_library_func(symbolTable, func_name))
    {
        print_error(func_name, yylineno, "ERROR : function name shadows libfunc");
    }
    else if (status == ERROR_FUNC)
    {
        print_error(func_name, yylineno, "ERROR : function already exists");
    }
    else if (status == ERROR_VAR)
    {
        print_error(func_name, yylineno, "ERROR : use variable as function"); //kalo?
    }
    else
    {
        symbolTable_insert(symbolTable, bucket);
        push(functions_stack, bucket);
    }

    return _expr;
}

void print_to_stream(char *msg)
{

    fprintf(output_file, "%s\n", msg);
}
void print_error(const char *name, int line, char *msg)
{
    print_Red();
    fprintf(stderr, "%s", msg);
    fprintf(stderr, " in line : %d", line);
    if (name != NULL)
        fprintf(stderr, " ID : %s\n", name);
    else
        fprintf(stderr, "\n");

    reset_Red();
    found_compile_error = 1;
}
void process_anonymous_function(SymbolTable *symbolTable)
{
    Function *func;
    SymbolTableEntry *bucket;
    func = create_func(NULL, scope, yylineno);
    bucket = create_bucket_func(1, func, USERFUNC);
    symbolTable_insert(symbolTable, bucket);
    push(functions_stack, bucket);
}
void process_function_arguments(SymbolTable *symbolTable, char *arg_name)
{
    SymbolTableEntry *bucket;
    Variable *var;
    var = create_var(arg_name, scope, yylineno);
    bucket = create_bucket_var(1, var, FORMAL);
    if (is_library_func(symbolTable, arg_name))
    {
        print_error(NULL, yylineno, "ERROR : formal argument shadows libfunc");
    }
    else if (symbolTable_lookup_exists_exact_scope(symbolTable, scope, arg_name) != 0)
    {
        print_error(NULL, yylineno, "ERROR : formal argument redeclaration");
    }
    else
    {
        symbolTable_insert(symbolTable, bucket);
        create_argument(symbolTable, arg_name, scope);
    }
}
void process_double_colon_id(SymbolTable *symbolTable, char *name, expr **lvalue)
{
    if (symbolTable_lookup_exists_exact_scope(symbolTable, 0, name) == 0)
    {
        print_error(name, yylineno, "ERROR : global variable doesn't exist");
    }
    lvalue_ptr->sym = find_bucket_by_scope_and_name(symbolTable, name, 0);
}
