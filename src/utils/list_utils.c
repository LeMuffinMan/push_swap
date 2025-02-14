/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:04:56 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/14 11:29:30 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <stdlib.h>

void	free_list(t_stack **l)
{
	t_stack	*tmp;
	t_stack	*next_node;

	tmp = *l;
	if (!*l)
		return ;
	(*l)->prev->next = NULL;
	while (tmp)
	{
		next_node = tmp->next;
		free(tmp);
		tmp = next_node;
	}
	*l = NULL;
}

static void	add_first_node(t_stack **lst, t_stack *new, int n)
{
	*lst = new;
	new->prev = new;
	new->n = n;
	new->start = TRUE;
	new->next = new;
}

void	add_back(t_stack **lst, int n)
{
	t_stack	*ptr;
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (new == NULL)
	{
	  free_list(lst);
	  exit (1);
	}
	if (*lst == NULL)
		add_first_node(lst, new, n);
	else
	{
		ptr = (*lst)->prev; 
		ptr->next = new;   
		(*lst)->prev = new;
		new->prev = ptr; 
		new->next = *lst;
		new->n = n;
		new->start = FALSE;
	}
}

int	lst_size(t_stack *l)
{
	t_stack	*ptr;
	int		i;

	if (l == NULL)
		return (0);
	ptr = l;
	if (ptr->next == ptr)
		return (1);
	i = 1;
	ptr = ptr->next;
	while (ptr->start != TRUE)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

int	is_sorted_check(t_stack *la)
{
	t_stack	*tmp;

	tmp = la;
	while (tmp->n < tmp->next->n)
		tmp = tmp->next;
	if (tmp->next != la)
		return (0);
	return (1);
}
