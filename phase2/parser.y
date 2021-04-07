%{
#include "bison_functions/bison_functions.h"
#include <stdio.h>
extern FILE * yyin;
extern int yylineno; 
int func_line=0;
SymbolTable *  symbolTable;
FILE *output_file;
int yylex(void);
short is_local_id=0;
int yyerror( char * msg );
unsigned int  scope=0;
unsigned int need_check=0;
unsigned int iam_in_function=0;
unsigned int iam_in_loop=0;
function_stack * functions_stack=NULL;


%}
%union {
    struct SymbolTableEntry * exprNode;
	float floatVal;
    int intigerVal;
    //float real;
	char * str;
}
%start program
%token <str> ID
%token <intigerVal> INTEGER
%token <floatVar> FLOAT
%token    IF ELSE WHILE FOR FUNCTION RETURN  BREAK CONTINUE AND  NOT  OR  LOCALL TRUE FALSE NIL STRING EQUALS PLUS
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

%type <exprNode> lvalue 


%%         
program: statements {print_to_stream("Program");}  ;
stmt:   expr SEMICOLON   {print_to_stream("Statement");}  
        | ifstmt         {print_to_stream("Statement");}  
        | whilestmt      {print_to_stream("Statement");}  
        | forstmt        {print_to_stream("Statement");}  
        | returnstmt     {print_to_stream("Statement");}  
        | BREAK SEMICOLON {      {print_to_stream("Statement");}  
                                   if(top_func_loop()!=for_loop && top_func_loop()!=while_loop )
                                    {
                                        print_error(NULL,yylineno, "ERROR : use BREAK not in a loop");
                                    } 
                                    
        
                            }
        | CONTINUE SEMICOLON {     {print_to_stream("Statement");}  
                                    if(top_func_loop()!=for_loop && top_func_loop()!=while_loop)
                                    {
                                       print_error(NULL,yylineno, "ERROR : use CONTINUE not in a loop");
                                    } 
                                    
                            }
        | block             {print_to_stream("Statement");}  
        | funcdef           {print_to_stream("Statement");}  
        |SEMICOLON          {print_to_stream("Statement");}  
        ;
statements: statements stmt
            |stmt;

expr:   assignexpr  {print_to_stream("Expression");}
        |expr PLUS expr {print_to_stream("+ expression");}
        |expr MINUS expr {print_to_stream("- expression");}
        |expr ASTERISK expr {print_to_stream("* expression");}
        |expr DIVISION expr {print_to_stream("/ expression");}
        |expr PERCENT expr {print_to_stream("% expression");}
        |expr GREATER expr {print_to_stream("> expression");}
        |expr GREATER_EQUALS expr {print_to_stream(">= expression");}
        |expr LESS  expr {print_to_stream("< expression");}
        |expr LESS_EQUALS expr {print_to_stream("<= expression");}
        |expr EQUALS expr {print_to_stream("== expression");}
        |expr DIFFERENT expr {print_to_stream("!= expression");}
        |expr AND expr {print_to_stream("and expression");}
        |expr OR expr {print_to_stream("or expression");}
        | term  {print_to_stream("Expression");};

        

term:   LEFT_BRACKETS expr RIGHT_BRACKETS {print_to_stream("Term");}
        | MINUS expr %prec UMINUS   {print_to_stream("Term");}
                                  
        
        | NOT expr        {print_to_stream("Term");}                   
                                           
        
        | PLUS_PLUS lvalue  {               {print_to_stream("Term");}
                                          process_plus_plus(symbolTable, scope, yylineno,
                                        iam_in_function, &functions_stack, &$2);
                                           
                                            
                            }
        | lvalue PLUS_PLUS  {                {print_to_stream("Term");}
                                            process_plus_plus(symbolTable, scope, yylineno,
                                        iam_in_function, &functions_stack, &$1);
                            }
        | MINUS_MINUS lvalue{              {print_to_stream("Term");
                                          process_minus_minus(symbolTable, scope, yylineno,
                                        iam_in_function, &functions_stack, &$2);
                                        }
                                          
        }
        | lvalue MINUS_MINUS {               print_to_stream("Term");
                                                process_minus_minus(symbolTable, scope, yylineno,
                                                iam_in_function, &functions_stack, &$1);}
                                           
        
        | primary                             {print_to_stream("Term");};  

