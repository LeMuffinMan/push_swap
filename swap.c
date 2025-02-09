#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h> // a vrirer avec stdio

//1 fonction a racourcir
//faire dossier ops



/* sa (swap a): Swap the first 2 elements at the top of stack a. */
/* Do nothing if there is only one or no elements. */
/* sb (swap b): Swap the first 2 elements at the top of stack b. */
/* Do nothing if there is only one or no elements. */
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

  get_position(l);
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

  get_position(l);
}

/* ss : sa and sb at the same time. */
void ss(t_list **la, t_list **lb)
{
  int tmp;

  if (*la == NULL || *lb == NULL)
  {
    printf("ss but one stack is empty !");
    exit(1);
  }
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
  
  get_position(la);
  get_position(lb);
  printf("ss\n");
}
