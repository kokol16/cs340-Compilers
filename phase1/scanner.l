
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
%option case-insensitive 
%x COMMENT INCLUDE

ID  [a-zA-Z][a-zA-Z_0-9]*
INT [0-9][0-9]*
REAL [0-9]+[.][0-9]+
STRING \"[^\n"]*\"  
ONELINECOMMENTT "//".*         
/*\"[^"\n]∗\"  */
/* Rules Section*/


%% 
\n   {
       
}
if|else|while|for|function|return|break|continue|and|not|or|local|true|false|nil  {
            alpha_CreateData("KEYWORD",yylval);


}
{STRING}    {
            alpha_CreateData("STRING",yylval);


} 
{REAL}    {
            alpha_CreateData("REALCONST",yylval);


} 
{INT}    {
            alpha_CreateData("INTCONST",yylval);


} 
{ID}    {
            alpha_CreateData("IDENT",yylval);

} 
=   {
            alpha_CreateData("OPERATOR",yylval);

}
==  {
            alpha_CreateData("OPERATOR",yylval);

}
>=  {
            alpha_CreateData("OPERATOR",yylval);

}
%  {
            alpha_CreateData("OPERATOR",yylval);

}
"++"  {
            alpha_CreateData("OPERATOR",yylval);

}

"{" {
            alpha_CreateData("PUNCTUATION",yylval);

}
";" {
            alpha_CreateData("PUNCTUATION",yylval);
}

{ONELINECOMMENTT}   {
            alpha_CreateData("COMMENT",yylval);
}

"/*"    {
    int c;
    int nested=0;
    //printf("opened multti line  comment\n");
    int start_line;
    int last_line;
    while((c=input())!=EOF )
    {
        if(c=='*')
        {
            if((c=input())=='/' )
            {
                if(nested==0)
                {
                    alpha_CreateData("COMMENT",yylval);
                    //printf("closed one multi line  comment\n");
                    break;
                }
                else
                {
                    alpha_CreateData("NESTED COMMENT",yylval);
                    //printf("closed one nested comment\n");

                    nested--;
                }    
            }
            else
            {
                unput(c);
            }
        }
        else if(c=='/')
        {
             if((c=input())=='*' )
            {
                nested++;
                //printf("open one nested comment\n");
            }
            else
            {
                unput(c);
            }
        }
    }


}
%% 
void alpha_CreateData(char * operator , void * yylval)
{
    alpha_token_t * tmp;
    if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
     else                {   tmp = alpha_CreateNextNode(yylval); }
    alpha_CreateInfo(tmp , operator,++counter);
}

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