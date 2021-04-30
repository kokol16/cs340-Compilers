%{
#include "bison_functions/bison_functions.h"
#include <stdio.h>

int func_line=0;
SymbolTable *  symbolTable;
FILE *output_file;
int yylex(void);
int yyerror( char * msg );
extern FILE * yyin;




%}
%union {
    struct SymbolTableEntry * symboltable_Node;
	double floatVal;
    int intigerVal;
    unsigned curr_scope_offset;
    //float real;
    unsigned char bool;
    struct indexed *  _indexed;
    struct expr * expr_node;
	char * str;
    struct call_info* call_type;
}
%start program
%token <bool> TRUE  FALSE
%token <str> ID STRING
%token <intigerVal> INTEGER
%token <floatVal> FLOAT 
%token    IF ELSE WHILE FOR FUNCTION RETURN  BREAK CONTINUE AND  NOT  OR  LOCALL NIL EQUALS PLUS
%token ASSIGN MINUS UMINUS ASTERISK DIVISION PERCENT DIFFERENT PLUS_PLUS MINUS_MINUS GREATER LESS GREATER_EQUALS LESS_EQUALS
%token SEMICOLON COMMA COLON DOUBLE_COLON DOT Diaeresis LEFT_BRACE RIGHT_BRACE LEFT_SQUARE RIGHT_SQUARE LEFT_BRACKETS RIGHT_BRACKETS  

%right ASSIGN
%left OR
%left AND 
%nonassoc EQUALS DIFFERENT  
%nonassoc GREATER GREATER_EQUALS LESS_EQUALS LESS
%left PLUS MINUS
%left ASTERISK  PERCENT DIVISION
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left DOT Diaeresis
%left LEFT_SQUARE RIGHT_SQUARE
%left LEFT_BRACKETS RIGHT_BRACKETS

%type <expr_node> lvalue member expr assignexpr const  primary term elist objectdef
%type<curr_scope_offset> block_func
%type<str> funcname
%type <_indexed> indexedelem indexed 

%type<expr_node> funcprefix funcdef call
%type<call_type> methodcall normcall callsuffix 

%%         
program: statements {print_to_stream("Program");}  ;
stmt:   expr SEMICOLON   {print_to_stream("Statement");resettemp();}  
        | ifstmt         {print_to_stream("Statement");resettemp();}  
        | whilestmt      {print_to_stream("Statement");resettemp();}  
        | forstmt        {print_to_stream("Statement");resettemp();}  
        | returnstmt     {print_to_stream("Statement");resettemp();}  
        | BREAK SEMICOLON {     print_to_stream("Statement");resettemp();
                                   if(top_func_loop()!=for_loop && top_func_loop()!=while_loop )
                                    {
                                        print_error(NULL,yylineno, "ERROR : use BREAK not in a loop");
                                    } 
                                    
        
                            }
        | CONTINUE SEMICOLON {     {print_to_stream("Statement");resettemp();}  
                                    if(top_func_loop()!=for_loop && top_func_loop()!=while_loop)
                                    {
                                       print_error(NULL,yylineno, "ERROR : use CONTINUE not in a loop");
                                    } 
                                    
                            }
        | block             {print_to_stream("Statement");resettemp();}  
        | funcdef           {print_to_stream("Statement");resettemp();}  
        |SEMICOLON          {print_to_stream("Statement");resettemp();}  
        ;
statements: statements stmt
            |stmt;

expr:   assignexpr  {print_to_stream("Expression");}
        |expr PLUS expr {print_to_stream("+ expression");  $$=process_arithm_operation(add,$1,$3,symbolTable);}
        |expr MINUS expr {print_to_stream("- expression"); $$=process_arithm_operation(sub,$1,$3,symbolTable);}
        |expr ASTERISK expr {print_to_stream("* expression"); $$=process_arithm_operation(mul,$1,$3,symbolTable);}
        |expr DIVISION expr {print_to_stream("/ expression"); $$=process_arithm_operation(_div,$1,$3,symbolTable);}
        |expr PERCENT expr {print_to_stream("% expression"); $$=process_arithm_operation(mod,$1,$3,symbolTable);}
        |expr GREATER expr {print_to_stream("> expression");}
        |expr GREATER_EQUALS expr {print_to_stream(">= expression");}
        |expr LESS  expr {print_to_stream("< expression");}
        |expr LESS_EQUALS expr {print_to_stream("<= expression");}
        |expr EQUALS expr {print_to_stream("== expression");}
        |expr DIFFERENT expr {print_to_stream("!= expression");}
        |expr AND expr {print_to_stream("and expression");}
        |expr OR expr {print_to_stream("or expression");}
        | term  {print_to_stream("Expression"); $$=$1;};

        

