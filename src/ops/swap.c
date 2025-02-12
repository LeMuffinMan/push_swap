#include "push_swap.h"
#include <stdio.h>

void sa(t_list **l)
{
  int tmp;

  if (*l == NULL || *l == (*l)->next)
    return ;
  tmp = (*l)->n;
  (*l)->n = (*l)->next->n;
  (*l)->next->n = tmp;
  tmp = (*l)->i;
  (*l)->i = (*l)->next->i;
  (*l)->next->i = tmp;
  printf("sa\n");
}

void sb(t_list **l)
{
  int tmp;

  if (*l == NULL || *l == (*l)->next)
    return ;
  tmp = (*l)->n;
  (*l)->n = (*l)->next->n;
  (*l)->next->n = tmp;
  tmp = (*l)->i;
  (*l)->i = (*l)->next->i;
  (*l)->next->i = tmp;
  printf("sb\n");
}

void ss(t_list **la, t_list **lb)
{
  int tmp;

  if (*la == NULL || *la == (*la)->next)
    return ;
  tmp = (*la)->n;
  (*la)->n = (*la)->next->n;
  (*la)->next->n = tmp;
  tmp = (*la)->i;
  (*la)->i = (*la)->next->i;
  (*la)->next->i = tmp;
  if (*lb == NULL || *lb == (*lb)->next)
    return ;
  tmp = (*lb)->n;
  (*lb)->n = (*lb)->next->n;
  (*lb)->next->n = tmp;
  tmp = (*lb)->i;
  (*lb)->i = (*lb)->next->i;
  (*lb)->next->i = tmp;
  printf("ss\n");
}
