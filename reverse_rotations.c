#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h> // a virer avec stido

/* rra (reverse rotate a): Shift down all elements of stack a by 1. */
/* The last element becomes the first one. */
/* rrb (reverse rotate b): Shift down all elements of stack b by 1. */
/* The last element becomes the first one. */
void rra(t_list **l)
{
  if (*l == NULL || *l == (*l)->next)
    return ;
  (*l)->prev->start = true;
  (*l)->start = false;
  *l = (*l)->prev;
  printf("rra\n");

  get_position(l);
}

void rrb(t_list **l)
{
  if (*l == NULL || *l == (*l)->next)
    return ;
  (*l)->prev->start = true;
  (*l)->start = false;
  *l = (*l)->prev;
  printf("rrb\n");

  get_position(l);
}

/* rrr : rra and rrb at the same time. */
void rrr(t_list **la, t_list **lb)
{
  if (*la == NULL || *lb == NULL)
  {
    printf("rrr but one stack is empty !");
    exit(1);
  }
  if (*la == NULL || *la == (*la)->next)
    return ;
  (*la)->prev->start = true;
  (*la)->start = false;
  *la = (*la)->prev;
  if (*lb == NULL || *lb == (*lb)->next)
    return ;
  (*lb)->prev->start = true;
  (*lb)->start = false;
  *lb = (*lb)->prev;
  printf("rrr\n");

  get_position(la);
  get_position(lb);
}