assignexpr: lvalue  ASSIGN  expr    { 
                                        print_to_stream("Assign expression");
                                         
                                        process_assign(symbolTable, scope, yylineno,
                                        iam_in_function, &functions_stack, &$1);
                                    }; 
    
                                   


primary:  lvalue { print_to_stream("Primary");  process_primary(symbolTable, scope, yylineno,iam_in_function, &functions_stack, &$1);   }
          | call {print_to_stream("Primary");}
          | objectdef {print_to_stream("Primary");}
          | LEFT_BRACKETS funcdef RIGHT_BRACKETS  {print_to_stream("Primary");}
          | const {print_to_stream("Primary");} ;

lvalue:   ID                    {print_to_stream("Lvalue"); process_id(symbolTable,scope,yylineno,$1,iam_in_function,&functions_stack,&$$); }
          | LOCALL ID           {print_to_stream("Lvalue"); process_local_id(symbolTable,  scope,  yylineno, $2,  iam_in_function,  &$$);}
          | DOUBLE_COLON ID     {print_to_stream("Lvalue"); process_double_colon_id(symbolTable,$2,yylineno,&$$); }             
          | member {print_to_stream("Lvalue"); $$=NULL;} ; //alliws apaiteitai typos gia to member

member:    lvalue DOT ID {print_to_stream("Member");}
            | lvalue LEFT_SQUARE expr RIGHT_SQUARE {print_to_stream("Member");}
            | call DOT ID {print_to_stream("Member");}
            | call LEFT_SQUARE expr RIGHT_SQUARE {print_to_stream("Member");} ;

call:      call LEFT_BRACKETS elist RIGHT_BRACKETS {print_to_stream("Call");} 
            | lvalue callsuffix { print_to_stream("Call");
                process_callsuffix(symbolTable, scope,  yylineno,  iam_in_function, 
                &functions_stack, &$1);

                                }
            | LEFT_BRACKETS funcdef RIGHT_BRACKETS LEFT_BRACKETS elist RIGHT_BRACKETS {print_to_stream("Call");}
            | LEFT_BRACKETS funcdef RIGHT_BRACKETS LEFT_BRACKETS  RIGHT_BRACKETS {print_to_stream("Call");}
            | call LEFT_BRACKETS  RIGHT_BRACKETS;

callsuffix: normcall {print_to_stream("Call Suffix");}
            | methodcall {print_to_stream("Call Suffix");} ;

normcall: LEFT_BRACKETS elist RIGHT_BRACKETS {print_to_stream("Normal Call");}
          |LEFT_BRACKETS  RIGHT_BRACKETS {print_to_stream("Normal Call");};
methodcall:Diaeresis ID LEFT_BRACKETS elist RIGHT_BRACKETS {print_to_stream("Method Call");} /* equivalent to lvalue.ID'('lvalue, elist')';*/
           |Diaeresis ID LEFT_BRACKETS  RIGHT_BRACKETS {print_to_stream("Method Call");}
elist:   expr   {print_to_stream("Expression List");} 
        | expr COMMA elist {print_to_stream("Expression List");};
         
            
objectdef: LEFT_SQUARE  elist  RIGHT_SQUARE     {print_to_stream("Object Definition");}
           |LEFT_SQUARE  indexed  RIGHT_SQUARE {print_to_stream("Object Definition");}
           |LEFT_SQUARE  RIGHT_SQUARE {print_to_stream("Object Definition");};

indexed:    indexedelem  {print_to_stream("Indexed");}
            | indexedelem COMMA  indexed {print_to_stream("Indexed");};
           

