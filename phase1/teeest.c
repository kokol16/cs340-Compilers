#include<stdio.h>

/*

10 omorfos l++alla% 214.4 hafdhfd 
for 0.3432 ; "fsdsfad\nfsd" 432.//
6 "fsdfsda" //1213.43;
//"ok bro" sda
//"fdsfds"
"ds\n\tad"
*/


int main()
{
    
    printf("%f\n",241.);
}

/*
<COMMENT>[^*]*
<COMMENT>"*"+[^*/]*
<COMMENT>"*"+"/"    {
    int last_line=yylineno;
    int init_line=yylineno;
    alpha_token_t * tmp;
    if(FirstNode==1)    {  FirstNode=0;     tmp=yylval;         }
    else                {   tmp = alpha_CreateNextNode(yylval); }
    alpha_CreateInfo(tmp , "COMMENT",++counter);
    
    /*char str[10];
    sprintf(str, "%d", yylineno);
    strcat(str,"\"");
    memcpy(->content , str , sizeof(str));
    printf("last line %d\n",last_line);*/
    BEGIN(INITIAL);
}*/



 /*char str[10];
    tmp->content=malloc(10*sizeof(char) );
    sprintf(str, "%d", yylineno);
    strcat(str,"-");
    memcpy(tmp->content , str , sizeof(str));*/
    //int last_line=yylineno;
    //printf("%d-%d\n",init_line,last_line);



    /*<INITIAL>{
"/*"             BEGIN(COMMENT);
            
} 
<COMMENT>{
"*/"      BEGIN(INITIAL);
[^*\n]+   // eat comment in chunks
"*"       // eat the lone star
\n        yylineno++;
           
}
*/