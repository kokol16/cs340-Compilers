
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
    return PLUS ; 
}
{IF}    {
    printf("IF \n");
    return  IF ; 
}
{EQUALS}    {
    printf("find : == \n");
    return EQUALS ; 
}
{LEFT_BRACKETS} {
    printf("find : ( \n");
    return LEFT_BRACKETS ; 
}
{RIGHT_BRACKETS}    {
    printf("find : ) \n");
    return RIGHT_BRACKETS ; 
}
{RIGHT_SQUARE}  {
    printf("right\n");
    return RIGHT_SQUARE ; 
}
{LEFT_SQUARE}   {
    printf("left\n");
    return LEFT_SQUARE ; 
}
{ELSE}  { 
    printf("else\n");              
    return ELSE ; 
}
{ASSIGN}  {
    return ASSIGN;
}         
{MINUS}  {
    return MINUS;
}  
{ASTERISK}  {
    printf("asteri\n");
    return ASTERISK;
}                
{DIVISION}  {
    return DIVISION;
}  
{PERCENT}  {
    return PERCENT;
}                
{DIFFERENT}  {
    return DIFFERENT;
}         
{PLUS_PLUS}  {
    return PLUS_PLUS;
}  
{MINUS_MINUS}  {
    return MINUS_MINUS;
}                
{GREATER}  {
    return GREATER;
}         
{LESS}  {
    return LESS;
}         
{GREATER_EQUALS}  {
    return GREATER_EQUALS;
}         
{LESS_EQUALS}  {
    return LESS_EQUALS;
}         
{LEFT_BRACE}  {
    return LEFT_BRACE;
} 
{RIGHT_BRACE}  {
    return LEFT_BRACE;
}
{SEMICOLON}  {
    return SEMICOLON;
}
{COMMA}  {
    return COMMA;
}
{COLON}  {
    return COLON;
}
{DOUBLE_COLON}  {
    return DOUBLE_COLON;
}
{DOT}  {
    return DOT;
}
{Diaeresis}  {
    return Diaeresis;
}
                

%% 

