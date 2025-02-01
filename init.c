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
#include <stdio.h> // a virer : bien gerer les debugs d'erreurs : peut faire KO si pas demande 
#include <stdlib.h> 

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
		exit (1);
	}
	return (0);
}

int duplicate_checker(t_list *l) // a raccourcir 
{
	t_list *tmp;
	int n;
	bool dup;

	dup = 0;
	tmp = l;
	n = tmp->n;
	tmp = tmp->next;
	if (n == tmp->n)
		return (1);
	while (tmp != l && !dup) //tour de toute la chaine pour reset n_compared
	{
		while(tmp != l && !dup) //tour de toute la chaine pour comparer n_compared avec tous les n qui suivent 
		{
			if(n == tmp->n)
			{
				printf("duplicated found\n");
				dup = 1;
			}
			tmp = tmp->next;
		}
		tmp = tmp->next;
		n = tmp->n;
	}
	if (dup)
		return (1);
	return (0);
}

void free_splited(char **splited)
{
	int i;

  i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);

}

int init_stack(t_list **l, char **av)
{
  int i;
  int j;
  char **splitted;

  j = 0;
  i = 0;
  if (!av[1][0])
  {
  	printf("list empty at initialisation\n");
	  exit(EXIT_FAILURE);
	}
  splitted = ft_split(av[1], ' '); // penser a gerer plus de sep : tout ce qui n'est pas un - + ou un digit *l ?
  if (splitted[1] == NULL) // si il n'y a qu'un seul element
  {
  	free_splited(splitted);
  	printf("list has only 1 element\n");
  	exit(EXIT_FAILURE);
  }
  *l = fill_list(splitted);
  free_splited(splitted);
  if (is_sorted(*l) ||  duplicate_checker(*l)) 
  {
  	printf("sorted list or duplicated ints\n");
  	free_list(l);
  	exit(1);
  }
  return (0);
}

//a virer 
/* void init_stackb(t_list **l) */
/* { */
/*   int i; */
/**/
/*   i = -6; */
/*   while (++i < 0) */
/*     add_back(l, i); */
/* } */
/**/
