/*lex program to count number of words*/
%{ 
#include<stdio.h> 
#include<string.h> 
#include"test.h"
#define YY_DECL int yylex(YYSTYPE * test)
%} 
/*keep current line */
%option yylineno
ID  [a-zA-Z_][a-zA-Z_0-9]*





/* Rules Section*/
%% 
{ID}   {printf("ID :  %s\n",yytext) ;} /* Rule for counting number of words yylval->count++*/

%% 
  
int yywrap(void){} 

int main() 
{    
    Test test;
    
    memset(&test,0,sizeof(Test));
    
    // The function that starts the analysis 
    
    yylex(&test); 
   // printf("words : %ui",test.count);
    return 0; 
} 