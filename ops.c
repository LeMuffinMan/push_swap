/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:30:43 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/30 13:53:52 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"
#include <stdio.h>

/* ra (rotate a): Shift up all elements of stack a by 1. */
/* The first element becomes the last one. */
/* rb (rotate b): Shift up all elements of stack b by 1. */
/* The first element becomes the last one. */
void rotate(t_list **l)
{
  if (*l == NULL || *l == (*l)->next)
    return ;
  (*l)->start = false;
  (*l)->next->start = true;
  *l = (*l)->next;
}

/* rr : ra and rb at the same time. */
void rotate_both(t_list **la, t_list **lb)
{
  if (*la == NULL || *lb == NULL)
  {
    printf("rr but one stack is empty !");
    exit(1);
  }
  rotate(la);
  rotate(lb);
}

/* rra (reverse rotate a): Shift down all elements of stack a by 1. */
/* The last element becomes the first one. */
/* rrb (reverse rotate b): Shift down all elements of stack b by 1. */
/* The last element becomes the first one. */
void reverse_rotate(t_list **l)
{
  if (*l == NULL || *l == (*l)->next)
    return ;
  (*l)->prev->start = true;
  (*l)->start = false;
  *l = (*l)->prev;
}

/* rrr : rra and rrb at the same time. */
void reverse_rotate_both(t_list **la, t_list **lb)
{
  if (*la == NULL || *lb == NULL)
  {
    printf("rrr but one stack is empty !");
    exit(1);
  }
  reverse_rotate(la);
  reverse_rotate(lb);
}

/* sa (swap a): Swap the first 2 elements at the top of stack a. */
/* Do nothing if there is only one or no elements. */
/* sb (swap b): Swap the first 2 elements at the top of stack b. */
/* Do nothing if there is only one or no elements. */
void swap(t_list **l)
{
  int tmp;

  if (*l == NULL || *l == (*l)->next)
    return ;
  tmp = (*l)->n;
  (*l)->n = (*l)->next->n;
  (*l)->next->n = tmp;
}

/* ss : sa and sb at the same time. */
void swap_both(t_list **la, t_list **lb)
{
  if (*la == NULL || *lb == NULL)
  {
    printf("ss but one stack is empty !");
    exit(1);
  }
  swap(la);  
  swap(lb);  
}

/* pa (push a): Take the first element at the top of b and put it at the top of a. */
/* Do nothing if b is empty. */
/* pb (push b): Take the first element at the top of a and put it at the top of b. */
/* Do nothing if a is empty */
void push(t_list **la, t_list **lb) //encore des pb ici
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
}


