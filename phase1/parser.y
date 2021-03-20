%{

#include"lib.h"

#include <stdio.h>

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
{

}
int main(int argc , char * argv[])
{
    extern FILE *yyin;

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
    alpha_token_t * alpha_head;
    alpha_head=(alpha_token_t *)malloc(sizeof(alpha_token_t));
    alpha_head->alpha_yylex=NULL;
    

    
    
    yyparse(alpha_head);


    alpha_free_tokens_list(alpha_head);
    //if(output_file!=NULL)
    //fclose(output_file);
//    fclose(yyin);
}

