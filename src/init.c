/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:36 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/15 16:29:40 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

int	init_step_2(t_stack **l)
{
	t_stack	*tmp;

	tmp = *l;
	tmp->cost = INT_MAX;
	tmp->dest = -1;
	tmp->dest_rot = 0;
	while (1)
	{
		tmp->rot = 0;
		tmp = tmp->next;
		if (tmp->start)
			break ;
	}
	return (0);
}

static int	duplicate_checker(t_stack *l)
{
	t_stack	*n1;
	t_stack	*n2;

	n1 = l;
	n2 = l->next;
	while (1)
	{
		while (1)
		{
			if (n2->n == n1->n && n1 != n2)
				return (1);
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

int	invalid_input(t_stack *l, int *array, char **s)
{
	if (s)
		/* ft_free(s); */
	if (array)
		/* free(array); */
	if (l)
		/* free_list(&l); */
	write(2, "Error\n", 6);
	exit(1);
}

static t_stack	*fill_list(char **splitted)
{
	t_stack	*l;
	int		i;
	int		n;
	int		size;
	int		*array;

	l = NULL;
	i = 0;
	while (splitted[i])
	{
		if (is_digits_or_sign(splitted[i]))
			invalid_input(l, NULL, NULL);
		n = ft_atoi_limits_check(splitted[i], l);
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

int	init_stack(t_stack **l, int ac, char **av)
{
	if (ac == 1 || !av[1][0])
		exit(1);
	else if (ac >= 2)
	{
		av++;
		*l = fill_list(av);
		if (duplicate_checker(*l))
			invalid_input(*l, NULL, NULL);
	}
	return (0);
}
