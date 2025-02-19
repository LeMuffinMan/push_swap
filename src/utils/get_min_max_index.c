/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_min_max_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:04:32 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/13 14:04:49 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min_index(t_stack **l)
{
	int		min;
	t_stack	*tmp;

	min = (*l)->i;
	tmp = (*l)->next;
	while (!tmp->start)
	{
		if (tmp->i < min)
			min = tmp->i;
		tmp = tmp->next;
	}
	return (min);
}

int	get_max_index(t_stack **l)
{
	int		max;
	t_stack	*tmp;

	max = (*l)->i;
	tmp = (*l)->next;
	while (!tmp->start)
	{
		if (tmp->i > max)
			max = tmp->i;
		tmp = tmp->next;
	}
	return (max);
}
