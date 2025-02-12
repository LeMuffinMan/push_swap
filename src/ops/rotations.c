#include "push_swap.h"
#include <stdio.h>

void ra(t_list **l)
{
  if (*l == NULL || *l == (*l)->next)
    return ;
  (*l)->start = false;
  (*l)->next->start = true;
  *l = (*l)->next;
  printf("ra\n");
}

void rb(t_list **l)
{
  if (*l == NULL || *l == (*l)->next)
    return ;
  (*l)->start = false;
  (*l)->next->start = true;
  *l = (*l)->next;
  printf("rb\n");
}

void rr(t_list **la, t_list **lb)
{
  if (*la == NULL || *la == (*la)->next)
    return ;
  (*la)->start = false;
  (*la)->next->start = true;
  *la = (*la)->next;
  if (*lb == NULL || *lb == (*lb)->next)
    return ;
  (*lb)->start = false;
  (*lb)->next->start = true;
  *lb = (*lb)->next;
  printf("rr\n");
}


