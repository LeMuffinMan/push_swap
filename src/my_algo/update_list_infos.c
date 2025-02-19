/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_list_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:36:23 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/15 13:36:46 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_index(t_stack **l, int *array)
{
	int		i;
	t_stack	*tmp;
	int		size;

	size = lst_size(*l);
	i = 0;
	tmp = *l;
	while (1)
	{
		i = 0;
		while (i < size)
		{
			if (tmp->n == array[i])
			{
				tmp->i = i;
				break ;
			}
			i++;
		}
		tmp = tmp->next;
		if (tmp->start)
			break ;
	}
}

void	get_dests(t_stack **la, t_stack **lb, int max_index, int min_index)
{
	t_stack	*tmp_a;
	t_stack	*tmp_b;

	tmp_b = *lb;
	while (1)
	{
		tmp_b->dest = max_index;
		if (tmp_b->i > max_index)
			tmp_b->dest = min_index;
		tmp_a = *la;
		while (tmp_b->dest != min_index)
		{
			if (tmp_a->i > tmp_b->i && tmp_a->i < tmp_b->dest)
				tmp_b->dest = tmp_a->i;
			tmp_a = tmp_a->next;
			if (tmp_a->start)
				break ;
		}
		tmp_b = tmp_b->next;
		if (tmp_b->start)
			break ;
	}
}

void	get_dest_rots(t_stack **la, t_stack **lb)
{
	t_stack	*tmp_a;
	t_stack	*tmp_b;
	int		dest;

	tmp_a = *la;
	tmp_b = *lb;
	while (1)
	{
		dest = tmp_b->dest;
		while (1)
		{
			if (tmp_a->i == dest)
				tmp_b->dest_rot = tmp_a->rot;
			tmp_a = tmp_a->next;
			if (tmp_a->start)
				break ;
		}
		tmp_b = tmp_b->next;
		if (tmp_b->start)
			break ;
	}
}

void	get_rots(t_stack **l)
{
	t_stack	*tmp;
	int		rot;

	(*l)->rot = 0;
	tmp = (*l)->next;
	rot = 1;
	while (tmp->start == FALSE)
	{
		if (rot > lst_size(*l) / 2)
			rot = (lst_size(*l) - rot) * -1;
		tmp->rot = rot;
		rot++;
		tmp = tmp->next;
	}
}

int	get_position(t_stack **l)
{
	t_stack	*tmp;
	int		i;

	if (!*l)
		return (1);
	(*l)->pos = 0;
	i = 1;
	tmp = (*l)->next;
	while (tmp->start == FALSE)
	{
		tmp->pos = i;
		i++;
		tmp = tmp->next;
	}
	return (0);
}
