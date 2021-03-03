
%{ 
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

/*STRING \"[^\n"]∗\"  */
STRING \"[^"\n]*\"

ONELINECOMMENTT "//".*         
/* Rules Section*/

%% 



\n   {
       
}
if|else|while|for|function|return|break|continue|and|not|or|local|true|false|nil  {
        alpha_token_t * tmp =    alpha_CreateData("KEYWORD",yylval,"IF",yylineno);

        alpha_PrintData(tmp ,"<-enumerated" );

}
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
{STRING}    {
            unsigned int index=0,str_index=0;
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
            string[str_index]='\0';
            //printf("length : %d\n",yyleng);
            //printf("char : %c\n",yytext[9]);
            //printf("length : %d\n",strlen(yytext));
            printf("%s\n",string);
            //printf("\n");
            alpha_token_t * tmp =   alpha_CreateData("STRING",yylval,string,yylineno);

            alpha_PrintData(tmp ,"<-char*" );

} 
=   {
          alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"ASSIGN",yylineno);

            alpha_PrintData(tmp ,"<-enumerated" );

}
==  {
           alpha_token_t * tmp =   alpha_CreateData("OPERATOR",yylval,"EQUALS",yylineno);
            alpha_PrintData(tmp ,"<-enumerated" );


}
>=  {
          alpha_token_t * tmp =   alpha_CreateData("OPERATOR",yylval,"GREATER_EQUALS",yylineno);
            alpha_PrintData(tmp ,"<-enumerated" );

}
%  {
          alpha_token_t * tmp =    alpha_CreateData("OPERATOR",yylval,"PERCENTAGES",yylineno);
            alpha_PrintData(tmp ,"<-enumerated" );

}
"++"  {
           alpha_token_t * tmp =   alpha_CreateData("OPERATOR",yylval,"PLUS_PLUS",yylineno);
            alpha_PrintData(tmp ,"<-enumerated" );

}

"{" {
          alpha_token_t * tmp =   alpha_CreateData("PUNCTUATION",yylval,"LEFT_BRACE",yylineno);
            alpha_PrintData(tmp ,"<-enumerated" );


}
";" {
        alpha_token_t * tmp =    alpha_CreateData("PUNCTUATION",yylval,"SEMICOLON",yylineno);
        alpha_PrintData(tmp ,"<-enumerated" );       
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
    while((c=input())!=0 )
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
        printf("#%*u\t",line_width , node->numToken);
        printf("%*s\t" ,line_width , node->content);
        printf("%*s\t",line_width ,node->type);
        printf("%*s\n" ,line_width ,extra_type); 
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