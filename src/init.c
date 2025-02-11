/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:36 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/11 16:00:43 by oelleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
// a virer : bien gerer les debugs d'erreurs : peut faire KO si pas demande
#include <stdlib.h>

//reunir les fonctions init et deplacer free_splitted 

// a reverifier
int	duplicate_checker(t_list *l)
{
	t_list	*n1;
	t_list	*n2;

	n1 = l;
	n2 = l->next;
	while (n1->next != l) // on fait le tour de la liste avec n1
	{
		while (n2 != l)
		// on teste chaque noeud jusqu'a revenir a debut de liste
		{
			/* printf("n1->n = %d | n2->n = %d\n", n1->n, n2->n); */
			if (n1->n == n2->n)
				return (1);
			n2 = n2->next;
		}
		n1 = n1->next;
		n2 = n1->next;
	}
	return (0);
}

void	free_splited(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}

//revoir !!
int	init_stack(t_list **l, int ac, char **av)
{
	char	**splitted;

	if (ac == 1 || !av[1][0]) // pas sur la seconde condition
		exit(1);
	// si ac == 2 : gerer 1 int unique et une string d'ints
	else if (ac == 2)
	{
		splitted = ft_split(av[1], ' ');
		// gerer plus de sep : n'est pas un - + ou un digit *l ?
		if (splitted[1] == NULL) // si il n'y a qu'un seul element
		{
			free_splited(splitted);
			printf("Error\n");
			exit(EXIT_FAILURE);
		}
		*l = fill_list(splitted);
		free_splited(splitted);
		//iversion de la condition is_sorted ?
		if (is_sorted_check(*l) || duplicate_checker(*l))
		{
			printf("sorted list or duplicated ints\n");
			free_list(l);
			exit(1);
		}
	}
	else if (ac > 2)
	{
		av++;
		*l = fill_list(av);
	}
	return (0);
}
