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
#include <unistd.h>
#include <limits.h>

//reunir les fonctions init et deplacer free_splitted 

int init_step_2(t_list **l)
{
	t_list *tmp;

	(*l)->rot = 0;
	(*l)->cost = INT_MAX;
	(*l)->dest = -1;
	(*l)->dest_rot = 0;
	tmp = (*l)->next;
	if (tmp->start == true)
		return (0);
	if (init_step_2(&tmp))
		return (1);
	return(0);
}

static int duplicate_checker(t_list *l)
{
	t_list *n1;
	t_list *n2;

	n1 = l;
	n2 = l->next;
	while (1)
	{
		while(1)
		{
			if (n2->n == n1->n && n1 != n2)
				return(1);
			n2 = n2->next;
			if (n2->start)
				break ;
		}
		n1 = n1->next;
		if (n1->start)
			break ;
	}
	return (0);
}

int invalid_input(t_list *l, int *array, char **s)
{
	if (s)
		free_splited(s);
	if (array)
		free(array);
	if (l)
		free(l);
	write(2, "Error", 5);
	exit(1);
}

int	init_stack(t_list **l, int ac, char **av)
{
	char	**splitted;

	if (ac == 1 || !av[1][0]) 
		exit(1);
	else if (ac == 2)
	{
		splitted = ft_split(av[1], ' ');
		if (splitted[1] == NULL) 
			invalid_input(NULL, NULL, splitted);
		*l = fill_list(splitted);
		free_splited(splitted);
		if (duplicate_checker(*l))
			invalid_input(*l, NULL, NULL);
	}
	else if (ac > 2)
	{
		av++;
		*l = fill_list(av);
		if (duplicate_checker(*l))
			invalid_input(*l, NULL, NULL);
	}
	return (0);
}
