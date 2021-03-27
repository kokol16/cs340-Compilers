%{

#include"lib.h"

#include <stdio.h>




extern FILE * yyin;
FILE *output_file;
int yylex(void);

int yyerror( char * msg );

%}
%union{
	int num;
	char * str;
}
%start program
%token <num> NUMBER 
%token    IF ELSE WHILE FOR FUNCTION RETURN  BREAK CONTINUE AND  NOT  OR  LOCAL TRUE FALSE NIL STRING  ID EQUALS PLUS
%token ASSIGN MINUS ASTERISK DIVISION PERCENT DIFFERENT PLUS_PLUS MINUS_MINUS GREATER LESS GREATER_EQUALS LESS_EQUALS
%token SEMICOLON COMMA COLON DOUBLE_COLON DOT Diaeresis LEFT_BRACE RIGHT_BRACE LEFT_SQUARE RIGHT_SQUARE LEFT_BRACKETS RIGHT_BRACKETS  
%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'  
%%                 
program: stmt;
stmt:   expr   {printf("hello\n");}  /*trexei xwris to SEMICOLON*/
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
        | MINUS expr
        | NOT expr
        | PLUS_PLUS lvalue
        | lvalue PLUS_PLUS
        | MINUS_MINUS lvalue
        | lvalue MINUS_MINUS
        | primary ;

assignexpr: lvalue ASSIGN expr ;

primary:  lvalue
          | call
          | objectdef
          | LEFT_BRACKETS funcdef RIGHT_BRACKETS 
          | const ;

lvalue:   ID
          | LOCAL ID
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

elist: LEFT_SQUARE expr LEFT_SQUARE COMMA expr RIGHT_SQUARE  RIGHT_SQUARE;

objectdef: LEFT_SQUARE LEFT_SQUARE elist | indexed RIGHT_SQUARE RIGHT_SQUARE;

indexed: LEFT_SQUARE indexedelem LEFT_SQUARE COMMA indexedelem RIGHT_SQUARE  RIGHT_SQUARE;

indexedelem: LEFT_BRACE expr COLON expr RIGHT_BRACE;

block: LEFT_BRACE LEFT_SQUARE stmt RIGHT_SQUARE RIGHT_BRACE;

funcdef: FUNCTION LEFT_SQUARE ID RIGHT_SQUARE LEFT_BRACKETS idlist RIGHT_BRACKETS block;

const: NUMBER | STRING | NIL | TRUE | FALSE;

idlist:    LEFT_SQUARE ID LEFT_SQUARE COMMA ID RIGHT_SQUARE  RIGHT_SQUARE;

ifstmt: IF LEFT_BRACKETS expr RIGHT_BRACKETS stmt LEFT_SQUARE ELSE stmt RIGHT_SQUARE  { printf("if statement\n"); };

whilestmt: WHILE LEFT_BRACKETS expr RIGHT_BRACKETS stmt;

forstmt:  FOR LEFT_BRACKETS elist SEMICOLON  expr SEMICOLON  elist RIGHT_BRACKETS stmt;

returnstmt: RETURN LEFT_SQUARE expr RIGHT_SQUARE {printf("return\n");} ;



%%

int yyerror( char * msg )
{

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
  
    
    //yylex();
    //yyin=stdin;
    yyparse() ;


    //if(output_file!=NULL)
    //fclose(output_file);
//    fclose(yyin);
}

