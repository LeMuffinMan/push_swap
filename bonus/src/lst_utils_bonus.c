/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:42:54 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/15 17:15:22 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/checker_bonus.h"
#include <stdlib.h>
#include <unistd.h>

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
		exit(1);
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

void	free_list(t_stack **l)
{
	t_stack	*tmp;
	t_stack	*next_node;

	if (!l || !*l)
		return ;
	tmp = *l;
	(*l)->prev->next = NULL;
	while (tmp)
	{
		next_node = tmp->next;
		free(tmp);
		tmp = next_node;
	}
	*l = NULL;
}

int	*lst_to_array(t_stack **la, int size)
{
	int		*array;
	int		i;
	t_stack	*tmp;

	array = malloc(sizeof(int) * size);
	if (!array)
	{
		free_list(la);
		return (NULL);
	}
	array[0] = (*la)->n;
	i = 1;
	tmp = (*la)->next;
	while (!tmp->start)
	{
		array[i] = tmp->n;
		i++;
		tmp = tmp->next;
	}
	sort_int_tab(array, i);
	return (array);
}
