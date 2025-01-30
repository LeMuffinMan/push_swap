/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:32:38 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/30 16:06:10 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <stdio.h>

void free_list(t_list *l)
{
    t_list *tmp = l;
    t_list *next_node;
    
    if (!l)
        return;
    l->prev->next = NULL;
    while (tmp)
    {
        next_node = tmp->next;
        free(tmp);
        tmp = next_node;
    }
}

t_list *lst_last(t_list *lst)
{
  t_list *ptr;

  ptr = lst;
  if (ptr == NULL)
    return (NULL);
  ptr = ptr->next;
  //le pb etait que ptr->start me permet pas de checker l'element suivant : 
  //on s'arrete quand "le prochain est le premier"
  while (ptr->next->start != true)
    ptr = ptr->next;
  return (ptr);
}

//pour init : il manque le "circulaire"
void add_back(t_list **lst, int n)
{
  t_list *ptr;
  t_list *new;

  /* write(1, "ici, 3", 1); */
  new = malloc(sizeof(t_list) * 1);
  /* if (new == NULL) */
  /*   lst_clear(*lst); */
  //si ma liste est vide 
  if (*lst == NULL)
  {
    /* printf("la\n"); */
    new->prev = new;
    new->next = new;
    new->n = n;
    new->start = true;
    *lst = new;
  }
  // liste pas vide : on veut set : 
  //  - prev du premier 
  //  - prev & next du dernier (new) 
  else 
  { 
    ptr = *lst;
    ptr->prev = lst_last(*lst);
    ptr = ptr->prev;
    /* printf("ptr->n = %d\n", ptr->n); */
    new->prev = ptr;
    ptr->next = new;
    new->next = *lst;
    new->n = n;
    new->start = false;
  }
}

void print_lst(t_list *l)
{
  t_list *ptr;
  int i;

  i = 1;
  if (l == NULL)
    return ;
  ptr = l;
  printf("node #%d = %d | start = %d\n", i, ptr->n, ptr->start);
  ptr = ptr->next;
  // une fois sur le maillon inexistant : la boucle stop
  while (ptr->start == false)
  {
    i++;
    printf("node #%d = %d\n", i, ptr->n);
    //comme pour le swap ! c'est deux pointeurs 
    ptr = ptr->next;
  }
}
