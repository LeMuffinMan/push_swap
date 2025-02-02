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

//a reecrir
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

//a reverifier
int 	duplicate_checker(t_list *l)
{
	t_list *n1;
	t_list *n2;

	n1 = l;
	n2 = l->next;
	while (n1->next != l) // on fait le tour de la liste avec n1
	{
		while (n2 != l) // on teste chaque noeud jusqu'a revenir a debut de liste
		{
			/* printf("n1->n = %d | n2->n = %d\n", n1->n, n2->n); */
			if(n1->n == n2->n)	
				return (1);
			n2 = n2->next;
		}
		n1 = n1->next;
		n2 = n1->next;
	}
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
  char **splitted;

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
  if (is_sorted(*l) || duplicate_checker(*l)) 
  {
  	printf("sorted list or duplicated ints\n");
  	free_list(l);
  	exit(1);
  }
  return (0);
}

