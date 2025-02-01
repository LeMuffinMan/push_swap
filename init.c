/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:36 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/31 14:16:03 by oelleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h> // a virer
#include <stdlib.h> // Add par moi

int is_sorted(t_list *l)
{
	t_list 	*tmp;
	int 	n;

	tmp = l;
	n = tmp->n;
	tmp = tmp->next;
	while(tmp->n > n)
	{
		n = tmp->n;
		tmp = tmp->next;
	}
	if (tmp == l)
	{
		printf("list is sorted at init\n");
		return (1);
	}
	return (0);
}

int duplicate_checker(t_list *l)
{
	t_list *tmp;
	t_list n_compared; //il me faut une boucle en plus
	int n;

	tmp = l;
	n = tmp->n;
	tmp = tmp->next;
	while (tmp != l) // je fais le tour complet de ma liste 
	{
		if (n == tmp->n)
			break ;
	}
	if (tmp != l)
	{
		printf("duplicated numbers in list\n");
		return (1);
	}
	return (0);
}


int init_stack(t_list **l, char **av)
{
  int i;
  int j;
  char **splitted;

  j = 0;
  i = 0;
  if (!av[1][0])
	  return (-1);
  splitted = ft_split(av[1], ' '); // penser a gerer plus de sep : tout ce qui n'est pas un - + ou un digit *l ?
  if (splitted[1] == NULL) // si il n'y a qu'un seul element
    return (-1);
  *l = fill_list(splitted);
  i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	printf("l = %x | (*l).next = %x\n", l, (*l)->next);
  if (is_sorted(*l) || *l == (*l)->next /* duplicate_checker(l) */) // marche pas 
  	exit(1);
  return (0);
}

//a virer 

void init_stackb(t_list **l)
{
  int i;

  i = -6;
  while (++i < 0)
    add_back(l, i);
}