indexedelem: LEFT_BRACE expr COLON expr RIGHT_BRACE {print_to_stream("Index Element");};

block: LEFT_BRACE {scope++;}  RIGHT_BRACE  {print_to_stream("Block"); symbolTable_hide(symbolTable, scope); scope--;}       
       |LEFT_BRACE {scope++;}  statements  RIGHT_BRACE {print_to_stream("Block"); symbolTable_hide(symbolTable, scope); scope--;} ;  
       
block_func: LEFT_BRACE {iam_in_function++;enum func_loops entry = func; push_func_loop(   entry  );}  RIGHT_BRACE  {print_to_stream("Function Block");  symbolTable_hide(symbolTable, scope);
 scope--; iam_in_function--;   pop(&functions_stack);    pop_func_loop();   }       
       |LEFT_BRACE {iam_in_function++;enum func_loops entry = func; push_func_loop(   entry  );}    statements  RIGHT_BRACE {print_to_stream("Function Block");  symbolTable_hide(symbolTable, scope); scope--;  iam_in_function--;
     pop(&functions_stack);  pop_func_loop();  } ;  
  

funcdef: FUNCTION   ID  { process_function_id(symbolTable,  scope,  yylineno, $2,  &iam_in_function, &functions_stack  );

                        } LEFT_BRACKETS {scope++;}  idlist   RIGHT_BRACKETS  block_func {print_to_stream("Function Definition");} 
                                                                
         |FUNCTION {   process_anonymous_function(symbolTable,  scope,  yylineno, &functions_stack); 

                            }
                            LEFT_BRACKETS {scope++;} idlist RIGHT_BRACKETS block_func {print_to_stream("Function Definition");}; 
                                                                  

const:  INTEGER {print_to_stream("Integer");}
        |FLOAT  {print_to_stream("Float");}
        | STRING  {print_to_stream("String");}
        | NIL {print_to_stream("NIL");}
        | TRUE {print_to_stream("TRUE");}
        | FALSE {print_to_stream("FALSE");};

idlist: ID  { print_to_stream("ID List");  process_function_arguments(symbolTable,scope,yylineno,$1);                     

                                           
            }
            |   ID { process_function_arguments(symbolTable,scope,yylineno,$1); 
            }  COMMA idlist  {print_to_stream("ID List");}
        
            |    {print_to_stream("ID List");};

ifstmt: IF LEFT_BRACKETS expr RIGHT_BRACKETS stmt  ELSE stmt {print_to_stream("If Statement");} 
        | IF LEFT_BRACKETS expr RIGHT_BRACKETS stmt {print_to_stream("If Statement");} 
whilestmt: WHILE LEFT_BRACKETS {iam_in_loop++; enum func_loops entry = while_loop; push_func_loop(   entry  ); } expr RIGHT_BRACKETS stmt {print_to_stream("While Statement"); 
        iam_in_loop--;   pop_func_loop();                                };

forstmt:  FOR LEFT_BRACKETS {iam_in_loop++;enum func_loops entry = for_loop; push_func_loop(   entry  );} elist SEMICOLON  expr SEMICOLON  elist RIGHT_BRACKETS stmt 
                            { print_to_stream("For Statement"); iam_in_loop--;  pop_func_loop(); }
        |  FOR LEFT_BRACKETS {iam_in_loop++;enum func_loops entry = for_loop; push_func_loop(   entry  );}     SEMICOLON  expr SEMICOLON   RIGHT_BRACKETS stmt   
                            {print_to_stream("For Statement"); iam_in_loop--; pop_func_loop();};  
        
            
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
    yyparse() ;
    //symbolTable_print(symbolTable);
    //symbolTable_print_scope_list(symbolTable, 1);
    symbolTable_print_scopes(symbolTable,100);
    if(output_file!=NULL)
    fclose(output_file);
    fclose(yyin);
}

