#include <stdlib.h>
static unsigned int counter = 0;
static short FirstNode = 1;
typedef struct alpha_token_t
{
  unsigned int numline;
  unsigned int numToken;
  char *content;
  char *type;
  struct alpha_token_t *alpha_yylex;

} alpha_token_t;

typedef struct alpha_comments_info_t
{
  unsigned int first_line;
  unsigned int last_line;
  struct alpha_comments_info_t *next;
} alpha_comments_info_t;

#define DOUBLE_SPACE 3
#define alpha_ptr ((alpha_token_t *)yylval)
alpha_token_t *alpha_CreateData(char *identifier, void *yylval, char *additional_info, unsigned int start_line);
void alpha_PrintData(alpha_token_t *node, char *extra_type);

void push_comments_info(alpha_comments_info_t *head, unsigned int first_line)
{
  alpha_comments_info_t *node = (alpha_comments_info_t *)malloc(sizeof(alpha_comments_info_t));
  node->first_line = first_line;
  node->next = NULL;
  while (head->next != NULL)
  {
    head = head->next;
  }
  head->next = node;
}
unsigned int get_first_line(alpha_comments_info_t *head, unsigned int index)
{
  unsigned int i = 0;
  while (head->next != NULL && i < index)
  {
    head = head->next;
    i++;
  }
  return head->first_line;
}
void print_comments_info(alpha_comments_info_t *head)
{
  while (head != NULL)
  {
    printf("from %u to %u \n", head->first_line, head->last_line);
    head = head->next;
  }
}

void alpha_CreateInfo(void *yylval, char *identifier, char *additional_info, unsigned int start_line)
{
  short isComment = 0;
  alpha_ptr->numline = start_line;
  alpha_ptr->numToken = ++counter;
  if (strcmp(identifier, "COMMENT") == 0 || strcmp(identifier, "NESTED COMMENT") == 0)
  {
    isComment = 1;
    if (yylineno == start_line)
    {
      alpha_ptr->content = malloc(1 * sizeof(char));
      memcpy(alpha_ptr->content, "", 1);
    }
    else
    {
      int start_line_length = snprintf(NULL, 0, "%u", start_line);
      int end_line_length = snprintf(NULL, 0, "%u", yylineno);
      // +4 for "  "  ,+1 for '\0'
      alpha_ptr->content = malloc(start_line_length + end_line_length + 4 + 1);
      snprintf(alpha_ptr->content, start_line_length + 1, "%u", start_line);
      memcpy(alpha_ptr->content + start_line_length, " - ", 4);
      snprintf(alpha_ptr->content + start_line_length + 3, end_line_length + 1, "%d", yylineno);
    }
  }
  if (strcmp(identifier, "STRING") == 0 || strcmp(identifier, "IDENT") == 0)
  {

    int length = strlen(additional_info) + 1;
    alpha_ptr->content = malloc(sizeof(char) * length);
    memcpy(alpha_ptr->content, additional_info, length);

    int identifier_length = strlen(identifier) + 1;
    alpha_ptr->type = malloc(sizeof(char) * identifier_length);
    memcpy(alpha_ptr->type, identifier, identifier_length);
  }
  else
  {
    if (isComment != 1)
    {
      int length = strlen(yytext) + 1;
      alpha_ptr->content = malloc(sizeof(char) * length);
      memcpy(alpha_ptr->content, yytext, length);
    }

    int identifier_length = strlen(identifier) + 1;
    int additional_info_length = strlen(additional_info) + 1;
    alpha_ptr->type = malloc(sizeof(char) * identifier_length + additional_info_length + DOUBLE_SPACE);
    memcpy(alpha_ptr->type, identifier, identifier_length);
    strncat(alpha_ptr->type, "  ", DOUBLE_SPACE);
    strncat(alpha_ptr->type, additional_info, additional_info_length);
  }
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