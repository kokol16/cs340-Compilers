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
%token    IF ELSE WHILE FOR FUNCTION RETURN  BREAK CONTINUE AND  NOT  OR  LOCAL TRUE FALSE NIL STRING  ID
%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'  
%%                 
program: stmt;
stmt:   expr;   
        | ifstmt 
        | whilestmt 
        | forstmt 
        | returnstmt
        | BREAK ;
        | CONTINUE;
        | block
        | funcdef
        | ;

expr:   assignexpr
        |expr op expr
        | term;

op:     '+'
        | '-' 
        | '*' 
        | '/' 
        | '%' 
        | '>' 
        | ">=" 
        | '<' 
        | "<=" 
        | "==" 
        | "!=" 
        | AND 
        | OR;
        

term:   '(' expr ')'
        | '-' expr
        | NOT expr
        | "++"lvalue
        | lvalue"++"
        | "--"lvalue
        | lvalue"--"
        | primary ;

assignexpr: lvalue '=' expr ;

primary:  lvalue
          | call
          | objectdef
          | '(' funcdef ')' 
          | const ;

lvalue:   ID
          | LOCAL ID
          | "::" ID
          | member ;

member:    lvalue '.' ID
            | lvalue '[' expr ']'
            | call '.' ID
            | call '[' expr ']' ;

call:      call '(' elist ')'
            | lvalue callsuffix
            | '(' funcdef')' '(' elist ')';

callsuffix: normcall
            | methodcall ;

normcall: '(' elist ')';

methodcall:    ".." ID '(' elist ')'; /* equivalent to lvalue.ID'('lvalue, elist')';*/

elist: '[' expr '['',' expr']'  ']';

objectdef: '[' '['elist | indexed']' ']';

indexed: '['indexedelem '[' ',' indexedelem']'  ']';

indexedelem: '{' expr : expr '}';

block: '{' '['stmt']' '}';

funcdef: FUNCTION '['ID']' '('idlist')' block;

const: NUMBER | STRING | NIL | TRUE | FALSE;

idlist:    '['ID '[' ',' ID']'  ']';

ifstmt: IF '(' expr ')' stmt '[' ELSE stmt ']'  { printf("if statement\n"); };

whilestmt: WHILE '(' expr ')' stmt;

forstmt:  FOR '(' elist';'  expr';'  elist')' stmt;

returnstmt: RETURN '['expr']';



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

