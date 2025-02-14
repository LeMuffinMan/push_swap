/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_on_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:03:27 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/14 12:31:19 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"
#include "../checker.h"
#include <unistd.h>

void	push(t_stack **la, t_stack **lb)
{
	t_stack	*tmp;

	if (*lb == NULL)
		return ;
	tmp = *lb;
	if (tmp == (*tmp).next)
		*lb = NULL;
	else
		take_out_stack_top(la, lb, &tmp);
	if (*la == NULL)
		stack_empty_case(la, &tmp);
	else if (*la == (*la)->next && *la == (*la)->prev)
		stack_one_node_case(la, &tmp);
	else
		plug_on_stack(la, &tmp);
}

