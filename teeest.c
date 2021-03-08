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
    
    printf("lala");

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