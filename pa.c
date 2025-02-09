#include "push_swap.h"
#include <stdio.h> // a virer

/* pa (push a): Take the first element at the top of b and put it at the top of a. */
/* Do nothing if b is empty. */
/* pb (push b): Take the first element at the top of a and put it at the top of b. */
/* Do nothing if a is empty */
/* push a (&la, &lb) */
/* push b (&lb, &la) */

// a diviser et mettre en static

void pa(t_list **la, t_list **lb) //encore des pb ici
{
  t_list *last;
  t_list *tmp;

  if (*lb == NULL)
    return ;
  tmp = *lb;
  if (tmp == (*tmp).next) // si j'ai plus qu'un seul element dans la pile a reduire 
    *lb = NULL;
  else 
  {
    (*lb)->start = false;
    last = (*lb)->prev;
    *lb = (*lb)->next;
    (*lb)->start = true;
    (*lb)->prev = last;
    last->next = *lb;  //lb a toujours son premier element
    tmp->next = *la;
  }
  if (*la == NULL)
  {
    tmp->prev = tmp;
    tmp->start = true;
    tmp->next = tmp;
    *la = tmp;
  }
  else if (*la == (*la)->next && *la == (*la)->prev) // si la liste ne contient qu'un seul element 
  {
    (*la)->next = tmp;
    (*la)->prev = tmp;
    (*la)->next->next = *(la);
    (*la)->prev->prev = *(la);
    (*la)->start = false;
    (*la)->next->start = true;
    *la = tmp;
  }
  else 
  {
    (*la)->prev->next = tmp; // le next du dernier est branche sur le nouveau
    tmp->prev = (*la)->prev;
    (*la)->prev = tmp;
    tmp->next = *la;
    (*la)->start = false;
    *la = tmp;
    tmp->start = true;
  }
  get_position(la);
  get_position(lb);
  printf("pa\n");
}

