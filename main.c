/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:49:41 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/31 14:16:40 by oelleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

// PAS d'OPERATION SI LA PILE EST DEJA TRIEE   a tester
////tester les ints min et les ints max TODO

/* The goal is to sort in ascending order numbers into stack a. */

// /!\ un seul arg part en vrille : un cas d'erreur e
// cas sur peu d'arguments : mois de 3 ca bug

// d'abord : verifier les doublons
// verifier si j'ai plus d'un element e
// hardcoder de 2 a 5 elements

void	homegrown_algo(t_list *la) // pour pile de 2 ou 3
								// lui passer *la ou **la ?
{
	if (lst_size(la) == 2) // si on a deux chiffres a trier
	{
		printf("sa\n");
		swap(&la);
	}
	else if (lst_size(la) == 3)
	{
		if (la->n > la->next->n && la->n < la->next->next->n
			&& la->next->n < la->next->next->n) // 2 1 3
		{
			printf("sa\n");
			swap(&la);
		}
		else if (la->n > la->next->n && la->n > la->next->next->n
			&& la->next->n < la->n && la->next->n > la->next->next->n) // 3 2 1
		{
			printf("ra\n");
			rotate(&la);
			printf("sa\n");
			swap(&la);
		}
		else if (la->n > la->next->n && la->n > la->next->next->n
			&& la->next->n < la->n && la->next->n < la->next->next->n) // 3 1 2
		{
			printf("ra\n");
			rotate(&la);
		}
		else if (la->n < la->next->n && la->n < la->next->next->n
			&& la->next->n > la->n && la->next->n > la->next->next->n) // 1 3 2
		{
			printf("sa\n");
			swap(&la);
			printf("ra\n");
			rotate(&la);
		}
		else if (la->n < la->next->n && la->n > la->next->next->n
			&& la->next->n > la->n && la->next->n > la->next->next->n) // 2 3 1
		{
			printf("rra\n");
			reverse_rotate(&la);
		}
	}
}

// revoir ma fonction is sorted !
int	is_desc_sorted(t_list *l)
{
	t_list	*tmp;
	int		n;

	if (l == NULL || l == l->next)
		return (0);
	tmp = l;
	n = tmp->n;
	tmp = tmp->next;
	while (tmp != l)
	{
		if (tmp->n > n)
			return (1);
		n = tmp->n;
		tmp = tmp->next;
	}
	return (0); // 0 = sorted
}

/* int is_desc_sorted(t_list *lb) */
/* { */
/*   t_list *tmp; */
/**/
/*   if (tmp->n > tmp->next->n) */
/*     tmp = tmp->next; */
/*   else  */
/*     return (1); */
/*   while (tmp != lb) */
/*   { */
/*     if (tmp->n < tmp->next->n) */
/*       return (1); */
/*     tmp = tmp->next; */
/*   } */
/*   return (0); */
/* } */

#include <unistd.h>

void	insertion_sort(t_list **la, t_list **lb)
{

	/* printf("------------ insertion sort ------------\n"); */
	while (*la != NULL) // tant que ma pile a n'est pas vide
	{
		if (lst_size(*lb) > 1 && (*la)->n < (*lb)->n && (*la)->n > (*lb)->prev->n) // si n < 1er et n > dernier : on cherche sa place
		{
    	t_list *tmp;

    	tmp = (*lb)->next;
			while ((*la)->n < tmp->n)
				tmp = tmp->next;

    	// Effectuer des rotations pour amener la bonne position en haut de lb
    	while (*lb != tmp)
        rotate(lb); // On fait tourner jusqu'à la bonne position
      //
			push(lb, la);
			printf("[pb]\n");
			printf("\nlb :\n");
			print_lst(*lb);
			printf("[is_desc_sorted(*lb) == %d]\n", is_desc_sorted(*lb));
			printf("\n");
			

      while ((*lb)->n < (*lb)->prev->n)
      	reverse_rotate(lb);
		}
		else 
		{
			push(lb, la); // on push le premier element dans b
			printf("[pb]\n");
			printf("\nlb :\n");
			print_lst(*lb);
			printf("[is_desc_sorted(*lb) == %d]\n", is_desc_sorted(*lb));
			printf("\n");
			
		}		// a partir de deux elements on commence la tambouille
		if (lst_size(*lb) > 1)
		{
			// si le new est inferieur au dernier : on le met en dernier
			if ((*lb)->n < (*lb)->prev->n)
			{
				rotate(lb);
				printf("[rotate]\n");
				printf("\nlb :\n");
				print_lst(*lb);
				printf("\n");
				printf("[is_desc_sorted(*lb) == %d]\n", is_desc_sorted(*lb));
			}
			if ((*lb)->n < (*lb)->next->n)
			{
				swap(lb);
				printf("[swap]\n");
				printf("\nlb :\n");
				print_lst(*lb);
				printf("\n");
				printf("[is_desc_sorted(*lb) == %d]\n", is_desc_sorted(*lb));
			}
		}
	}
	while (*lb != NULL)
	{
		push(la, lb);
		printf("pa\n");
	}
}
// 10 <= n <= 100 : quicksort / tri par groupes
// n > 100 : Radix sort adapte (base 2 ou 10)

void is_sorted_check(t_list *la)
{
	t_list *tmp;

	//securiser ?
	tmp = la;
	while (tmp->next != la)
	{
		if (tmp->n > tmp->next->n)
		{
			printf("list unsorted\n");
			return ;
		}
		tmp = tmp->next;
	}
	printf("list sorted\n");
}

int	main(int ac, char **av)
{
	t_list	*la;

	// l'idee est de garder ce pointeur vers le 1er element de ma liste
	la = NULL;
	t_list *lb = NULL; // pb avec ma stack b au demarrage
	if (ac <= 1)       // ARG "1 5 -65" comme seul input ?
	{
		printf("ERROR : not enough arguments\n");
		// error a afficher dans certains cas seulement
		exit(1);
	}
	init_stack(&la, av);
	/* printf("list_size(*lb) = %d\n", lst_size(lb)); */
	printf("==========================\nstack initialized :\n");
	print_lst(la);
	printf("==========================\n\n");
	if (lst_size(la) <= 3)
		homegrown_algo(la);
	else
		insertion_sort(&la, &lb);
	printf("\n========================\nlist sorted : \n");
	print_lst(la);
	/* print_lst(lb); */
	is_sorted_check(la);
	free_list(&la);
	free_list(&lb);
	return (0);
}
// dans fractol je declare une struct : ici je declare un pointeur sur la struct :
// C'EST POUR CA QUE envoyer &l ici peut etre recupere en **lst
/* t_list *a = NULL; */
/* t_list *b = NULL; */
/* t_list *ptr = NULL; */
/**/
/* (void)ptr; */
/* add_front(&a, 5); */
/* add_front(&a, 1); */
/*  printf("\n"); */
/* add_front(&b, 2); */
/* add_front(&b, 8); */
/*  add_back(&a, 1);  */
/* print_lst(a); */
/* printf("\n"); */
/* print_lst(b); */
/* ptr = lst_last(a); */
/* printf("\nlast = %d\n\n", ptr->n); */
/* print_rev_lst(a); */
/* printf("\n"); */
/* print_rev_lst(b); */
/**/
/* (*lst) */
/* *lst->next */
/**/
/* (**lst) */
/* (*lst)->next */
