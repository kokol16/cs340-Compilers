#include<stdlib.h>
#include<stdio.h> 
#include<string.h> 
#define DOUBLE_SPACE 3
#define YYSTYPE void* 


static unsigned int counter = 0;
static short FirstNode = 1;
extern  FILE *output_file;

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
  int first_line;
  unsigned int last_line;
  short is_closed;
  struct alpha_comments_info_t *next;
} alpha_comments_info_t;

alpha_token_t *alpha_CreateData(char *identifier, void *yylval, char *additional_info, unsigned int start_line);
void alpha_CreateInfo(void *yylval, char *identifier, char *additional_info, unsigned int start_line);
alpha_token_t *alpha_CreateNextNode(void *yylval);
void alpha_free_tokens_list(alpha_token_t *head);
void alpha_PrintData(alpha_token_t *node, char *extra_type);
void print_Red();
void reset_Red();
void print_Yellow();
void reset_Yellow();
alpha_comments_info_t *get_node(alpha_comments_info_t *head, unsigned int nested);
unsigned int get_first_line(alpha_comments_info_t *head, unsigned int index);
void print_comments_info(alpha_comments_info_t *head);
void alpha_free_comments_list(alpha_comments_info_t *head);
void push_comments_info(alpha_comments_info_t *head, int first_line,int counter);


