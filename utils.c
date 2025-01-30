/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:32:38 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/30 18:13:44 by oelleaum         ###   ########lyon.fr   */
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
	//le premier element a la meme adresse que son prev ??? : le VRAIS dernier element n'est plus dans a liste au free ?
	printf("*l = %d\n", (*l)->n);
	printf("l prev = %x | l prev next = %x | l prev n = %d\n\n", (*l)->prev, (*l)->prev->next, (*l)->prev->n);
	(*l)->prev->next = NULL;
	while (tmp)
	{
		next_node = tmp->next;
	  printf("n = %d | start = %d | next = %x | %x\n", tmp->n, tmp->start, tmp, tmp->next);
		free(tmp);
		tmp = next_node;
	}
	/* free(tmp); */
	*l = NULL;
}

/* void free_list(t_list **l) */
/* { */
/*   t_list *tmp; */
/*    */
/*   if (!*l) */
/*     return ; */
/*   *l = (*l)->next; */
/*   while ((*l)->start != true) */
/*   { */
/*     tmp = *l; */
/*     *l = (*l)->next; */
/*     free(tmp); */
/*   } */
/*   tmp = *l; */
/*     (*l)->next; */
/*   free(tmp); */
/*   free(l); */
/* } */

/* void free_list(t_list **lst) */
/* { */
/*   t_list *tmp; */
/**/
/*   while (*lst) */
/*   { */
/*     tmp = *lst; */
/*     *lst = (*lst)->next; */
/*     free(tmp); */
/*   } */
/* } */

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

// pour init : il manque le "circulaire"
void	add_back(t_list **lst, int n)
{
	t_list	*ptr;
	t_list	*new;

	/* write(1, "ici, 3", 1); */
	//on a rajouter l'init parce que valgind parlait d'une variable non init
	new = NULL;
	new = malloc(sizeof(t_list));
	/* if (new == NULL) */
	/*   lst_clear(*lst); */
	// si ma liste est vide
	if (*lst == NULL)
	{
		/* printf("la\n"); */
		*lst = new;
		new->prev = NULL;
		new->prev = new;
		printf("new->prev = %p\n", new->prev);
		new->next = new;
		new->n = n;
		new->start = true;
		//*lst = new; 
	}
	// liste pas vide : on veut set :
	//  - prev du premier
	//  - prev & next du dernier (new)
	else
	{
		ptr = (*lst)->prev; // on est sur le dernier de la liste
		//Ici, d'une maniere ou d'une autre, je cree un prev sur lui meme 
		ptr->next = new; //next etait sur la tete : on le passe sur le nouveau node 
		/* ptr = ptr->prev; */
		/* printf("ptr->n = %d\n", ptr->n); */
		new->prev = ptr; //le precedent du new, est l'ancien dernier 
		new->next = *lst;
		new->n = n;
		new->start = false;
	}  
	printf("n = %d | %x | *new->next = %p | *new-prev = %p\n", n, *new, new->next, new->prev); 
}

void	print_lst(t_list *l)
{
	t_list	*ptr;
	int		i;

	i = 1;
	if (l == NULL)
		return ;
	ptr = l;
	printf("node #%d = %d | start = %d\n", i, ptr->n, ptr->start);
	ptr = ptr->next;
	// une fois sur le maillon inexistant : la boucle stop
	while (ptr->start == false)
	{
		i++;
		printf("node #%d = %d\n", i, ptr->n);
		// comme pour le swap ! c'est deux pointeurs
		ptr = ptr->next;
	}
}
