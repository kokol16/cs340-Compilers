
%{ 
#include "lib.h"
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
LOCAl           local 
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




ONELINECOMMENTT "//".*         
/* Rules Section*/

%% 
{FUNCTION}    {
    //printf("FUNCTION \n");
     yylval.str=yytext;
    return FUNCTION;
}

{INT}       {
        yylval.num=atoi(yytext);  return NUMBER ;
}
{REAL}       {
     yylval.real=atof(yytext); return REAL ;
}
{WHILE}       {
      return WHILE ;
}
{FOR}       {
      return FOR ;
}

{RETURN}       {
      return RETURN ;
}
{BREAK}       {
      return BREAK ;
}
{CONTINUE}       {
      return CONTINUE ;
}
{AND}       {
      return AND ;
}
{NOT}       {
      return NOT ;
}
{OR}       {
      return OR ;
}
{LOCAl}       {
      return LOCAl ;
}
{TRUE}       {
      return TRUE ;
}
{FALSE}       {
      return FALSE ;
}
{NIL}       {
      return NIL ;
}

{PLUS}      {
    //printf("plus \n");
    return PLUS ; 
}
{IF}        {
    //printf("IF \n");
    return  IF ; 
}
{EQUALS}    {
    //printf("find : == \n");
    return EQUALS ; 
}
{LEFT_BRACKETS} {
    //printf("find : ( \n");
    yylval.str=yytext;
    return LEFT_BRACKETS ; 
}
{RIGHT_BRACKETS}    {
    //printf("find : ) \n");
     yylval.str=yytext;
    return RIGHT_BRACKETS ; 
}
{RIGHT_SQUARE}  {
    //printf("right\n");
    return RIGHT_SQUARE ; 
}
{LEFT_SQUARE}   {
    //printf("left\n");
    return LEFT_SQUARE ; 
}
{ELSE}  { 
    //printf("else\n");              
    return ELSE ; 
}
{ASSIGN}  {
    return ASSIGN;
}         
{MINUS}  {
    return MINUS;
}  
{ASTERISK}  {
    //printf("asteri\n");
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
    yylval.str=yytext;  return LEFT_BRACE;
} 
{RIGHT_BRACE}  {
    yylval.str=yytext;   return RIGHT_BRACE;
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
\"    {
            /* optimization if(c==n || c==t ...) */
            int start_line=yylineno;
            int c;
            unsigned int max_size=30;
            short is_closed=0;
            char * str=malloc(max_size*sizeof(char));
            int index=0;
            int x;
            int  slash_counter=0;
            while((c=input())>MY_EOF )
            {

                if(c=='\"' )
                {
                    
                    
                    if(index==0){break;}/* empty string*/
                    if((slash_counter % 2) == 0)
                    {
                        break;
                    }
                    

                }
                else if(c=='\\')
                {
                    slash_counter++;
                    c=input();
                    if(c=='n')
                    {
                        
                        if((slash_counter % 2) != 0)
                        {

                            str[index++]='\n';

                        }

                       
                        slash_counter=0;

                    }
                    else if(c=='t')
                    {

                        if((slash_counter % 2) != 0)/* cases like \\t */
                        {
                            str[index++]='\t';

                        }
                        slash_counter=0;

                    }
                    else if(c=='\"')
                    {
                        if((slash_counter % 2) != 0)
                        {
                            str[index++]='\"';
                        }
                       
                        
                        slash_counter=0;
                       
                    }
                    else
                    {
                        
                        if(c!='\\') /*  \\ is not a warning */
                        {
                            /* unsupported \x characters only warning */
                            print_Yellow();
                            fprintf(stderr,"warning invalid escape character %c\n",c);
                            reset_Yellow();
                            unput(c);

                        }
                        else
                        {
                            slash_counter++;
                        }

                        str[index++]='\\';

                    }
                }
                else
                {

                    str[index++]=c;
                    slash_counter=0;
                }

                if(index==max_size)/* check if we need to expand string size*/
                {
                    max_size*=2;
                    str = realloc(str, max_size* sizeof(char));
                   
                }
            }
            if(c<=MY_EOF){ /* String never closed case*/
                print_Red();
                fprintf(stderr , "String that started on line %d didn't close\n",start_line);
                reset_Red();
            }
            else
            {
                if(index==0) /* "" is warning as a zero length string */
                {
                    print_Yellow();
                    fprintf(stderr,"warning zero length string in line %d \n",yylineno);
                    reset_Yellow();
                }
                str[index]='\0';
                //alpha_token_t * tmp =   alpha_CreateData("STRING",yylval,str,start_line);
                //alpha_PrintData(tmp ,"<-char*" );

            }
            
            //free(str);
        yylval.str = malloc(sizeof(char)* (strlen(str)+1 ))    ;
        memcpy( yylval.str  , str ,strlen(str)+1 );
        return STRING;

} 


{ID}        {
    //printf("ID \n");
    yylval.str=strdup(yytext);     return ID;
}    


" "  {

}
\t  {

}
\v  {

}
\r  {
    
}
\n   {
       
}   
.           {
    print_Red();
    fprintf(stderr , "undefined  input %s in line : %d \n",yytext ,yylineno);
    reset_Red();
}

%% 

