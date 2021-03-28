%{
#include"symbolTable.h"
#include <stdio.h>
#include "lib.h"
extern FILE * yyin;
extern int yylineno; 
SymbolTable *  symbolTable;
FILE *output_file;
int yylex(void);
int yyerror( char * msg );
unsigned int  scope=0;

%}
%union{
	int num;
    float real;
	char * str;
}
%start program
%token <num> NUMBER
%token <real> REAL
%token <str> ID
%token  <str>  IF ELSE WHILE FOR FUNCTION RETURN  BREAK CONTINUE AND  NOT  OR  LOCAl TRUE FALSE NIL STRING EQUALS PLUS
%token <str>ASSIGN MINUS UMINUS ASTERISK DIVISION PERCENT DIFFERENT PLUS_PLUS MINUS_MINUS GREATER LESS GREATER_EQUALS LESS_EQUALS
%token <str>SEMICOLON COMMA COLON DOUBLE_COLON DOT Diaeresis LEFT_BRACE RIGHT_BRACE LEFT_SQUARE RIGHT_SQUARE LEFT_BRACKETS RIGHT_BRACKETS  
%right ASSIGN
%left OR
%left AND 
%nonassoc EQUALS DIFFERENT  
%nonassoc GREATER GREATER_EQUALS LESS_EQUALS LESS
%left PLUS MINUS
%left ASTERISK  PERCENT
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left DOT Diaeresis
%left LEFT_SQUARE RIGHT_SQUARE
%left LEFT_BRACKETS RIGHT_BRACKETS

%%         
program: statements   ;
stmt:   expr SEMICOLON   {printf("colon end\n");}  /*trexei xwris to SEMICOLON*/
        | ifstmt 
        | whilestmt 
        | forstmt 
        | returnstmt
        | BREAK SEMICOLON
        | CONTINUE SEMICOLON
        | block
        | funcdef
        |SEMICOLON
        ;
statements: statements stmt
            |stmt;

expr:   assignexpr
        |expr op expr
        | term;

op:     PLUS
        | MINUS 
        | ASTERISK 
        | DIVISION
        | PERCENT 
        | GREATER 
        | GREATER_EQUALS 
        | LESS 
        | LESS_EQUALS 
        | EQUALS 
        | DIFFERENT
        | AND 
        | OR;
        

term:   LEFT_BRACKETS expr RIGHT_BRACKETS
        | MINUS expr %prec UMINUS
        | NOT expr
        | PLUS_PLUS lvalue
        | lvalue PLUS_PLUS
        | MINUS_MINUS lvalue
        | lvalue MINUS_MINUS
        | primary ;

assignexpr: lvalue ASSIGN expr  {printf("assign\n");}

primary:  lvalue
          | call
          | objectdef
          | LEFT_BRACKETS funcdef RIGHT_BRACKETS 
          | const ;

lvalue:   ID
          | LOCAl ID
          | DOUBLE_COLON ID
          | member ;

member:    lvalue DOT ID
            | lvalue LEFT_SQUARE expr RIGHT_SQUARE
            | call DOT ID
            | call LEFT_SQUARE expr RIGHT_SQUARE ;

call:      call LEFT_BRACKETS elist RIGHT_BRACKETS
            | lvalue callsuffix
            | LEFT_BRACKETS funcdef RIGHT_BRACKETS LEFT_BRACKETS elist RIGHT_BRACKETS;

callsuffix: normcall
            | methodcall ;

normcall: LEFT_BRACKETS elist RIGHT_BRACKETS;

methodcall:    Diaeresis ID LEFT_BRACKETS elist RIGHT_BRACKETS; /* equivalent to lvalue.ID'('lvalue, elist')';*/

elist:   expr    
        | expr COMMA elist
        |    ;

objectdef: LEFT_SQUARE  elist  RIGHT_SQUARE
           |LEFT_SQUARE  indexed  RIGHT_SQUARE
           |LEFT_SQUARE RIGHT_SQUARE ;

indexed:    indexedelem  
            | indexedelem COMMA  indexed
            |   ;

indexedelem: LEFT_BRACE expr COLON expr RIGHT_BRACE;

block: LEFT_BRACE {scope++;}  RIGHT_BRACE  {scope--;}       
       |LEFT_BRACE {scope++;}  statements  RIGHT_BRACE {scope--;} ;  
       
block_func: LEFT_BRACE  RIGHT_BRACE  {scope--;}       
       |LEFT_BRACE   statements  RIGHT_BRACE {scope--;} ;  
  

funcdef: FUNCTION  ID LEFT_BRACKETS {scope++;}  idlist RIGHT_BRACKETS block_func {
                                                                    Function * func;
                                                                    Variable **arguments;
                                                                    unsigned int size;
                                                                    arguments=sanitize_arguments((char*)$3, &size,scope,yylineno);
                                                                    SymbolTableEntry * bucket;
                                                                    func=create_func($2 , scope , yylineno,arguments,size);
                                                                    free(arguments);
                                                                    bucket=create_bucket_func( 1 ,  func  ,USERFUNC );
                                                                    print_args(func);
                                                                    symbolTable_insert(symbolTable, bucket);
                                                                    }
                                                                
         |FUNCTION LEFT_BRACKETS {scope++;} idlist RIGHT_BRACKETS block_func {
                                                                    Function * func;
                                                                    Variable **arguments;
                                                                    unsigned int size;
                                                                    arguments=sanitize_arguments((char*)$2, &size,scope,yylineno);
                                                                    SymbolTableEntry * bucket;
                                                                    func=create_func(NULL , scope , yylineno,arguments,size);
                                                                    free(arguments);
                                                                    bucket=create_bucket_func( 1 ,  func  ,USERFUNC );
                                                                    print_args(func);
                                                                    symbolTable_insert(symbolTable, bucket);};

const: NUMBER | STRING | NIL | TRUE | FALSE;

idlist: ID  {}
        | ID COMMA idlist { printf("multtiple arguemnts\n");}
        |   ;

ifstmt: IF LEFT_BRACKETS expr RIGHT_BRACKETS stmt  ELSE stmt   { printf("if statement\n"); }
        | IF LEFT_BRACKETS expr RIGHT_BRACKETS stmt; 
whilestmt: WHILE LEFT_BRACKETS expr RIGHT_BRACKETS stmt;

forstmt:  FOR LEFT_BRACKETS elist SEMICOLON  expr SEMICOLON  elist RIGHT_BRACKETS stmt;

returnstmt: RETURN expr {printf("return\n");} 
            |  RETURN;


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
            fprintf(stderr,"error can't read file\n");
            return -1;
        }   
        
    }
    else if (argc>2)
    {
        if(!( yyin=fopen(argv[1],"r") )  )
        {
            fprintf(stderr,"error can't read file\n");
            return -1;
        } 
        output_file=fopen(argv[2],"w");
        if(output_file==NULL)
        {
            fprintf(stderr,"error can't open write file\n");
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
    symbolTable_print_scope_list(symbolTable, 0);

    //if(output_file!=NULL)
    //fclose(output_file);
//    fclose(yyin);
}