term:   LEFT_BRACKETS expr RIGHT_BRACKETS {print_to_stream("Term"); $$=$2;}
        | MINUS expr %prec UMINUS   {print_to_stream("Term"); check_arith($2,"uminus expression");
                                                               $$=new_expr(arithexpr_e);
                                                               $$->sym=new_temp(symbolTable);
                                                               emit(uminus , $2,NULL,$$,curr_quad,yylineno);                  }
                                  
        
        | NOT expr        {print_to_stream("Term");     $$ = new_expr(boolexpr_e);
                                                        $$->sym = new_temp(symbolTable);
                                                        emit(not,$2, NULL, $$,curr_quad,yylineno);
                                                        }                   
                                           
        
        | PLUS_PLUS lvalue  {               {print_to_stream("Term");}
                                          process_plus_plus(symbolTable, &$2);
                                          process_term_plus_plus_lvalue($2,&$$,symbolTable);
                                          
                                            
                            }
        | lvalue PLUS_PLUS  {                {print_to_stream("Term");}
                                            process_plus_plus(symbolTable,  &$1);
                                            process_term_lvalue_plus_plus($1,&$$,symbolTable);//...

                                            
                            }
        | MINUS_MINUS lvalue{              {print_to_stream("Term");
                                          process_minus_minus(symbolTable, &$2);
                                          process_term_minus_minus_lvalue($2,&$$,symbolTable);
                                        }
                                          
        }
        | lvalue MINUS_MINUS {               print_to_stream("Term");
                                                process_minus_minus(symbolTable, &$1);
                                                process_term_lvalue_minus_minus($1,&$$,symbolTable);}
                                           
        
        | primary                             {print_to_stream("Term"); $$=$1;};  

assignexpr: lvalue  ASSIGN  expr    { 
                                        print_to_stream("Assign expression");
                                        //printf("const %d\n",$3->intConst);
                                        process_assign(symbolTable,  &$1, &$$ , $3 );
                                    }; 
    
                                   


primary:  lvalue { print_to_stream("Primary");  process_primary(symbolTable,  &$1);   }
          | call {print_to_stream("Primary");}
          | objectdef {print_to_stream("Primary");}
          | LEFT_BRACKETS funcdef RIGHT_BRACKETS  {print_to_stream("Primary"); $$=new_expr(programfunc_e);
                                                                                $$->sym=$2->sym;             }
          | const {print_to_stream("Primary"); $$=$1;} ;

lvalue:   ID                    {print_to_stream("Lvalue"); process_id(symbolTable,$1,&$$); }
          | LOCALL ID           {print_to_stream("Lvalue"); process_local_id(symbolTable,  $2, &$$);}
          | DOUBLE_COLON ID     {print_to_stream("Lvalue"); process_double_colon_id(symbolTable,$2,&$$); }             
          | member {print_to_stream("Lvalue"); $$=$1;} ; 

member:    lvalue DOT ID {print_to_stream("Member");   $$= member_item($1,$3); }
            | lvalue LEFT_SQUARE expr RIGHT_SQUARE {print_to_stream("Member");  
                                                    $1=emit_if_table_item($1);
                                                    $$=new_expr(tableitem_e);
                                                    $$->sym=$1->sym;
                                                    $$->index=$3;
                                                    }
            | call DOT ID {print_to_stream("Member");}
            | call LEFT_SQUARE expr RIGHT_SQUARE {print_to_stream("Member");} ;

call:      call LEFT_BRACKETS elist RIGHT_BRACKETS {print_to_stream("Call1"); $$=make_call($1,$3,symbolTable);} 
            | lvalue callsuffix { print_to_stream("Call5"); 
                                                            process_callsuffix(symbolTable, &$1);
                                                            $1=emit_if_table_item($1);
                                                            if($2->method){
                                                              expr* e=$1;
                                                              $1=emit_if_table_item(member_item(e,$2->name));
                                                              expr * tmp= $2->elist;
                                                              if(tmp==NULL)
                                                              {
                                                                $2->elist=e;
                                                              }
                                                              else
                                                              {

                                                                while(tmp->next!=NULL)
                                                                {
                                                                    tmp=tmp->next;
                                                                }
                                                                tmp->next=e;
                                                              }

                                                           }
                                                           $$=make_call($1,$2->elist,symbolTable);
                                                            

                                }
            | LEFT_BRACKETS funcdef RIGHT_BRACKETS LEFT_BRACKETS elist RIGHT_BRACKETS {print_to_stream("Call2"); expr* func=new_expr(programfunc_e);
                                                                                                                 func->sym=$2->sym;
                                                                                                                 $$=make_call(func,$5,symbolTable);}
            | LEFT_BRACKETS funcdef RIGHT_BRACKETS LEFT_BRACKETS  RIGHT_BRACKETS {print_to_stream("Call3");
                                                                                    expr* func=new_expr(programfunc_e);
                                                                                    func->sym=$2->sym;
                                                                                    $$=make_call(func,NULL,symbolTable);
                                                                                }
            | call LEFT_BRACKETS  RIGHT_BRACKETS {print_to_stream("Call4"); $$=make_call($$,NULL,symbolTable);};

