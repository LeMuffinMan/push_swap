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

// installer le vizuallizer pour tester
// adapter code au vizu
// implementer quick sort
// radix ?
//
////tester les ints min et les ints max TODO

/* The goal is to sort in ascending order numbers into stack a. */

// /!\ un seul arg part en vrille : un cas d'erreur e
// cas sur peu d'arguments : mois de 3 ca bug

// d'abord : verifier les doublons
// verifier si j'ai plus d'un element e
// hardcoder de 2 a 5 elements

// A REVOIR
void	size_3_sort(t_list **la) // pour pile de 2 ou 3
								// lui passer *la ou **la ?
{
	if (lst_size(*la) == 2) // si on a deux chiffres a trier
	{
		sa(la);
	}
	else if (lst_size(*la) == 3)
	{
		if ((*la)->n > (*la)->next->n && (*la)->n < (*la)->next->next->n
			&& (*la)->next->n < (*la)->next->next->n) // 2 1 3
		{
			sa(la);
		}
		else if ((*la)->n > (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n < (*la)->n
			&& (*la)->next->n > (*la)->next->next->n) // 3 2 1
		{
			ra(la);
			sa(la);
		}
		else if ((*la)->n > (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n < (*la)->n
			&& (*la)->next->n < (*la)->next->next->n) // 3 1 2
		{
			ra(la);
		}
		else if ((*la)->n < (*la)->next->n && (*la)->n < (*la)->next->next->n
			&& (*la)->next->n > (*la)->n
			&& (*la)->next->n > (*la)->next->next->n) // 1 3 2
		{
			sa(la);
			ra(la);
		}
		else if ((*la)->n < (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n > (*la)->n
			&& (*la)->next->n > (*la)->next->next->n) // 2 3 1
		{
			rra(la);
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

/* void get_min_max(int *min, int *max, t_list *la) */
/* { */
/* 	t_list *tmp; */
/* 		*/
/* 	//securiser !  */
/* 	*min = la->n; */
/* 	*max = la->n; */
/* 	tmp = la->next; */
/* 	while (tmp->start == false) */
/* 	{ */
/* printf("tmp->start = %d\n", tmp->start); */
/* 		if (tmp->n < *min) */
/* 			*min = tmp->n; */
/* 		if (tmp->n > *max) */
/* 			*max = tmp->n; */
/* 		tmp = tmp->next; */
/* 	} */
/* } */

void	get_index(t_list **l, int *array)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *l;
	while (array[i])
	{
		if (tmp->n == array[i])
		{
			tmp->i = i + 1;
			break ;
		}
		i++;
	}
	i = 0;
	tmp = (*l)->next;
	while (tmp->start == false)
	{
		i = 0;
		while (array[i])
		{
			if (tmp->n == array[i])
			{
				tmp->i = i + 1;
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

// on veut garder 3 valeurs a gauche : on envoie a droite en pretriant
// tant que size A > 3
// si n == min || n == max : ra
// si > pivot : pb et rb
// esle pb

// a tester
int	get_moves_count(t_list *la, t_list *lb, int i)
{
	t_list	*tmp;
	int		count;
	int		j;
	int size; //segfault en essayer de recuperer la taille ?

	tmp = lb;
	j = 1; // un pour push
	while (tmp->i != i)
	{
		tmp = tmp->next;
		j++; // j ++ pour chaque rotations
	}
	if (j > size / 2)
		j = size - j; // on peut acceder au milieu en rotatant dans l'autre sens
	// ici, j = le nombre de rotation / rrotation pour avoir i en haut de lb
		/* + 1 pour le push */
	if (i == la->i - 1)
		return (j); // si on doit le push simplement : count = rotations + push
	tmp = la->next;
	j++;  // si le premier est pas bon, on rotate une fois la : donc j++
	while (tmp->start == false)
		// tant qu'on n'a pas fait le tour de la sans trouver ou mettre i
	{
		if (i == la->i - 1) // ajouter le + 1 !!
			count = j;
		j++;
		tmp = tmp->next;
	}
	if (count > size / 2)
		return (size - count);
	return (count);
}

int	get_cheaper_i(t_list **la, t_list **lb)
{
	t_list	*tmp;
	int		i;
	int		cheaper;

	tmp = *lb;
	cheaper = get_moves_count(la, lb, tmp->i);
	tmp = tmp->next;
	while (tmp->start == false)
	{
		if (get_moves_count(la, lb, tmp->i) < cheaper)
			cheaper = tmp->i;
		tmp = tmp->next;
	}
	return (cheaper);
}

void	sort(t_list **la, t_list **lb)
{
	int	median;
	int	size;
	int	*array;
	int	i;

	size = lst_size(*la);
	array = lst_to_array(la, size);
	median = array[size / 2];
	get_index(la, array);
	free(array);
	/* printf("min = %d | max = %d | median = %d\n", min, max, median); */
	while (lst_size(*la) > 3)
	{
		printf("(*la)->i = %d | size = %d\n", (*la)->i, size);
		if ((*la)->i == 1) // on a le min
			ra(la);
		else if ((*la)->i == size) // on a le max
			ra(la);
		else if ((*la)->i == size / 2)
			ra(la);
		else
		{
			if ((*la)->i > size / 2)
				pb(la, lb);
			else
			{
				pb(la, lb);
				rb(lb);
			}
		}
		size_3_sort(la);
		// la on a le plus petit en haut, la mediane, puis le max
	}
	i = get_cheaper_i(la, lb);
	printf("i = %d\n", i);
	// chercher i dans lb, tourner et inserer au bon moment
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
	init_stack(&la, ac, av);
	/* printf("list_size(*lb) = %d\n", lst_size(lb)); */
	printf("==========================\nstack initialized :\n");
	print_lst(la);
	printf("==========================\n\n");
	/* partition_setup(&la, &lb); */
	/* printf("la :\n"); */
	/* print_lst(la); */
	/* printf("lb :\n"); */
	/* print_lst(lb); */
	sort(&la, &lb);
	/* if (lst_size(la) <= 3) */
	/* 	size_3_sort(&la); */
	/* else */
	/* 	insertion_sort(&la, &lb); */
	printf("\n========================\n");
	printf("la :\n");
	print_lst(la);
	/* printf("la->n = %d start = %d | la->next->n = %d  start =
		%d  | la->prev->n = %d  start = %d\n", la->n, la->start, la->next->n,
		la->next->start, la->prev->n, la->prev->start); */
	printf("lb :\n");
	print_lst(lb);
	is_sorted_check(la);
	free_list(&la);
	free_list(&lb);
	return (0);
}
// dans fractol je declare une struct : ici je declare un pointeur sur la struct :
// C'EST POUR CA QUE envoyer &l ici peut etre recupere en **lst
