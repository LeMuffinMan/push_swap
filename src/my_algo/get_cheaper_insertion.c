/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cheaper_insertion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:02:44 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/13 14:02:48 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_cheaper_insertion(t_stack **l)
{
	int		cheaper;
	t_stack	*tmp;
	int		min_cost;

	if (lst_size(*l) == 1)
	{
		cheaper = (*l)->i;
		return (cheaper);
	}
	min_cost = (*l)->cost;
	cheaper = (*l)->i;
	tmp = (*l)->next;
	while (!tmp->start)
	{
		if (tmp->cost < min_cost)
		{
			min_cost = tmp->cost;
			cheaper = tmp->i;
		}
		tmp = tmp->next;
	}
	return (cheaper);
}

static int	synch_rotations(int rot, int dest_rot)
{
	if (rot >= dest_rot)
		return (rot);
	else
		return (dest_rot);
}

int	optimise_rotations(t_stack *node)
{
	int	rot;
	int	dest_rot;

	rot = node->rot;
	dest_rot = node->dest_rot;
	if (rot >= 0 && dest_rot < 0)
		return (rot + dest_rot * -1);
	if (rot < 0 && dest_rot >= 0)
		return (rot * -1 + dest_rot);
	if (rot >= 0 && dest_rot >= 0)
		return (synch_rotations(rot, dest_rot));
	if (rot < 0 && dest_rot < 0)
		return (synch_rotations(rot * -1, dest_rot * -1));
	return (0);
}

void	get_costs(t_stack **lb)
{
	t_stack	*tmp;

	(*lb)->cost = optimise_rotations(*lb);
	tmp = (*lb)->next;
	while (!tmp->start)
	{
		tmp->cost = optimise_rotations(tmp);
		tmp = tmp->next;
	}
}