callsuffix: normcall {print_to_stream("Call Suffix"); $$=$1;}
            | methodcall {print_to_stream("Call Suffix"); $$=$1;} ;

normcall: LEFT_BRACKETS elist RIGHT_BRACKETS {print_to_stream("Normal Call") ;              $$=malloc(sizeof(struct call_info));
                                                                                            $$->elist=$2;
                                                                                            $$->method=0;
                                                                                            $$->name=NULL;

                                                                                            }
          
          |LEFT_BRACKETS  RIGHT_BRACKETS {print_to_stream("Normal Call");                   $$=malloc(sizeof(struct call_info));
                                                                                            $$->elist=NULL;
                                                                                            $$->method=0;
                                                                                            $$->name=NULL;};

methodcall:Diaeresis ID LEFT_BRACKETS elist RIGHT_BRACKETS {print_to_stream("Method Call");
                                                                                            $$=malloc(sizeof(struct call_info));
                                                                                            $$->elist=$4;
                                                                                            $$->method=1;
                                                                                            $$->name=strdup($2);} /* equivalent to lvalue->ID'('lvalue, elist')';*/
           
           |Diaeresis ID LEFT_BRACKETS  RIGHT_BRACKETS {print_to_stream("Method Call");    
                                                                                            $$=malloc(sizeof(struct call_info));
                                                                                            $$->elist=NULL;
                                                                                            $$->method=1;
                                                                                            $$->name=strdup($2);}

elist:   expr   {print_to_stream("Expression List");
                                       

                                        $$=$1;  
                                         } 
        | expr COMMA elist {print_to_stream("Expression List Comma");      
                                                                
                                                                    
                                                                    $1->next=$3;
                                                                    
                                                                
                                                                  
                                                                    
                                                                       };
            
objectdef: LEFT_SQUARE  elist  RIGHT_SQUARE     {print_to_stream("Object Definition");  $$=process_array_elist($2,symbolTable);}
           |LEFT_SQUARE  indexed  RIGHT_SQUARE {print_to_stream("Object Definition"); $$=process_table_indexed($2,symbolTable);}
           |LEFT_SQUARE  RIGHT_SQUARE {print_to_stream("Object Definition"); $$=process_array_elist(NULL,symbolTable);};

indexed:    indexedelem  {print_to_stream("Indexed");  $$=$1;    }
            | indexedelem COMMA  indexed {print_to_stream("Indexed");  $1->next=$3; };
           

indexedelem: LEFT_BRACE expr  COLON expr RIGHT_BRACE {print_to_stream("Index Element"); $$=malloc(sizeof(indexed));
                                                                                        $$->left=$2;
                                                                                        $$->right=$4;
                                                                                        $$->next=NULL;
                                                                                        
                                                                                        };

block: LEFT_BRACE {scope++;}  RIGHT_BRACE  {print_to_stream("Block"); symbolTable_hide(symbolTable, scope); scope--;}       
       |LEFT_BRACE {scope++;}  statements  RIGHT_BRACE {print_to_stream("Block"); symbolTable_hide(symbolTable, scope); scope--;} ;  
       
block_func: LEFT_BRACE {iam_in_function++;enum func_loops entry = func; push_func_loop(   entry  );}  RIGHT_BRACE  {print_to_stream("Function Block");  symbolTable_hide(symbolTable, scope);
 scope--; iam_in_function--;   pop(functions_stack);    pop_func_loop(); $$=curr_scope_offset(); exit_scope_space();  }       
       |LEFT_BRACE {iam_in_function++;enum func_loops entry = func; push_func_loop(   entry  );}    statements  RIGHT_BRACE {print_to_stream("Function Block");  symbolTable_hide(symbolTable, scope); scope--;  iam_in_function--;
     pop(functions_stack);  pop_func_loop(); $$=curr_scope_offset(); exit_scope_space();  } ;  
  

