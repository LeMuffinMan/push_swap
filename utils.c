/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:32:38 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/31 14:34:07 by oelleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

void	free_list(t_list **l)
{
	t_list	*tmp;
	t_list	*next_node;

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

//a virer ?
t_list	*lst_last(t_list *lst)
{
	t_list	*ptr;

	ptr = lst;
	if (ptr == NULL)
		return (NULL);
	ptr = ptr->next;
	// le pb etait que ptr->start me permet pas de checker l'element suivant :
	// on s'arrete quand "le prochain est le premier"
	while (ptr->next->start != true)
		ptr = ptr->next;
	return (ptr);
}

void add_first_node(t_list **lst, t_list *new, int n)
{
		*lst = new;
		new->prev = new;
		new->n = n;
		new->start = true;
		new->next = new;
}

// pour init : il manque le "circulaire"
void	add_back(t_list **lst, int n)
{
	t_list	*ptr;
	t_list	*new;

	new = NULL;
	new = malloc(sizeof(t_list));
	/* if (new == NULL) */
	/*   lst_clear(*lst); */
	if (*lst == NULL)
		add_first_node(lst, new, n);
	else
	{
		ptr = (*lst)->prev; // on est sur le dernier de la liste
		ptr->next = new; //next etait sur la tete : on le passe sur le nouveau node 
		(*lst)->prev = new;
		new->prev = ptr; //le precedent du new, est l'ancien dernier 
		new->next = *lst;
		new->n = n;
		new->start = false;
	}  
}

void	print_lst(t_list *l)
{
	t_list	*ptr;
	int		i;

	i = 1;
	if (l == NULL)
	{
		printf("list is empty\n");
		return ;
	}
	ptr = l;
	printf("node #%d = %d | start = %d\n", i, ptr->n, ptr->start);
	ptr = ptr->next;
	while (ptr->start == false  && i < 10)
	{
		i++;
		printf("node #%d = %d\n", i, ptr->n);
		ptr = ptr->next;
	}
}

int lst_size(t_list *l)
{
	t_list *ptr;
	int i;

	ptr = l;
	if (ptr->next == ptr)
		return (1);
	i = 1;
	ptr = ptr->next;
	while (ptr->start != true)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}
