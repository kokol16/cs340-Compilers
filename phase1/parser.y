%{

#include"lib.h"

#include <stdio.h>

<<<<<<< HEAD
int yyerror(YYSTYPE   yylval , char * lala);
extern int yyparse(void * yylval);

extern FILE * yyin;
FILE *output_file;
#define YY_DECL int yylex( YYSTYPE  yylval)

extern YY_DECL;


%}
%param {void * yylval}
%start program
%token DIGIT
%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'

%%                 
program: stmt;
stmt:    expr;
expr:   expr op expr
         {
           $$ = $1 + $3;
         } ;
         |
         number
         ;

op : '+'; 


number:  DIGIT
    
         ;
%%

int yyerror(void * yylval , char * lala)
=======



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
>>>>>>> trelh
{

}
int main(int argc , char * argv[])
{
<<<<<<< HEAD
    extern FILE *yyin;

  if(argc==2)
=======
    if(argc==2)
>>>>>>> trelh
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
<<<<<<< HEAD
    alpha_token_t * alpha_head;
    alpha_head=(alpha_token_t *)malloc(sizeof(alpha_token_t));
    alpha_head->alpha_yylex=NULL;
    

    
    
    yyparse(alpha_head);


    alpha_free_tokens_list(alpha_head);
=======
  
    
    //yylex();
    //yyin=stdin;
    yyparse() ;


>>>>>>> trelh
    //if(output_file!=NULL)
    //fclose(output_file);
//    fclose(yyin);
}