funcdef: funcprefix  LEFT_BRACKETS {scope++;}  
                        idlist   RIGHT_BRACKETS {enter_scope_space(); reset_function_locals_offset(); }
                      block_func {print_to_stream("Function Definition");   }
                      {
                          $$ = process_funcdef($1, $7);
                      };

                                                                
        
                                                                  
funcprefix: FUNCTION funcname {  $$=process_function_prefix(symbolTable,   $2  ); };
funcname: ID {$$=$1; }
|  {$$=new_func_name();};


const:  INTEGER {print_to_stream("Integer");  $$ = new_expr_const_int($1);}
        |FLOAT    {print_to_stream("Float"); $$=new_expr_const_double($1);}
        | STRING  {print_to_stream("String");$$ = new_expr_const_string($1);}
        | NIL {print_to_stream("NIL");$$ = new_expr_const_nil();}
        | TRUE {print_to_stream("TRUE");$$ = new_expr_const_bool($1);}
        | FALSE {print_to_stream("FALSE"); $$ = new_expr_const_bool($1);};

idlist: ID  { print_to_stream("ID List");  process_function_arguments(symbolTable,$1);                     

                                           
            }
            |   ID { process_function_arguments(symbolTable,$1); 
            }  COMMA idlist  {print_to_stream("ID List");}
        
            |    {print_to_stream("ID List");};

ifstmt: IF LEFT_BRACKETS expr RIGHT_BRACKETS stmt  ELSE stmt {print_to_stream("If Statement");} 
        | IF LEFT_BRACKETS expr RIGHT_BRACKETS stmt {print_to_stream("If Statement");} 
whilestmt: WHILE LEFT_BRACKETS {iam_in_loop++; enum func_loops entry = while_loop; push_func_loop(   entry  ); } expr RIGHT_BRACKETS stmt {print_to_stream("While Statement"); 
        iam_in_loop--;   pop_func_loop();                                };

forstmt:  forprefix elist SEMICOLON  expr SEMICOLON  elist RIGHT_BRACKETS stmt 
                            { print_to_stream("For Statement"); iam_in_loop--;  pop_func_loop(); }
         | forprefix elist SEMICOLON  expr SEMICOLON   RIGHT_BRACKETS stmt 
                            { print_to_stream("For Statement"); iam_in_loop--;  pop_func_loop(); }                  
         | forprefix     SEMICOLON  expr SEMICOLON elist  RIGHT_BRACKETS stmt   
                            {print_to_stream("For Statement"); iam_in_loop--; pop_func_loop();}
         | forprefix     SEMICOLON  expr SEMICOLON   RIGHT_BRACKETS stmt   
                            {print_to_stream("For Statement"); iam_in_loop--; pop_func_loop();};  

forprefix:  FOR LEFT_BRACKETS  {iam_in_loop++;enum func_loops entry = for_loop; push_func_loop(   entry  );};      
            
returnstmt: RETURN expr SEMICOLON {   print_to_stream("Return Statement");
                                    if(iam_in_function <=0)
                                    {
                                       print_error(NULL,yylineno, "ERROR : return out of function");
                                    } 
                                    
                                 } 
                                    
            |  RETURN SEMICOLON    {    print_to_stream("Return Statement");
                                        if(iam_in_function <=0)
                                        {
                                           print_error(NULL,yylineno, "ERROR : return out of function");
                                        } 
                                        
                                        
                                     };


%%

int yyerror( char * msg )
{
    print_Red();
    fprintf(stderr ,"%s in line : %d \n", msg,yylineno);
    reset_Red();

}
int main(int argc , char * argv[])
{
    if(argc==2)
    {
        if(!( yyin=fopen(argv[1],"r") )  )
        {
            fprintf(stderr,"Error: can't read file\n");
            return -1;
        }   
        output_file=stdout;
        
    }
    else if (argc>2)
    {
        if(!( yyin=fopen(argv[1],"r") )  )
        {
            fprintf(stderr,"Error: can't read file\n");
            return -1;
        } 
        output_file=fopen(argv[2],"w");
        if(output_file==NULL)
        {
            fprintf(stderr,"Error: can't open write file\n");
            return -1;
        }
    }
    else
    {
        output_file=stdout;
        yyin=stdin;
    }
  
    symbolTable = symbolTable_create();
    FILE *quad_file = fopen("quads.txt", "w+");

    yyparse() ;
    //symbolTable_print(symbolTable);
    //symbolTable_print_scope_list(symbolTable, 1);
    symbolTable_print_scopes(symbolTable,100);
    if(output_file!=NULL)
    fclose(output_file);
    fclose(yyin);
}

