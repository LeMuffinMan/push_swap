/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_list_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:03:15 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/13 14:03:19 by oelleaum         ###   ########lyon.fr   */
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

//racourciri
void	get_dests(t_stack **la, t_stack **lb)
{
	t_stack	*tmp_A;
	t_stack	*tmp_B;
	int max_index;
	int min_index;

	max_index = get_max_index(la);
	min_index = get_min_index(la);
	tmp_B = *lb;
	while (1)
	{
		tmp_B->dest = max_index;
		if (tmp_B->i > max_index)
			tmp_B->dest = min_index;
		tmp_A = *la;
		while (tmp_B->dest != min_index)
		{
			if (tmp_A->i > tmp_B->i && tmp_A->i < tmp_B->dest)
				tmp_B->dest = tmp_A->i;
			tmp_A = tmp_A->next;
			if (tmp_A->start)
				break ;
		}
		tmp_B = tmp_B->next;
		if (tmp_B->start)
			break ;
	}
}

void	get_dest_rots(t_stack **la, t_stack **lb)
{
	t_stack	*tmp_A;
	t_stack	*tmp_B;
	int		dest;

	tmp_A = *la;
	tmp_B = *lb;
	while (1)
	{
		dest = tmp_B->dest;
		while (1)
		{
			if (tmp_A->i == dest)
				tmp_B->dest_rot = tmp_A->rot;
			tmp_A = tmp_A->next;
			if (tmp_A->start)
				break ;
		}
		tmp_B = tmp_B->next;
		if (tmp_B->start)
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
