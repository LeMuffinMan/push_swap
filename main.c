/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:49:41 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/07 20:00:37 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //a virer apres debug

// Boucle infinie dans des cas particuliers + 10 elem sur ra ?
// get_cheaper renvoie une structure
// on boucle tant qu'on n'a pas le prev et le next correct
// optimiser les rotations synchronisees
////tester les ints min et les ints max TODO

/* The goal is to sort in ascending order numbers into stack a. */

// /!\ un seul arg part en vrille : un cas d'erreur e
// cas sur peu d'arguments : mois de 3 ca bug

// d'abord : verifier les doublons
// verifier si j'ai plus d'un element e
// hardcoder de 2 a 5 elements

// A renommer et reecrire comme pour inverted_size_3_sort
// faire pour 5 et 6 ?
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

// reecrire is sorted sur ce modele
void	inverted_size_3_sort(t_list **l)
{
	int	a;
	int	b;
	int	c;

	/* print_lst(*l); */
	a = (*l)->i;
	b = (*l)->next->i;
	c = (*l)->prev->i;
	if (lst_size(*l) == 2 && a < b)
		sb(l);
	else if (lst_size(*l) == 3)
	{
		if (a < b && b < c && b < c) // 1 2 3 -> sb + rrb
		{
			sb(l);
			rrb(l);
		}
		else if (a < b && a < c && b > c) // 1 3 2 -> rb
			rb(l);
		else if (a > b && a < c && b < c) // 2 1 3 -> rrb
			rrb(l);
		else if (a < b && a > c && b > c) // 2 3 1 -> sb
			sb(l);
		else if (a > b && a > c && b < c) // 3 1 2 -> sb + rb
		{
			sb(l);
			rb(l);
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

void	get_index(t_list **l, int *array)
{
	//si size < p ca peut poser soucis
	int		i;
	int 	p;
	t_list	*tmp;
	int		size;

	p = 3; // a opti
	size = lst_size(*l);
	i = 0;
	tmp = *l;
	while (i < size)
	// si je met juste array[i] : si il vaut 0 la boucle s'arrete
	{
		if (tmp->n == array[i])
		{
			tmp->i = i;
			tmp->pivot = i / (size / p); // Calcul du pivot
			break ;
		}
		i++;
	}
	i = 0;
	tmp = (*l)->next;
	while (tmp->start == false)
	{
		i = 0;
		while (i < size)
		{
			if (tmp->n == array[i])
			{
				tmp->i = i;
				tmp->pivot = i / (size / p); // Calcul du pivot
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

int	partition_stacks(t_list **la, t_list **lb)
{
	t_list *tmp;
	int count;
	int size;
	int p;
	int j;

	p = 3; // a opti
	j = 0;
	size = lst_size(*la);
	count = 0;
	//proteger si stack a < 3
	if ((*la)->i == size - 1)
		ra(la);
	if ((*la)->pivot <= j)
	{
		count++;
		pb(la, lb);
		if ((*lb)->pivot >= j + 1)
			rb(lb);
		if (count >= size / p)
		{
			j++;
			count = 0;
		}
	}
	else
		ra(la);
	tmp = (*la)->next;
	j = 0;
	while (lst_size(*la) > 3) // opti a faire ici
	{
		if (tmp->i == size - 1)
		{
			ra(la);
			tmp = tmp->next;
			continue ;
		}
		if (tmp->pivot <= j)
		{	

			if (j == p)
				break ;
			count++;
			pb(la, lb);
			if ((*lb)->pivot >= j + 1)
				rb(lb);
			if (count >= size / p)
			{
				j++;
				count = 0;
			}
		}
		else
			ra(la);
		tmp = tmp->next;
	}
}


int do_rotates(t_list **la, t_list **lb, t_move *best_move)
{

	while (best_move->rr > 0)
	{
		/* printf("rr : %d\n", best_move->rr); */
		rr(la, lb);
		best_move->rr--;
	}
	while (best_move->rrr > 0)
	{
		/* printf("rrr : %d\n", best_move->rrr); */
		rrr(la, lb);
		best_move->rrr--;
	}
	while (best_move->ra > 0)
	{
		/* printf("ra : %d\n", best_move->ra); */
		ra(la);
		best_move->ra--;
	}
	while (best_move->rb > 0)
	{
		/* printf("rb : %d\n", best_move->rb); */
		rb(lb);
		best_move->rb--;
	}
	while (best_move->rra > 0)
	{
		/* printf("rra : %d\n", best_move->rra); */
		rra(la);
		best_move->rra--;
	}
	while (best_move->rrb > 0)
	{
		/* printf("rrb : %d\n", best_move->rrb); */
		rrb(lb);
		best_move->rrb--;
	}
	/* printf("do rotates end\n"); */
}

int optimise_rotations(t_list *node)
{
	int tmp_1;
	int tmp_2;

		// pb ici, les negatifs donnent des coup = 0
	if (node->rot > 0 && node->dest->rot < 0)
		return (node->rot + node->dest->rot * -1);
	if (node->rot < 0 && node->dest->rot > 0)
		return (node->rot * -1 + node->dest->rot);
	if (node->rot > 0 && node->dest->rot > 0)
	{
		if (node->rot > node->dest->rot)
			return (node->rot);
		else 
			return (node->dest->rot);
	}
	if (node->rot < 0 && node->dest->rot < 0)
	{
		tmp_1 = node->rot * -1;
		tmp_2 = node->dest->rot * -1;
		printf("tmp_1 = %d | tmp_2 = %d\n", tmp_1, tmp_2);
		if (node->rot > node->dest->rot)
			return (node->rot);
		else 
			return (node->dest->rot);
	}
}

int get_costs(t_list **lb)
{
/* le coup est le nombre de rot de tmp et de sa cible */ 
	t_list *tmp;
	
	//revoir les couts : + et - a repenser ?
	(*lb)->cost = (*lb)->rot + (*lb)->dest->rot;
	tmp = (*lb)->next;
	while (tmp->start == false)
	{
		tmp->cost = optimise_rotations(tmp);
		tmp = tmp->next;
	}
}


int get_dests(t_list **la, t_list **lb)
{
	t_list *tmp_A;
	t_list *tmp_B;

	(*lb)->dest = (*la)->prev;
	if ((*la)->i > (*lb)->i && (*la)->i < (*lb)->dest->i)
		(*lb)->dest = *la;
	tmp_A = (*la)->next;
	while (tmp_A->start == false)
	{
		if (tmp_A->i > (*lb)->i && tmp_A->i < (*lb)->dest->i)
			(*lb)->dest = tmp_A;
		tmp_A = tmp_A->next;
	}
	tmp_B = (*lb)->next;
	while (tmp_B->start == false)
	{
		tmp_B->dest = (*la)->prev;
		if ((*la)->i > tmp_B->i && (*la)->i < tmp_B->dest->i)
			tmp_B->dest = *la;
		tmp_A = (*la)->next;
		while (tmp_A->start == false)
		{
			if (tmp_A->i > tmp_B->i && tmp_A->i < tmp_B->dest->i)
				tmp_B->dest = tmp_A;
			tmp_A = tmp_A->next;
		}
		tmp_B = tmp_B->next;
	}
}

int get_rots(t_list **l)
{
	t_list *tmp;
	int rot;
	
	(*l)->rot = 0;
	tmp = (*l)->next;
	rot = 1;
	while (tmp->start == false)
	{
		if (rot > lst_size(*l) / 2)
			rot = (lst_size(*l) - rot) * -1; 
		tmp->rot = rot;
		rot++;
		tmp = tmp->next;
	}
}

t_move get_cheaper_insertion(t_list **la, t_list **lb)
{
	/* t_move cheaper; */
	/* cheaper = get_cheaper_node(); //on peut identifier le moins cher */
	/* return (cheaper);	 */
}

int insert_cheaper(t_list **la, t_list **lb)
{
	/* t_move move; */

	get_dests (la, lb); // on cherche a quel endroit on doit situer le node B dans A
	get_rots (la); // on setup les rots pour chaque nodes
	get_rots (lb); // on setup les rots pour chaque nodes
	get_costs(lb); // on peut donc calculer le coups pour chaque node B
	/* move = get_cheaper_insertion(); */
	/* do_rotates(); */
	/* pa(la, lb); */
	return (0);
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
		// A AFFICHER SUR LA STANDARD ERROR !
		exit(1);
	}
	// LES LISTES DEJA TRIEES PASSENT !!
	init_stack(&la, ac, av);
	printf("==========================\nstack initialized :\n");
	print_lst(la);
	printf("==========================\n\n");
	sleep(1);

	if (lst_size(la) <= 3)
		size_3_sort(&la);
	else
	{
		partition_stacks(&la, &lb);
		size_3_sort(&la);
		insert_cheaper(&la, &lb);
	}
	printf("\n========================\n");
	printf("la :\n");
	print_lst(la);
	printf("lb :\n");
	print_lst(lb);
	if (is_sorted_check(la))
		printf("\nLIST SORTED\n");
	free_list(&la);
	free_list(&lb);
	return (0);
}
