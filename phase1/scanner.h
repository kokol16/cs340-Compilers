typedef struct alpha_token_t {
  unsigned int     numline;
  unsigned int     numToken;
  char          *content;
  char          *type;
  struct alpha_token_t *alpha_yylex;

}alpha_token_t;

#define  alpha_ptr ( (alpha_token_t * )yylval )

void  alpha_CreateInfo(void* yylval ,  char * identifier , unsigned int  counter)
{
    
    alpha_ptr->numline=yylineno;
    alpha_ptr->numToken=counter;
    int length = strlen(yytext)+1;
    alpha_ptr->content=malloc(sizeof(char) * length);
    memcpy ( alpha_ptr->content , yytext , length);

    int length_type= strlen(identifier)+1;
    alpha_ptr->type=malloc(sizeof(char) * length_type);
    memcpy ( alpha_ptr->type , identifier , length_type);

   

}
alpha_token_t * alpha_CreateNextNode(void* yylval)
{
    static alpha_token_t * alpha_node ;
            
    alpha_node=(alpha_token_t *)malloc(sizeof(alpha_token_t));
           
    alpha_ptr->alpha_yylex=alpha_node;
    return  alpha_ptr->alpha_yylex;

}