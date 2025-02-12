#include "push_swap.h"
#include <stdio.h> // a virer
#include <unistd.h>

static void take_out_B_top(t_list **la, t_list **lb, t_list **node, t_list **last)
{
    (*lb)->start = false;
    (*last) = (*lb)->prev;
    *lb = (*lb)->next;
    (*lb)->start = true;
    (*lb)->prev = (*last);
    (*last)->next = *lb;  
    (*node)->next = *la;
}

static void A_empty_case(t_list **l, t_list **tmp)
{
    (*tmp)->prev = *tmp;
    (*tmp)->start = true;
    (*tmp)->next = *tmp;
    *l = *tmp;
}

static void A_one_node_case(t_list **l, t_list **tmp)
{
    (*l)->next = *tmp;
    (*l)->prev = *tmp;
    (*l)->next->next = *(l);
    (*l)->prev->prev = *(l);
    (*l)->start = false;
    (*l)->next->start = true;
    *l = *tmp;
}

static void plug_on_A(t_list **l, t_list **tmp)
{
    (*l)->prev->next = *tmp; 
    (*tmp)->prev = (*l)->prev;
    (*l)->prev = (*tmp);
    (*tmp)->next = *l;
    (*l)->start = false;
    *l = *tmp;
    (*tmp)->start = true;
}

void pa(t_list **la, t_list **lb) 
{
  t_list *last;
  t_list *tmp;

  if (*lb == NULL)
    return ;
  tmp = *lb;
  if (tmp == (*tmp).next) 
    *lb = NULL;
  else 
    take_out_B_top(la, lb, &tmp, &last);
  if (*la == NULL)
    A_empty_case(la, &tmp);
  else if (*la == (*la)->next && *la == (*la)->prev)  
    A_one_node_case(la, &tmp);
  else 
    plug_on_A(la, &tmp);
  get_position(la);
  get_position(lb);
  printf("pa\n");
}

