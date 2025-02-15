/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:40:50 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/15 17:22:31 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/checker.h"
#include <stdlib.h>
#include <unistd.h>

int	execute_push(char *op, t_stack **la, t_stack **lb)
{
	if (!ft_strncmp(op, "pa\n", 3))
		push(la, lb);
	else if (!ft_strncmp(op, "pb\n", 3))
		push(lb, la);
	else
		return (1);
	return (0);
}

int	execute_rotations(char *op, t_stack **la, t_stack **lb)
{
	if (!ft_strncmp(op, "ra\n", 3))
		rotations(la);
	else if (!ft_strncmp(op, "rb\n", 3))
		rotations(lb);
	else if (!ft_strncmp(op, "rr\n", 3))
	{
		rotations(la);
		rotations(lb);
	}
	else if (!ft_strncmp(op, "rra\n", 4))
		reverse_rotations(la);
	else if (!ft_strncmp(op, "rrb\n", 4))
		reverse_rotations(lb);
	else if (!ft_strncmp(op, "rrr\n", 4))
	{
		reverse_rotations(la);
		reverse_rotations(lb);
	}
	else
		return (1);
	return (0);
}

int	execute_swap(char *op, t_stack **la, t_stack **lb)
{
	if (!ft_strncmp(op, "sa\n", 3))
		swap(la);
	else if (!ft_strncmp(op, "sb\n", 3))
		swap(lb);
	else if (!ft_strncmp(op, "ss\n", 3))
	{
		swap(la);
		swap(lb);
	}
	else
		return (1);
	return (0);
}

int	execute_ops(char *op, t_stack **la, t_stack **lb)
{
	if (execute_rotations(op, la, lb))
	{
		if (execute_swap(op, la, lb))
		{
			if (execute_push(op, la, lb))
				return (1);
		}
	}
	return (0);
}

int	get_ops(t_stack **la, t_stack **lb)
{
	char	*op;

	op = get_next_line(0);
	while (op != NULL)
	{
		if (execute_ops(op, la, lb))
		{
			write(2, "Error\n", 6);
			free(op);
			return (1);
		}
		free(op);
		op = get_next_line(0);
	}
	free(op);
	return (0);
}
