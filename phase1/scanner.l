
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
            alpha_token_t * tmp;
            if(FirstNode==1){    FirstNode=0;    tmp=yylval;             }
            else            {    tmp = alpha_CreateNextNode(yylval);      }
            alpha_CreateInfo(tmp , "KEYWORD",++counter);       
}
{STRING}    {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "STRING",++counter);    
} 
{REAL}    {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "REALCONST",++counter);    
} 
{INT}    {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "INTCONST",++counter);    
} 
{ID}    {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "IDENT",++counter);    
} 
=   {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "OPERATOR",++counter);
}
==  {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "OPERATOR",++counter);
}
>=  {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "OPERATOR",++counter);
}
%  {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "OPERATOR",++counter);
}
"++"  {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "OPERATOR",++counter);
}

"{" {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "PUNCTUATION",++counter);
}
";" {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "PUNCTUATION",++counter);
}

{ONELINECOMMENTT}   {
            alpha_token_t * tmp;
            if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
            else                {   tmp = alpha_CreateNextNode(yylval); }
            alpha_CreateInfo(tmp , "COMMENT",++counter);
}

"/*"       {
    int init_line=yylineno;
    BEGIN(COMMENT);
    alpha_token_t * tmp;
    if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
    else                {   tmp = alpha_CreateNextNode(yylval); }
    alpha_CreateInfo(tmp , "COMMENT",++counter);
    /*char str[10];
    tmp->content=malloc(10*sizeof(char) );
    sprintf(str, "%d", yylineno);
    strcat(str,"-");
    memcpy(tmp->content , str , sizeof(str));*/
    //int last_line=yylineno;
    //printf("%d-%d\n",init_line,last_line);

    

} 
<COMMENT>[^*]*
<COMMENT>"*"+[^*/]*
<COMMENT>"*"+"/"    {
    int last_line=yylineno;
    /*char str[10];
    sprintf(str, "%d", yylineno);
    strcat(str,"\"");
    memcpy(->content , str , sizeof(str));*/
    printf("last line %d\n",last_line);
    BEGIN(INITIAL);
}

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