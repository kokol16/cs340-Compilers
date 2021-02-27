
%{ 
#include<stdio.h> 
#include<string.h> 
#include"scanner.h"
#define YY_DECL int alpha_yylex (void * yylval)
static unsigned int counter=0;
static short  FirstNode=1;
%} 
/*keep current line */
%option yylineno

ID  [a-zA-Z][a-zA-Z_0-9]*

/* Rules Section*/
%% 

if|else|while|for|function|return|break|continue|and|not|or|local|true|false|nil  {
            alpha_token_t * tmp;
            if(FirstNode==1){    FirstNode=0;    tmp=yylval;             }
            else            {    tmp = alpha_CreateNextNode(yylval);      }
            alpha_CreateInfo(tmp , "KEYWORD",++counter);       
}
{ID}    {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "IDENT",++counter);    
} 
\n

%% 
  
int yywrap(void){} 

int main(int argc , char * argv[]) 
{    
    if(argc>1)
    {
        if(!( yyin=fopen(argv[1],"r") )  )
        {
            fprintf(stderr,"error can't read file\n");
            return -1;
        }   
    }
    else
    {
        yyin=stdin;
    }
    alpha_token_t * alpha_head, *tmp;
    alpha_head=(alpha_token_t *)malloc(sizeof(alpha_token_t));
    alpha_head->alpha_yylex=NULL;
    

    alpha_yylex((void*)alpha_head); 
    //printf("%u: \n",tmp->numline);
    tmp=alpha_head;
    int line_width=10;
    while(tmp != NULL)
    {
        printf("%u: ",tmp->numline);
        printf(" #%u",tmp->numToken);
        printf("\t%s" ,tmp->content);
        printf("\t%*s ",line_width ,tmp->type);

        printf("\n");
        tmp=tmp->alpha_yylex;
    }
    return 0; 
} 