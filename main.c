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
	int		i;
	t_list	*tmp;
	int		size;

	size = lst_size(*l);
	i = 0;
	tmp = *l;
	while (i < size)
	// si je met juste array[i] : si il vaut 0 la boucle s'arrete
	{
		if (tmp->n == array[i])
		{
			tmp->i = i;
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
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

int	get_rot_dir(t_list *l, int index, int size)
{
	t_list	*tmp;
	int		i;

	if (l->i == index)
		return (0);
	tmp = l->next;
	i = 0;
	while (tmp->start == false)
	{
		if (tmp->i == i)
			break ;
		tmp = tmp->next;
		i++;
	}
	if (i > size / 2)
		return (-1);
	else
		return (1);
}

t_move	get_moves_count(t_list **la, t_list **lb, int i)
{
	t_list	*tmp;
	t_move	move;
	int		size_A;
	int		size_B;

	move.cheaper = i;
	move.rr = 0;
	move.rrr = 0;
	move.ra = 0;
	move.rb = 0;
	move.rra = 0;
	move.rrb = 0;
	size_A = lst_size(*la);
	size_B = lst_size(*lb);
	tmp = *lb;
	// on cherche i dans lb
	while (tmp->i != i)
	{
		tmp = tmp->next;
		move.rb++;
	}
	tmp = *la;
	// on cherche ou placer i dans la
	while (tmp->i < i && tmp->prev->i > i)
	{
		tmp = tmp->next;
		move.ra++;
	}
	// si i est dans la premiere moitie de B et que son emplacement est dans la premiere moitie de A
	if (move.ra < size_A / 2 && move.rb < size_B / 2)
	{
		if (move.ra == move.rb)
		{
			move.rr = move.ra;
			move.rrr = 0;
			move.ra = 0;
			move.rb = 0;
			move.rra = 0;
			move.rrb = 0;
		}
		else if (move.ra < move.rb)
		{
			move.rr = move.ra;
			move.rb = move.rb - move.ra;
			move.rrr = 0;
			move.ra = 0;
			move.rra = 0;
			move.rrb = 0;
		}
		else if (move.ra > move.rb)
		{
			move.rr = move.rb;
			move.ra = move.ra - move.rb;
			move.rb = 0;
			move.rrr = 0;
			move.rra = 0;
			move.rrb = 0;
		}
	}
	// si i est dans la 2nd moitie de B et que son emplacement est dans la 2nd moitie de A
	else if (move.ra >= size_A / 2 && move.rb >= size_B / 2)
	{
		move.rra = size_A - move.ra;
		move.rrb = size_B - move.rb;
		move.ra = 0;
		move.rb = 0;
		if (move.rra == move.rrb)
		{
			move.rrr = move.rra;
			move.rr = 0;
			move.ra = 0;
			move.rb = 0;
			move.rra = 0;
			move.rrb = 0;
		}
		else if (move.rra < move.rrb)
		{
			move.rrr = move.rra;
			move.rrb = move.rrb - move.rra;
			move.rra = 0;
			move.ra = 0;
			move.rb = 0;
			move.rr = 0;
		}
		else if (move.rra > move.rrb)
		{
			move.rrr = move.rrb;
			move.rra = move.rra - move.rrb;
			move.rrb = 0;
			move.ra = 0;
			move.rb = 0;
			move.rr = 0;
		}
	}
	move.cost = move.rr + move.rrr + move.ra + move.rb;
	return (move);
}


int	partition_stacks(t_list **la, t_list **lb)
{
	int		size_A;
	int		size_B;
	int		i;
	t_move	move;

	size_A = lst_size(*la);
	while (lst_size(*la) > 3)
	// tester alternative Ahbram : pretrier en pushant dans B
	{
		if ((*la)->i > size_A / 2)
			pb(la, lb);
		else
		{
			pb(la, lb);
			rb(lb);
		}
		size_3_sort(la);
	}
}

int	cheapest_move(t_list **la, t_list **lb, t_move *best_move)
{
	best_move->cheaper = (*lb)->i;
	best_move->prev = (*la)->prev->i;
	best_move->next = (*la)->i;
	best_move->rr = 0;
	best_move->rrr = 0;
	best_move->ra = 0;
	best_move->rb = 0;
	best_move->cost = 0;
	return (0);
}

int	only_rotate_A(t_list **la, t_list **lb, t_move *best_move, int count)
{
	best_move->cheaper = (*lb)->i;
	//pour pas passer 5 arguments, j'ai remis dans get_cheaper ces deux lignes
	//	best_move->prev = tmp_A->prev->i;
	/* best_move->next = tmp_A->i; */
	best_move->rr = 0;
	best_move->rrr = 0;
	best_move->rrb = 0;
	best_move->rb = 0;
	if (count > lst_size(*la) / 2)
	{
		best_move->ra = 0;
		best_move->rra = lst_size(*la) - count;  // size - 1 ?
		best_move->cost = lst_size(*la) - count; // size - 1 ?
	}
	else
	{
		best_move->ra = count;
		best_move->rra = 0;
		best_move->cost = count; // size - 1 ?
	}
	return (0);
}

int init_move(t_move *move, t_list *node_B)
{
	move->cheaper = node_B->i;
	move->prev = -1; // pas sur, pour le debug au moins
	move->next = -1;
	move->rr = 0;
	move->rrr = 0;
	move->ra = 0;
	move->rb = 0;
	move->rra = 0;
	move->rrb = 0;
	move->cost = 2147483647;
}

int do_rotates(t_list **la, t_list **lb, t_move *best_move)
{
	/* printf("\ninside do rotates\n"); */
	/* 	printf("move.cheaper = %d\n", best_move->cheaper); */
	/* 	printf("move.prev = %d\n", best_move->prev); */
	/* 	printf("move.next = %d\n", best_move->next); */
	/* 	printf("move.rr = %d\n", best_move->rr); */
	/* 	printf("move.rrr = %d\n", best_move->rrr); */
	/* 	printf("move.ra = %d\n", best_move->ra); */
	/* 	printf("move.rb = %d\n", best_move->rb); */
	/* 	printf("move.rra = %d\n", best_move->rra); */
	/* 	printf("move.rrb = %d\n", best_move->rrb); */
	/* 	printf("move.cost = %d\n\n", best_move->cost); */
		/* sleep (1); */
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

int get_min_max(t_list *l, int *min, int *max)
{
	t_list *tmp;
	
	*min = l->i;
	*max = l->i;
	tmp = l->next;
	while (tmp->start == false)
	{
		if (tmp->i < *min)
			*min = tmp->i;
		if (tmp->i > *max)
			*max = tmp->i;
		tmp = tmp->next;
	}
}

int is_pushable(t_list *la, t_list *lb)
{
	int   min;
	int   max;

	get_min_max(la, &min, &max);
	/* printf("min = %d | max = %d\n", min, max); */
	if (lb->i > max && la->prev->i == max)
		return (0);
	else if (lb->i < min && la->i == min)
		return (0);
	else if (lb->i < la->i && lb->i > la->prev->i)
		return (0);
	/* printf("not pushable without rotations\n"); */
	return (1); // 0 puschable / 1 pas pushable
}

void print_best_move(t_move *best_move, t_list *la, t_list *lb)
{
		printf("\nBEST_MOVE\n");
		printf("move.cheaper = %d\n", best_move->cheaper);
		printf("move.prev = %d\n", best_move->prev);
		printf("move.next = %d\n", best_move->next);
		printf("move.rr = %d\n", best_move->rr);
		printf("move.rrr = %d\n", best_move->rrr);
		printf("move.ra = %d\n", best_move->ra);
		printf("move.rb = %d\n", best_move->rb);
		printf("move.rra = %d\n", best_move->rra);
		printf("move.rrb = %d\n", best_move->rrb);
		printf("move.cost = %d\n", best_move->cost);
		printf("la :\n");
		print_lst(la);
		printf("lb :\n");
		print_lst(lb);
		printf("\n");
	sleep(1);

}

void	get_cheaper(t_list **la, t_list **lb, t_move *best_move)
{
	t_list	*tmp_A;
	t_list	*tmp_B;
	t_move	move;
	int		count_A;
	int		count_B;

	//
	//implementer is_pushable
	//les rra et rrb sont mal set !!
	//
	init_move(&move, tmp_B); // a virer  ?
	init_move(best_move, tmp_B); // a virer  ?
	// Si on est dans la situation ou y'a rien a rotate : juste push et c'est bon
	/* if ((*lb)->i < (*la)->i && (*lb)->i > (*lb)->prev->i) */
	if (!is_pushable(*la, *lb))
	{
		/* printf("top B is pushable without any rotations\n"); */
		/* printf("(*la)->i = %d | (*la)->prev->i = %d\n", (*la)->i, (*la)->prev->i); */
		cheapest_move(la, lb, best_move);
		/* print_best_move(best_move, *la, *lb); */
		/* printf("i = %d | next = %d | prev = %d\n", best_move->cheaper, best_move->next, best_move->prev); */
		do_rotates(la, lb, best_move);
		pa(la, lb);
		/* printf("----------------------\n"); */
		return ;
	}
	// pour chaque node de b :
	// combien de rotation de B pour l'avoir en haut
	// combien de rotation dans A pour avoir la bonne place ?
	count_A = 0;
	tmp_A = *la;
	// cas de base : combien tourner A pour juste push A sans tourner B
	while (is_pushable(tmp_A, *lb))
	{
		count_A++;
		tmp_A = tmp_A->next;
	}
	only_rotate_A(la, lb, best_move, count_A);
	best_move->prev = tmp_A->prev->i;
	best_move->next = tmp_A->i;
	/* printf("i = %d | next = %d | prev = %d\n", best_move->cheaper, best_move->next, best_move->prev); */
	// on cherche dans tous le reste de B :
	tmp_B = (*lb)->next;
	count_B = 1;                  // un pour la premiere rotation
	while (tmp_B->start == false) // pour chaque element de B
	{
		init_move(&move, tmp_B);
		tmp_A = *la;
		count_A = 0;
		// on cherche l'emplacement dans A
		while (is_pushable(tmp_A, *lb))
		{
			count_A++;
			tmp_A = tmp_A->next;
			/* printf("tmp_A = %d | i = %d | next = %d | prev = %d\n", tmp_A->i, (*lb)->i, tmp_A->i, tmp_A->prev->i); */
			//ICI probleme dans le set du next / prev : TMP A ne bouge pas 
		}
		move.prev = tmp_A->prev->i;
		move.next = tmp_A->i;
		// ici on a trouver l'emplacement de A pour inserer le B
		// on stock les rotations de A
		if (count_A > lst_size(*la) / 2)
		{
			// on stock aussi la position ? prev et next ?
			move.rra = lst_size(*la) - count_A;
			move.ra = 0;
		}
		else
		{
			move.ra = count_A;
			move.rra = 0;
		}
		// on stock les rotations de B
		if (count_B > lst_size(*lb) / 2)
		{
			move.rrb = lst_size(*lb) - count_B;
			move.rb = 0;
		}
		else
		{
			move.rb = count_B;
			move.rrb = 0;
		}
		// Voir si on peut combiner RR RRR ?
		if (move.ra > 0 && move.rb > 0) // si je rotate les deux
		{
			if (move.ra == move.rb)
			{
				move.rr = move.ra;
				move.ra = 0;
				move.rb = 0;
			}
			else if (move.ra > move.rb) // mais plus ra
			{
				move.rr = move.rb;
				move.ra = move.ra - move.rb;
				move.rb = 0;
			}
		}
		else if (move.rra > 0 && move.rrb > 0) // si je reverse rotate les deux
		{
			if (move.rra == move.rrb)
			{
				move.rrr = move.rra;
				move.rra = 0;
				move.rrb = 0;
			}
			else if (move.rra > move.rrb)
			{
				move.rrr = move.rrb;
				move.rra = move.rra - move.rrb;
				move.rrb = 0;
			}
			else if (move.rra < move.rrb)
			{
				move.rrr = move.rra;
				move.rrb = move.rrb - move.rra;
				move.rra = 0;
			}
		}
		// si les deux tournent dans deux sens differents on fait rien ?
		move.cost = move.rr + move.rrr + move.ra + move.rb + move.rra + move.rrb;
		if (move.cost < best_move->cost)
			*best_move = move; //pas sur de ca ?         
		tmp_B = tmp_B->next;
		count_B++; // pour chaque element de B, on a une rotation de plus
	}
	//normalement, on a recupere un Best_move 
	/* print_best_move(best_move, *la, *lb); */
	do_rotates(la, lb, best_move);
	pa(la, lb);
	/* printf("----------------------\n"); */
}

int	cheaper_insertion(t_list **la, t_list **lb)
{
	t_move	move;
	t_list 	*tmp;
	int count;

	/* printf("\nCheaper insertion\n"); */
	while (lst_size(*lb) > 1)
	{
		get_cheaper(la, lb, &move); // renommer : on get cheaper et on rotate
		/* sleep (1); */
	}
	if (lst_size(*lb) == 1)
	{
		/* printf("THIS IS LAST PUSHA : %d\n", (*lb)->i); */
		if (!is_pushable(*la, *lb))
			pa(la, lb);
		else 
		{
			tmp = (*la)->next;
			count = 1;
			while (tmp->start == false)
			{
				if (!is_pushable(tmp, *lb))
					break ;
				tmp = tmp->next;
				count++;
			}
			if (count > lst_size(*la) / 2)
			{
				while (lst_size(*la) - count > 0)
				{
					count--;
					rra(la);
				}
				pa(la, lb);
			}
			while (count > 0)
			{
				count--;
				ra(la);
			}
			pa(la, lb);
		}
		//on rotate pour retrouver la liste A avec min en haut
		tmp = *la;
		count = 0;
		while (tmp->i != 0)
		{
			count++;
			tmp = tmp->next;
		}
		if (count > lst_size(*la) / 2)
		{
			count = lst_size(*la) - count;
			while (count > 0)
			{
				count--;
				rra(la);
			}
		}
		while (count > 0)
		{
			count--;
			ra(la);
		}
	}
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
	/* printf("==========================\nstack initialized :\n"); */
	/* print_lst(la); */
	/* printf("==========================\n\n"); */
	/* sleep(1); */
	if (lst_size(la) <= 3)
		size_3_sort(&la);
	else
	{
		partition_stacks(&la, &lb);
		size_3_sort(&la);
		cheaper_insertion(&la, &lb);
	}
	/* sort(&la, &lb); */
	/* printf("\n========================\n"); */
	/* printf("la :\n"); */
	print_lst(la);
	/* printf("lb :\n"); */
	/* print_lst(lb); */
	if (is_sorted_check(la))
		printf("\nLIST SORTED\n");
	free_list(&la);
	free_list(&lb);
	return (0);
}
