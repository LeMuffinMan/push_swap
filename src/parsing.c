/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:08:40 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/30 17:37:28 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h> // a virer
#include <stdlib.h>
#include <limits.h> // a virer ?
#include <unistd.h>

// ARG="4 56 -3 56" 54 -5
// a gerer !
// integrer la libft et laisser que la fonction fill_list ici
//cas d'erreur non gere correctement ? 
//./a.out "15- 75 34 0"
//45 12 32 62 -45 45-78 : invalid mais PASSE !
//duplicated passe aussi

//deux fonctions a mettre dans init
//libft !!




int get_position(t_list **l)
{
	t_list *tmp;
	int i;

	if (!*l)
		return (1);
	(*l)->pos = 0;
	i = 1;
	tmp = (*l)->next;
	while (tmp->start == false)
	{
		tmp->pos = i;
		i++;
		tmp = tmp->next;
	}
	return (0);
}


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



int is_digits_or_sign(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] != '-' && s[i] != '+' && (s[i] > '9' || s[i] < '0'))
			return (1);
		i++;
	}
	return (0);
}

t_list *fill_list(char **splitted) // revenir pour declarer ici la liste pas dans le main 
{
	t_list *l;
	int i;
	int n;
	int size;
	int *array;

	l = NULL;
	i = 0;
	while (splitted[i])
	{
		if(is_digits_or_sign(splitted[i]))
		{
			free(l);
			write(2, "Error", 5);
			exit(1);
		}
		n = ft_atoi(splitted[i], l); 
		add_back(&l, n);
		i++;
	}
	size = lst_size(l);
	array = lst_to_array(&l, size);
	get_index(&l, array);
	get_position(&l);
	init_step_2(&l);
	free(array);
	return (l);
}



// INIT !
// on doit creer la liste en respectant l'ordre dans lequel on recoit les int
// donc on add back pour que le premier arg soit le premier de la pile
/* add_back(&l, atoi(av[i]) */

// creer une liste de 5 elements
// chaque element a
//  - un next vers le suivant
//  - un prev vers le precedent
// Le next du dernier element pointe vers le premier
// le prev du premier elment pointe vers le dernier
//
