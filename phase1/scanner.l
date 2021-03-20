
%{ 
#include"lib.h"
#define MY_EOF 0   
#include"y.tab.h"
%} 

/*keep current line */
%option yylineno
%option case-sensitive  
%option noyywrap

ID  [a-zA-Z][a-zA-Z_0-9]*
INT [0-9][0-9]*
REAL [0-9]+[.][0-9]+
IF              if
ELSE            else
WHILE           while
FOR             for 
FUNCTION        function 
RETURN          return
BREAK           break 
CONTINUE        continue
AND             and     
NOT             not 
OR              or 
LOCAL           local 
TRUE            true 
FALSE           false 
NIL             nil

PLUS            "+"
ASSIGN          "=" 
MINUS           "-"
ASTERISK        "*"
DIVISION        "/"
PERCENT         "%"
EQUALS          "=="
DIFFERENT       "!="
PLUS_PLUS       "++"
MINUS_MINUS     "--"
GREATER         ">"
LESS            "<"
GREATER_EQUALS  ">=" 
LESS_EQUALS     "<="
LEFT_BRACE      "{" 
RIGHT_BRACE     "}" 
LEFT_SQUARE     "[" 
RIGHT_SQUARE    "]" 
LEFT_BRACKETS   "("
RIGHT_BRACKETS  ")" 
SEMICOLON       ";" 
COMMA           ","
COLON           ":"
DOUBLE_COLON    "::"
DOT             "." 
Diaeresis       ".."
/*STRING \"[^\n"]∗\"  */

STRING \"(.|\n)*\"

WRONGSTRING \"(.|\n)* 


ONELINECOMMENTT "//".*         
/* Rules Section*/

%% 
{INT}   {
        yylval.num=atoi(yytext);  return NUMBER ;
}
{PLUS}  {
    printf("plus \n");
    return *yytext ; 
}
{IF}    {
    printf("IF \n");
    return  IF ; 
}
{EQUALS}    {
    printf("find : == \n");
    return *yytext ; 
}
"("     {
    printf("find : ( \n");
    return '(' ; 
}
")"    {
    printf("find : ) \n");
    return ')' ; 
}
RIGHT_SQUARE    {
    return *yytext ; 
}
LEFT_SQUARE {
    return *yytext ; 
}
ELSE {
    return *yytext ; 
}
%% 

