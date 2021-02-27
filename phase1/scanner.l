
%{ 
#include<stdio.h> 
#include<string.h> 
#include"scanner.h"
#define YY_DECL int alpha_yylex (void * yylval)
#define  alpha_ptr ( (alpha_token_t * )yylval )
static unsigned int counter=0;
%} 
/*keep current line */
%option yylineno

ID  [a-zA-Z][a-zA-Z_0-9]*

/* Rules Section*/
%% 

if|else|while|for|function|return|break|continue|and|not|or|local|true|false|nil  {
            /*
            alpha_ptr->numline=yylineno;
            alpha_ptr->numToken=++counter;
            int length = strlen(yytext)+1;
            alpha_ptr->content=malloc(sizeof(char) * length);
            strncpy ( alpha_ptr->content , yytext , length);

            int length_type= strlen("KEYWORD")+1;
            alpha_ptr->type=malloc(sizeof(char) * length_type);
            strncpy ( alpha_ptr->type , "KEYWORD" , length_type);*/

            alpha_CreateInfo(yylval , "KEYWORD",++counter);

            yylval =alpha_CreateNextNode(yylval);
            
            /*alpha_token_t * alpha_node ;
            
            alpha_node=(alpha_token_t *)malloc(sizeof(alpha_token_t));
           
            alpha_ptr->alpha_yylex=alpha_node;
            yylval= alpha_ptr->alpha_yylex;*/
}
{ID}    {
            
           /*
            alpha_ptr->numline=yylineno;
            alpha_ptr->numToken=++counter;
            int length = strlen(yytext)+1;
            alpha_ptr->content=malloc(sizeof(char) * length);
            strncpy ( alpha_ptr->content , yytext , length);

            int length_type= strlen("IDENT")+1;
            alpha_ptr->type=malloc(sizeof(char) * length_type);
            strncpy ( alpha_ptr->type , "IDENT" , length_type);*/


            alpha_CreateInfo(yylval , "IDENT",++counter);
            //printf("ID :  %s\n",yytext) ;
            yylval =alpha_CreateNextNode(yylval);


            /* alpha_token_t * alpha_node ;
            
            alpha_node=(alpha_token_t *)malloc(sizeof(alpha_token_t));
           
            alpha_ptr->alpha_yylex=alpha_node;
            yylval= alpha_ptr->alpha_yylex;*/

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
    tmp=alpha_head;

    
    alpha_yylex(tmp); 
    printf("\b\b\b\b");
    while(alpha_head->alpha_yylex != NULL)
    {
        printf("%u: ",alpha_head->numline);
        printf(" #%u",alpha_head->numToken);
        printf("\t\"%s\" ",alpha_head->content);
        printf("\t%s ",alpha_head->type);

        printf("\n");
        alpha_head=alpha_head->alpha_yylex;
    }
    return 0; 
} 