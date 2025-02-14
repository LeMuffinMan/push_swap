/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:04:15 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/13 14:34:44 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

// static ou libft ?

static void	swap_elements(int *tab, unsigned int p1, unsigned int p2)
{
	int	tmp;

	tmp = tab[p1];
	tab[p1] = tab[p2];
	tab[p2] = tmp;
}

static void	bubble_sort(int *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (tab[j] > tab[j + 1])
				swap_elements(tab, j, j + 1);
			j++;
		}
		i++;
	}
}

static void	sort_int_tab(int *tab, unsigned int size)
{
	if (size <= 1)
		return ;
	bubble_sort(tab, size);
}

int	*lst_to_array(t_stack **la, int size)
{
	int		*array;
	int		i;
	t_stack	*tmp;

	//proteger en friant si necessaire
	array = malloc(sizeof(int) * size);
	if (!array)
		return (NULL);
	array[0] = (*la)->n;
	i = 1;
	tmp = (*la)->next;
	while (!tmp->start)
	{
		array[i] = tmp->n;
		i++;
		tmp = tmp->next;
	}
	sort_int_tab(array, i);
	return (array);
}
