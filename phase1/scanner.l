
%{ 
#define MY_EOF 0    
#include<stdio.h> 
#include<string.h> 
#include"scanner.h"
#define YY_DECL int alpha_yylex (void * yylval)

%} 
/*keep current line */
%option yylineno
%option case-insensitive  

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

IF      {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"IF",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

ELSE    {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"ELSE",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

WHILE   {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"WHILE",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

FOR     {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"FOR",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

FUNCTION {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"FUNCTION",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

RETURN  {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"RETURN",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

BREAK   {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"BREAK",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

CONTINUE {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"CONTINUE",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

AND     {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"AND",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

NOT     {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"NOT",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

OR      {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"OR",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

LOCAL   {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"LOCAL",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

TRUE    {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"TRUE",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

FALSE   {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"FALSE",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

NIL     {alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"NIL",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}


{ASSIGN}            {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"ASSIGN",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
    
{PLUS}              {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"PLUS",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
    
{MINUS}             {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"MINUS",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
    
{ASTERISK}          {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"ASTERISK",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
    
{DIVISION}          {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"DIVISION",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{PERCENT}          {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"PERCENT",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
    
{EQUALS}        {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"EQUALS",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
    
{DIFFERENT}        {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"DIFFERENT",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

{PLUS_PLUS}    {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"PLUS_PLUS",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

{MINUS_MINUS}    {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"MINUS_MINUS",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

{GREATER}    {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"GREATER",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

{LESS}    {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"LESS",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}

{GREATER_EQUALS}     {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"GREATER_EQUALS",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{LESS_EQUALS}    {alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"LESS_EQUALS",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{LEFT_BRACE}    {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"LEFT_BRACE",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{RIGHT_BRACE}    {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"RIGHT_BRACE",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{LEFT_SQUARE}    {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"LEFT_SQUARE",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{RIGHT_SQUARE}    {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"RIGHT_SQUARE",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{LEFT_BRACKETS}    {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"LEFT_BRACKETS",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{RIGHT_BRACKETS}     {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"RIGHT_BRACKETS",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{SEMICOLON}    {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"SEMICOLON",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{COMMA}    {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"COMMA",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{COLON}    {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"COLON",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{DOUBLE_COLON}    {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"DOUBLE_COLON",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{DOT}    {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"DOT",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}
{Diaeresis}    {alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"Diaeresis",yylineno);alpha_PrintData(tmp ,"<-enumerated" );}


{REAL}    {
          alpha_token_t * tmp =   alpha_CreateData("REALCONST",yylval,yytext,yylineno);

            alpha_PrintData(tmp ,"<-real" );

} 
{INT}    {
          alpha_token_t * tmp =    alpha_CreateData("INTCONST",yylval,yytext,yylineno);
            alpha_PrintData(tmp ,"<-integer" );

} 
{ID}    {
            alpha_token_t * tmp =    alpha_CreateData("IDENT",yylval,yytext,yylineno);
            alpha_PrintData(tmp ,"<-char*" );

} 

\"    {
            /* optimization if(c==n || c==t ...) */
            int start_line=yylineno;
            int c;
            unsigned int max_size=30;
            short is_closed=0;
            char * str=malloc(max_size*sizeof(char));
            int index=0;
            while((c=input())!=0 )
            {
                if(c=='\"'&&index==0){ is_closed=1; break;}
                if(c=='\"' && index-1>=0 &&  str[index-1]!='\\')
                {
                    is_closed=1;
                    break;
                }
                else if(c=='\\')
                {
                    c=input();
                    if(c=='n')
                    {
                        
                        if(  ((index-1)>0 ) && ( str[index-1]=='\\' ) )
                        {

                            str[index++]='n';
                        }
                        else
                        {

                            str[index++]='\n';

                        }

                    }
                    else if(c=='t')
                    {
                        if(index-1>=0 && str[index-1]=='\\')
                        {
                            str[index++]='t';
                        }
                        else
                        {
                            str[index++]='\t';

                        }
                    }
                    else if(c=='\"')
                    {
                        if(index-1>=0 &&  str[index-1]=='\\')
                        {
                            printf("error\n");
                        }
                        else
                        {
                            str[index++]='\"';
                        }
                        
                       
                    }
                    else
                    {
                        if(c!='\\') /*  \\ is not a warning */
                        printf("warning escaped character\n");
                        str[index++]='\\';
                        unput(c);

                    }
                }
                else
                {

                    str[index++]=c;
                }

                if(index==max_size)
                {
                    max_size*=2;
                    str = realloc(str, max_size* sizeof(char));
                   
                }
            }
            if(is_closed==0){
                
                printf("error string didn't close\n");
            }
            else
            {
                if(index==0)
                {
                    printf("warning zero lengtth string\n");
                }
                str[++index]='\0';
                alpha_token_t * tmp =   alpha_CreateData("STRING",yylval,str,start_line);
                alpha_PrintData(tmp ,"<-char*" );

            }
            

            /*
            unsigned int index=1,str_index=0;
            char string[yyleng];
            while(yytext[index]!='\0')
            {
                
                string[str_index]=yytext[index];
                if(yytext[index]=='\\')
                {
                    if(yytext[index+1]=='n')
                    {
                        
                        if(yytext[index-1]!='\\')
                        {
                            string[str_index]='\n';
                            index++;
                        }
                        
                    }
                    else if(yytext[index+1]=='t')
                    {
                        if(yytext[index-1]!='\\')
                        {
                            string[str_index]='\t';
                            index++;
                        }
                        
                    }
                    else if(yytext[index+1]=='\\')
                    {
                        string[str_index]='\\';
                        index++;
                    }
                }
                if(yytext[index]=='\0')
                {
                    break;
                }
                index++;
                str_index++;
            }
            string[str_index-1]='\0';
            alpha_token_t * tmp =   alpha_CreateData("STRING",yylval,yytext,yylineno);
            alpha_PrintData(tmp ,"<-char*" );
            */

} 





{ONELINECOMMENTT}   {
            alpha_token_t * tmp =alpha_CreateData("COMMENT",yylval,"LINE_COMMENT",yylineno);
            alpha_PrintData(tmp ,"<-enumerated" );
            
}

"/*"    {
    /* line_comment to multi_line_comment?? */
    int c;
    int nested=0;
    //printf("opened multti line  comment\n");
   
    alpha_comments_info_t * head;
    head=(alpha_comments_info_t *)malloc(sizeof(alpha_comments_info_t));
    head->next=NULL;
    head->first_line =yylineno;
    while((c=input())!=MY_EOF )
    {
        if(c=='*')
        {
            if((c=input())=='/' )
            {
                if(nested==0)
                {
                    
                    unsigned int first_line= get_first_line(head,nested);
                    alpha_token_t * tmp = alpha_CreateData("COMMENT",yylval,"BLOCK_COMMENT",first_line);
                    alpha_PrintData(tmp ,"<-enumerated" );

                    //printf("closed one multi line  comment\n");
                    break;
                }
                else
                {
                    unsigned int first_line= get_first_line(head,nested);

                    alpha_token_t * tmp = alpha_CreateData("NESTED COMMENT",yylval,"BLOCK_COMMENT",first_line);
                    alpha_PrintData(tmp ,"<-enumerated" );


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
                push_comments_info(head,yylineno);
                nested++;
                //printf("open one nested comment\n");
            }
            else
            {
                unput(c);
            }
        }
    }
    if(c==MY_EOF)
    {
        printf("error comment didn't close\n");
    }
}
" "  {

}
\t  {

}

\r  {
    
}
\n   {
       
}
.   {
    printf("error kanonas\n");
}
%% 
alpha_token_t * alpha_CreateData(char * identifier , void * yylval,char * additional_info , unsigned int start_line)
{
    alpha_token_t * tmp;
    if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
    else                {   tmp = alpha_CreateNextNode(yylval); }
    alpha_CreateInfo(tmp , identifier,additional_info ,start_line);
    return tmp;

}
void alpha_PrintData(alpha_token_t * node ,char * extra_type )
{
        int line_width=10;
        printf("\b");
        printf("%u:\t",node->numline);
        printf("#%u\t", node->numToken);
        printf("\"%s\"\t"  , node->content);
        printf("%s\t" ,node->type);
        if(strcmp(node->type,"STRING")==0 || strcmp(node->type,"IDENT")==0)
        {
            printf("\"%s\"\t",node->content);
        }
        printf("%s\n"  ,extra_type); 
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
   
   /* tmp=alpha_head;
    int line_width=10;
    while(tmp != NULL)
    {
        printf("%u: ",tmp->numline);
        printf(" #%u",tmp->numToken);
        printf("\t%s" ,tmp->content);
        printf("\t%*s ",line_width ,tmp->type);

        printf("\n");
        tmp=tmp->alpha_yylex;
    }*/
    return 0; 
} 