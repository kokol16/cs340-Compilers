#include "lib.h"

#define alpha_ptr ((alpha_token_t *)yylval)


void print_Red()
{
  fprintf(stderr, "\033[0;31m");
}
void reset_Red()
{
  fprintf(stderr, "\033[0;31m");
}
void print_Yellow()
{
  fprintf(stderr, "\033[1;33m");
}

void reset_Yellow()
{
  fprintf(stderr, "\033[0m");
}

void alpha_PrintData(alpha_token_t *node, char *extra_type)
{
  int line_width = 10;
  FILE *out;
  if (output_file != NULL)
  {
    out = output_file;
  }
  else
  {
    out = stdout;
  }
  //printf("\b");
  fprintf(out, "%u:\t", node->numline);
  fprintf(out, "#%u\t", node->numToken);
  fprintf(out, "\"%s\"\t", node->content);
  fprintf(out, "%s\t", node->type);
  if (strcmp(node->type, "STRING") == 0 || strcmp(node->type, "IDENT") == 0)
  {
    fprintf(out, "\"%s\"\t", node->content);
  }
  fprintf(out, "%s\n", extra_type);
}
void alpha_free_tokens_list(alpha_token_t *head)
{
  alpha_token_t *prev = head;
  while (head != NULL)
  {
    prev = head;
    head = head->alpha_yylex;
    free(prev->content);
    free(prev->type);

    free(prev);
  }
}
void alpha_free_comments_list(alpha_comments_info_t *head)
{
  alpha_comments_info_t *prev = head;
  while (head != NULL)
  {
    prev = head;
    head = head->next;
    free(prev);
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
void push_comments_info(alpha_comments_info_t *head, int first_line, int counter)
{
  alpha_comments_info_t *node = (alpha_comments_info_t *)malloc(sizeof(alpha_comments_info_t));
  node->first_line = first_line;
  node->is_closed = 0;
  node->next = NULL;
  int i = 0;
  while (head->next != NULL && i < counter)
  {
    head = head->next;
    i++;
  }
  if (head->next != NULL)
    free(head->next);
  head->next = node;
}
alpha_comments_info_t *get_node(alpha_comments_info_t *head, unsigned int nested)
{
  unsigned int counter = 0;
  while (head != NULL && counter < nested)
  {
    head = head->next;
    counter++;
  }
  return head;
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
    fprintf(output_file, "from %u to %u \n", head->first_line, head->last_line);
    head = head->next;
  }
}
