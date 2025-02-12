#include "push_swap.h"
#include <stdio.h>

void rra(t_list **l)
{
  if (*l == NULL || *l == (*l)->next)
    return ;
  (*l)->prev->start = true;
  (*l)->start = false;
  *l = (*l)->prev;
  printf("rra\n");
  /* get_position(l); */
}

void rrb(t_list **l)
{
  if (*l == NULL || *l == (*l)->next)
    return ;
  (*l)->prev->start = true;
  (*l)->start = false;
  *l = (*l)->prev;
  printf("rrb\n");
  /* get_position(l); */
}

void rrr(t_list **la, t_list **lb)
{
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
  /* get_position(la); */
  /* get_position(lb); */
}
