%{
#include "bison_functions.h"
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
/*%type <exprNode> funcdef 
%type <exprNode> call  
%type <exprNode> member  

%type <num> assignexpr
%type <num> term*/

%%         
program: statements   ;
stmt:   expr SEMICOLON   {printf("Statement\n");}  
        | ifstmt         {print_to_stream("If Statement");  }
        | whilestmt      {print_to_stream("While Statement");}
        | forstmt        {printf("For Statement\n");}
        | returnstmt     {printf("Return Statement\n");}
        | BREAK SEMICOLON {         if(iam_in_loop==0)
                                    {
                                        print_Red(); 

                                        fprintf(stderr,"Error in line %d: use BREAK not in a loop\n",yylineno); 
                                       reset_Red();
                                    } 
        
                            }
        | CONTINUE SEMICOLON {      if(iam_in_loop==0)
                                    {
                                        print_Red(); 

                                        fprintf(stderr,"Error in line %d:use CONTINUE not in a loop\n",yylineno); 
                                       reset_Red();
                                    } 
                            }
        | block
        | funcdef           {printf("Function definition\n");}
        |SEMICOLON
        ;
statements: statements stmt
            |stmt;

expr:   assignexpr {printf("Assign expression\n");}
        |expr PLUS expr
        |expr MINUS expr
        |expr ASTERISK expr
        |expr DIVISION expr
        |expr PERCENT expr
        |expr GREATER expr
        |expr GREATER_EQUALS expr
        |expr LESS  expr
        |expr LESS_EQUALS expr
        |expr EQUALS expr
        |expr DIFFERENT expr
        |expr AND expr
        |expr OR expr
        | term;

        

term:   LEFT_BRACKETS expr RIGHT_BRACKETS
        | MINUS expr %prec UMINUS  {  
                                           

        }
                                           
        
        | NOT expr{                        
                                           
        }
        | PLUS_PLUS lvalue  {               if(is_function($2) )
                                            {
                                                print_Red();
                                                fprintf(stderr, "Error in line %d: can't use ++ operator to function\n",yylineno);
                                                reset_Red();

                                            }
                            }
        | lvalue PLUS_PLUS  {               if(is_function($1) )
                                            {
                                                print_Red();
                                                fprintf(stderr, "Error in line %d: can't use ++ to function\n",yylineno);
                                                reset_Red();
                                            }
                            }
        | MINUS_MINUS lvalue{
                                            if(is_function($2) )
                                            {
                                                print_Red();
                                                fprintf(stderr, "Error in line %d: can't use -- to function\n",yylineno);
                                                reset_Red();
                                            }
        }
        | lvalue MINUS_MINUS {
                                            if(is_function($1) )
                                            {
                                                print_Red();
                                                fprintf(stderr, "Error in line %d: can't use -- to function\n",yylineno);
                                                reset_Red();
                                            }
        }
        | primary ;

assignexpr: lvalue  ASSIGN  expr    {
                                        if(is_function($1))
                                        {
                                            print_Red();
                                            fprintf(stderr, "Error in line %d: assign to function\n",yylineno);
                                            reset_Red();
                                        }    
                                        
                                    }  
    
                                   


primary:  lvalue
          | call
          | objectdef
          | LEFT_BRACKETS funcdef RIGHT_BRACKETS 
          | const ;

lvalue:   ID                    {process_id(symbolTable,scope,yylineno,$1,iam_in_function,&functions_stack,$$);}
          | LOCALL ID           { process_local_id(symbolTable,  scope,  yylineno, $2,  iam_in_function,  $$);}
          | DOUBLE_COLON ID     { process_double_colon_id(symbolTable,$2,yylineno); }             
          | member {$$=NULL;} ; //alliws apaiteitai typos gia to member

member:    lvalue DOT ID
            | lvalue LEFT_SQUARE expr RIGHT_SQUARE
            | call DOT ID
            | call LEFT_SQUARE expr RIGHT_SQUARE ;

call:      call LEFT_BRACKETS elist RIGHT_BRACKETS  
            | lvalue callsuffix {  if(!is_function($1) ) {
                                    print_Red(); 
                                    fprintf(stderr,"Error in line %d : can't use variable as function\n",yylineno); 
                                    reset_Red();
            }            }
            | LEFT_BRACKETS funcdef RIGHT_BRACKETS LEFT_BRACKETS elist RIGHT_BRACKETS ;

callsuffix: normcall
            | methodcall ;

normcall: LEFT_BRACKETS elist RIGHT_BRACKETS;

methodcall:    Diaeresis ID LEFT_BRACKETS elist RIGHT_BRACKETS; /* equivalent to lvalue.ID'('lvalue, elist')';*/

elist:   expr    
        | expr COMMA elist
        |    ;  
            
objectdef: LEFT_SQUARE  elist  RIGHT_SQUARE     {   printf("elist\n");    }
           |LEFT_SQUARE  indexed  RIGHT_SQUARE {   printf("indexed\n");    };
           

indexed:    indexedelem  
            | indexedelem COMMA  indexed
            |   ;

indexedelem: LEFT_BRACE expr COLON expr RIGHT_BRACE;

block: LEFT_BRACE {scope++;}  RIGHT_BRACE  {symbolTable_hide(symbolTable, scope); scope--;}       
       |LEFT_BRACE {scope++;}  statements  RIGHT_BRACE {symbolTable_hide(symbolTable, scope); scope--;} ;  
       
block_func: LEFT_BRACE {iam_in_function++;}  RIGHT_BRACE  {symbolTable_hide(symbolTable, scope); scope--; iam_in_function--;printf("lala\n"); 
pop(&functions_stack); printf("lala\n");}       
       |LEFT_BRACE {iam_in_function++;}    statements  RIGHT_BRACE {symbolTable_hide(symbolTable, scope); scope--;  iam_in_function--;
       printf("lala\n"); pop(&functions_stack); printf("lala2\n"); } ;  
  

funcdef: FUNCTION   ID  { process_function_id(symbolTable,  scope,  yylineno, $2,  iam_in_function, &functions_stack  );

                        } LEFT_BRACKETS {scope++;}  idlist   RIGHT_BRACKETS  block_func 
                                                                
         |FUNCTION {   process_anonymous_function(symbolTable,  scope,  yylineno, &functions_stack); 

                            }
                            LEFT_BRACKETS {scope++;} idlist RIGHT_BRACKETS block_func 
                                                                  

const:  INTEGER {printf("Integer\n");};
        |FLOAT  {printf("Float\n");};
        | STRING 
        | NIL 
        | TRUE 
        | FALSE;

idlist: ID  {  process_function_arguments(symbolTable,scope,yylineno,$1);                     

                                           
            }
            |   ID {                   process_function_arguments(symbolTable,scope,yylineno,$1); 
            }  COMMA idlist
        
            |   ;

ifstmt: IF LEFT_BRACKETS expr RIGHT_BRACKETS stmt  ELSE stmt   { /*printf("if statement\n");*/ }
        | IF LEFT_BRACKETS expr RIGHT_BRACKETS stmt; 
whilestmt: WHILE LEFT_BRACKETS {iam_in_loop++;} expr RIGHT_BRACKETS stmt {iam_in_loop--;};

forstmt:  FOR LEFT_BRACKETS {iam_in_loop++;} elist SEMICOLON  expr SEMICOLON  elist RIGHT_BRACKETS stmt {iam_in_loop--;};

returnstmt: RETURN expr SEMICOLON { 
                                    if(iam_in_function==0)
                                    {
                                        print_Red(); 

                                        fprintf(stderr,"Error in line %d: return not in a function\n",yylineno); 
                                       reset_Red();
                                    } 
                                    
                                } 
                                    
            |  RETURN SEMICOLON    { 
                                        if(iam_in_function==0)
                                        {
                                            print_Red(); 

                                            fprintf(stderr,"Error in line %d: return not in a function\n",yylineno); 
                                         reset_Red();
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
        yyin=stdin;
    }
  
    symbolTable = symbolTable_create();
    //yylex();
    //yyin=stdin;
    yyparse() ;
    //symbolTable_print(symbolTable);
    //symbolTable_print_scope_list(symbolTable, 1);
    symbolTable_print_scopes(symbolTable,10);
    //if(output_file!=NULL)
    //fclose(output_file);
//    fclose(yyin);
}

