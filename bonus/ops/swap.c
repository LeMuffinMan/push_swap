/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:04:08 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/13 14:32:03 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../checker.h"
#include "../../includes/push_swap.h"

//optimisable : on reuni sa et sb vu que y'a plus de printf

void	sa(t_stack **l)
{
	int	tmp;

	if (*l == NULL || *l == (*l)->next)
		return ;
	tmp = (*l)->n;
	(*l)->n = (*l)->next->n;
	(*l)->next->n = tmp;
	tmp = (*l)->i;
	(*l)->i = (*l)->next->i;
	(*l)->next->i = tmp;
}

void	sb(t_stack **l)
{
	int	tmp;

	if (*l == NULL || *l == (*l)->next)
		return ;
	tmp = (*l)->n;
	(*l)->n = (*l)->next->n;
	(*l)->next->n = tmp;
	tmp = (*l)->i;
	(*l)->i = (*l)->next->i;
	(*l)->next->i = tmp;
}

void	ss(t_stack **la, t_stack **lb)
{
	int	tmp;

	if (*la == NULL || *la == (*la)->next)
		return ;
	tmp = (*la)->n;
	(*la)->n = (*la)->next->n;
	(*la)->next->n = tmp;
	tmp = (*la)->i;
	(*la)->i = (*la)->next->i;
	(*la)->next->i = tmp;
	if (*lb == NULL || *lb == (*lb)->next)
		return ;
	tmp = (*lb)->n;
	(*lb)->n = (*lb)->next->n;
	(*lb)->next->n = tmp;
	tmp = (*lb)->i;
	(*lb)->i = (*lb)->next->i;
	(*lb)->next->i = tmp;
}
