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
	printf("node #%d = %d | index = %d | rot = %d | pivot = %d | cost = %d | dest = %d | start = %d\n", ptr->pos, ptr->n, ptr->i, ptr->rot, ptr->pivot, ptr->cost, ptr->dest, ptr->start);
	ptr = ptr->next;
	while (ptr->start == false)
	{
		i++;
	printf("node #%d = %d | index = %d | rot = %d | pivot = %d | cost = %d | dest = %d\n", ptr->pos, ptr->n, ptr->i, ptr->rot, ptr->pivot, ptr->cost, ptr->dest);
		ptr = ptr->next;
	}
}

void add_first_node(t_list **lst, t_list *new, int n)
{
		*lst = new;
		new->prev = new;
		new->n = n;
		new->start = true;
		new->next = new;
}

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

int lst_size(t_list *l)
{
	t_list *ptr;
	int i;

	if (l == NULL)
		return (0);
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

//a virer ?
/* t_list	*lst_last(t_list *lst) */
/* { */
/* 	t_list	*ptr; */
/**/
/* 	ptr = lst; */
/* 	if (ptr == NULL) */
/* 		return (NULL); */
/* 	ptr = ptr->next; */
/* 	// le pb etait que ptr->start me permet pas de checker l'element suivant : */
/* 	// on s'arrete quand "le prochain est le premier" */
/* 	while (ptr->next->start != true) */
/* 		ptr = ptr->next; */
/* 	return (ptr); */
/* } */



void	swap_elements(int *tab, unsigned int p1, unsigned int p2)
{
	int tmp = tab[p1];
	tab[p1] = tab[p2];
	tab[p2] = tmp;
}

void	bubble_sort(int *tab, unsigned int size)
{
	unsigned int i = 0;
	unsigned int j = 0;

	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (tab[j] > tab[j + 1])
				swap_elements(tab, j, j + 1);
			j++;
		}
		i++;
	}
}



void	sort_int_tab(int *tab, unsigned int size)
{
	if (size <= 1)
		return ;
	bubble_sort(tab, size);
}





int	*lst_to_array(t_list **la, int size)
{
	int	*array;
	int	i;
	t_list *tmp;

	array = (int *)malloc(sizeof(int) * size); //revoir ca 
	if (!array)
		return (NULL);
	array[0] = (*la)->n;
	i = 1;
	tmp = (*la)->next;
	while (tmp->start == false)
	{
		array[i] = tmp->n;
		i++;
		tmp = tmp->next;
	}
	sort_int_tab(array, i);
	/* i = 0; */
	/* while (i < size) */
	/* { */
	/* 	printf("array[%d] = %d\n", i, array[i]); */
	/* 	i++; */
	/* } */
	return (array);
}

//renvoyer un booleen
int is_sorted_check(t_list *la)
{
	t_list *tmp;

	//securiser ?
	tmp = la;
	while (tmp->n < tmp->next->n)
		tmp = tmp->next;
	/* printf("tmp->next = %x\nla = %x\n", tmp->next, la); */
	if (tmp->next != la)
		return (0);
	/* while (tmp->next != la) */
	/* { */
	/* 	if (tmp->n > tmp->next->n) */
	/* 	{ */
	/* 		printf("tmp->n = %d | tmp->next->n = %d\n", tmp->n, tmp->next->n); */
	/* 		return (1); */
	/* 	} */
	/* 	tmp = tmp->next; */
	/* } */
	/* printf("list sorted\n"); */
	return (1);
}

