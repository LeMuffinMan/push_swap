/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:03:48 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/13 14:31:28 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../checker.h"
#include "../../includes/push_swap.h"

//voir commentaire reverse rota

void	ra(t_stack **l)
{
	if (*l == NULL || *l == (*l)->next)
		return ;
	(*l)->start = FALSE;
	(*l)->next->start = TRUE;
	*l = (*l)->next;
}

void	rb(t_stack **l)
{
	if (*l == NULL || *l == (*l)->next)
		return ;
	(*l)->start = FALSE;
	(*l)->next->start = TRUE;
	*l = (*l)->next;
}

void	rr(t_stack **la, t_stack **lb)
{
	if (*la == NULL || *la == (*la)->next)
		return ;
	(*la)->start = FALSE;
	(*la)->next->start = TRUE;
	*la = (*la)->next;
	if (*lb == NULL || *lb == (*lb)->next)
		return ;
	(*lb)->start = FALSE;
	(*lb)->next->start = TRUE;
	*lb = (*lb)->next;
}
