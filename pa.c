#include "push_swap.h"
#include <stdio.h> // a virer

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

static void A_empty_case(t_list **la, t_list **lb, t_list **tmp)
{
    (*tmp)->prev = *tmp;
    (*tmp)->start = true;
    (*tmp)->next = *tmp;
    *la = *tmp;
}

static void A_one_node_case(t_list **la, t_list **lb, t_list **tmp)
{
    (*la)->next = *tmp;
    (*la)->prev = *tmp;
    (*la)->next->next = *(la);
    (*la)->prev->prev = *(la);
    (*la)->start = false;
    (*la)->next->start = true;
    *la = *tmp;
}

static void plug_on_A(t_list **la, t_list **lb, t_list **tmp)
{
    (*la)->prev->next = *tmp; 
    (*tmp)->prev = (*la)->prev;
    (*la)->prev = (*tmp);
    (*tmp)->next = *la;
    (*la)->start = false;
    *la = *tmp;
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
    A_empty_case(la, lb, &tmp);
  else if (*la == (*la)->next && *la == (*la)->prev)  
    A_one_node_case(la, lb, &tmp);
  else 
    plug_on_A(la, lb, &tmp);
  get_position(la);
  get_position(lb);
  printf("pa\n");
}

