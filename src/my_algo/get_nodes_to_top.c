/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nodes_to_top.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:02:53 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/13 14:02:56 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	get_node_by_index(t_stack **l, int index, t_stack **node)
{
	if ((*l)->i == index)
		(*node) = *l;
	else
	{
		(*node) = (*l)->next;
		while (!(*node)->start)
		{
			if ((*node)->i == index)
				break ;
			*node = (*node)->next;
		}
	}
}

static void	do_combine_rotates(t_stack **la, t_stack **lb, t_stack **candidate,
		t_stack **dest)
{
	while ((*candidate)->rot > 0 && (*dest)->rot > 0)
	{
		rr(la, lb);
		(*candidate)->rot--;
		(*dest)->rot--;
	}
	while ((*candidate)->rot < 0 && (*dest)->rot < 0)
	{
		rrr(la, lb);
		(*candidate)->rot++;
		(*dest)->rot++;
	}
}

static void	do_single_rotates(t_stack **la, t_stack **lb, t_stack **candidate,
		t_stack **dest)
{
	while ((*candidate)->rot > 0)
	{
		rb(lb);
		(*candidate)->rot--;
	}
	while ((*candidate)->rot < 0)
	{
		rrb(lb);
		(*candidate)->rot++;
	}
	while ((*dest)->rot > 0)
	{
		ra(la);
		(*dest)->rot--;
	}
	while ((*dest)->rot < 0)
	{
		rra(la);
		(*dest)->rot++;
	}
}

void	get_nodes_to_top(t_stack **la, t_stack **lb, int cheaper)
{
	t_stack	*candidate;
	t_stack	*dest;

	get_node_by_index(lb, cheaper, &candidate);
	get_node_by_index(la, candidate->dest, &dest);
	do_combine_rotates(la, lb, &candidate, &dest);
	do_single_rotates(la, lb, &candidate, &dest);
}
