typedef struct alpha_token_t {
  unsigned int     numline;
  unsigned int     numToken;
  char          *content;
  char          *type;
  struct alpha_token_t *alpha_yylex;

}alpha_token_t;


alpha_token_t * CreateInfo(char * identifier , unsigned int  counter)
{
    static alpha_token_t tmp_alpha;
    tmp_alpha.numline=yylineno;
    tmp_alpha.numToken=++counter;
    int length = strlen(yytext)+1;
    tmp_alpha.content=malloc(sizeof(char) * length);
    strncpy ( tmp_alpha.content , yytext , length);

    int length_type= strlen(identifier)+1;
    tmp_alpha.type=malloc(sizeof(char) * length_type);
    strncpy ( tmp_alpha.type , identifier , length_type);

    return &tmp_alpha;

}