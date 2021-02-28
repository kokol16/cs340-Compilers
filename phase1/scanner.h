typedef struct alpha_token_t
{
  unsigned int numline;
  unsigned int numToken;
  char *content;
  char *type;
  struct alpha_token_t *alpha_yylex;

} alpha_token_t;
#define alpha_ptr ((alpha_token_t *)yylval)

void alpha_CreateInfo(void *yylval, char *identifier, unsigned int counter)
{
  alpha_ptr->numline = yylineno;
  alpha_ptr->numToken = counter;
  if (strcmp(identifier,"COMMENT")==0)
  {
    alpha_ptr->content = malloc(2*sizeof(char) );
    memcpy(alpha_ptr->content, "\"\"", 2);
  }
  else
  {
    int length = strlen(yytext) + 1;
    alpha_ptr->content = malloc(sizeof(char) * length);
    memcpy(alpha_ptr->content, yytext, length);
  }

  int length_type = strlen(identifier) + 1;
  alpha_ptr->type = malloc(sizeof(char) * length_type);
  memcpy(alpha_ptr->type, identifier, length_type);
}
alpha_token_t *alpha_CreateNextNode(void *yylval)
{
  alpha_token_t *alpha_node, *tmp;

  alpha_node = (alpha_token_t *)malloc(sizeof(alpha_token_t));
  alpha_node->alpha_yylex = NULL;
  tmp = alpha_ptr;

  while (tmp->alpha_yylex != NULL)
  {
    tmp = tmp->alpha_yylex;
  }

  tmp->alpha_yylex = alpha_node;
  return tmp->alpha_yylex;
}

/*
            alpha_ptr->numline=yylineno;
            alpha_ptr->numToken=++counter;
            int length = strlen(yytext)+1;
            alpha_ptr->content=malloc(sizeof(char) * length);
            strncpy ( alpha_ptr->content , yytext , length);

            int length_type= strlen("KEYWORD")+1;
            alpha_ptr->type=malloc(sizeof(char) * length_type);
            strncpy ( alpha_ptr->type , "KEYWORD" , length_type);*/

/*alpha_token_t * alpha_node ;
            
            alpha_node=(alpha_token_t *)malloc(sizeof(alpha_token_t));
           
            alpha_ptr->alpha_yylex=alpha_node;
            yylval= alpha_ptr->alpha_yylex;*/

/*
            alpha_ptr->numline=yylineno;
            alpha_ptr->numToken=++counter;
            int length = strlen(yytext)+1;
            alpha_ptr->content=malloc(sizeof(char) * length);
            strncpy ( alpha_ptr->content , yytext , length);

            int length_type= strlen("IDENT")+1;
            alpha_ptr->type=malloc(sizeof(char) * length_type);
            strncpy ( alpha_ptr->type , "IDENT" , length_type);*/

//printf("ID :  %s\n",yytext) ;

/* alpha_token_t * alpha_node ;
            
            alpha_node=(alpha_token_t *)malloc(sizeof(alpha_token_t));
           
            alpha_ptr->alpha_yylex=alpha_node;
            yylval= alpha_ptr->alpha_yylex;*/

/*
10 omorfos l++alla% 214.4 hafdhfd 
for 0.3432 ; "fsdsfad\nfsd" 432.//
6 "fsdfsda" //1213.43;
//"ok bro" sda
//"fdsfds"
"ds\n\tad"
*/