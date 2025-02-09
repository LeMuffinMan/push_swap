#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h> // A virer !!

/* ra (rotate a): Shift up all elements of stack a by 1. */
/* The first element becomes the last one. */
/* rb (rotate b): Shift up all elements of stack b by 1. */
/* The first element becomes the last one. */
void ra(t_list **l)
{
  if (*l == NULL || *l == (*l)->next)
    return ;
  (*l)->start = false;
  (*l)->next->start = true;
  *l = (*l)->next;
  
  printf("ra\n");
  get_position(l);

}

void rb(t_list **l)
{
  if (*l == NULL || *l == (*l)->next)
    return ;
  (*l)->start = false;
  (*l)->next->start = true;
  *l = (*l)->next;
  printf("rb\n");
  get_position(l);
}


/* rr : ra and rb at the same time. */
void rr(t_list **la, t_list **lb)
{
  if (*la == NULL || *lb == NULL)
  {
    printf("rr but one stack is empty !");
    exit(1);
  }
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

  get_position(la);
  get_position(lb);
}


