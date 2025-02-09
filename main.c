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
	int rot;
	int dest_rot;

		rot = node->rot;
		dest_rot = node->dest_rot;
		/* printf("node #%d | i = %d | rot = %d | rot_dest = %d\n", node->pos, node->i, rot, dest_rot); */
	/* printf("node->dest_rot = %d\n", node->dest_rot); */
		// pb ici, les negatifs donnent des coup = 0
	if (rot >= 0 && dest_rot < 0)
		return (rot + dest_rot * -1);
	if (rot < 0 && dest_rot >= 0)
		return (rot * -1 + dest_rot);
	if (rot >= 0 && dest_rot >= 0)
	{
		if (rot >= dest_rot)
			return (rot);
		else 
			return (dest_rot);
	}
	if (rot < 0 && dest_rot < 0)
	{
		if (rot * -1 >= dest_rot * -1)
			return (rot * -1);
		else 
			return (dest_rot * -1);
	}
}

int get_costs(t_list **lb)
{
/* le coup est le nombre de rot de tmp et de sa cible */ 
	t_list *tmp;
	
	//revoir les couts : + et - a repenser ?
	(*lb)->cost = optimise_rotations(*lb);
	/* printf("i = %d | cost = %d\n", (*lb)->i, (*lb)->cost); */
	tmp = (*lb)->next;
	while (tmp->start == false)
	{
		tmp->cost = optimise_rotations(tmp);
	/* printf("i = %d | cost = %d\n", tmp->i, tmp->cost); */
		tmp = tmp->next;
	}
}


int get_min_index(t_list **l)
{
	int min;
	t_list *tmp;

	min = (*l)->i;
	tmp = (*l)->next;
	while (!tmp->start)
	{
		if (tmp->i < min)
			min = tmp->i;
		tmp = tmp->next;
	}
	return (min);
}

int get_max_index(t_list **l)
{
	int max;
	t_list *tmp;

	max = (*l)->i;
	tmp = (*l)->next;
	while (!tmp->start)
	{
		if (tmp->i > max)
			max = tmp->i;
		tmp = tmp->next;
	}
	return (max);
}

int get_dests(t_list **la, t_list **lb)
{
	t_list *tmp_A;
	t_list *tmp_B;
	int max_index;
	int min_index;

	max_index = get_max_index(la);
	min_index = get_min_index(la);
	/* printf("max = %d | min = %d\n", max_index, min_index); */
	(*lb)->dest = max_index;
	if ((*lb)->i > max_index)
		(*lb)->dest = min_index;
	else if ((*la)->i > (*lb)->i && (*la)->i < (*lb)->dest)
		(*lb)->dest = (*la)->i;
	tmp_A = (*la)->next;
	while (tmp_A->start == false && (*lb)->dest != min_index)
	{
		if (tmp_A->i > (*lb)->i && tmp_A->i < (*lb)->dest)
			(*lb)->dest = tmp_A->i;
		tmp_A = tmp_A->next;
	}
	/* printf("i = %d | dest = %d\n", (*lb)->i, (*lb)->dest); */
	tmp_B = (*lb)->next;
	while (tmp_B->start == false)
	{
		tmp_B->dest = max_index;
		if (tmp_B->i > max_index)
			tmp_B->dest = min_index;
		else if ((*la)->i > tmp_B->i && (*la)->i < tmp_B->dest)
			tmp_B->dest = (*la)->i;
		tmp_A = (*la)->next;
		while (tmp_A->start == false && tmp_B->dest != min_index)
		{
			if (tmp_A->i > tmp_B->i && tmp_A->i < tmp_B->dest)
				tmp_B->dest = tmp_A->i;
			tmp_A = tmp_A->next;
		}
		/* printf("i = %d | dest = %d\n", tmp_B->i, tmp_B->dest); */
		tmp_B = tmp_B->next;
	}
}

int get_dest_rots(t_list **la, t_list **lb)
{
	t_list *tmp_A;
	t_list *tmp_B;
	int rot;
	int dest;

	dest = (*lb)->dest;
	if ((*la)->i == dest)
		(*lb)->dest_rot = (*la)->rot;
	else
	{
		tmp_A = (*la)->next;
		while (tmp_A->start == false)
		{
			if (tmp_A->i == dest)
				(*lb)->dest_rot = tmp_A->rot;
			tmp_A = tmp_A->next;
		}
	}
	tmp_B = (*lb)->next;
	while (tmp_B->start == false)
	{
		dest = tmp_B->dest;
		if ((*la)->i == dest)
			tmp_B->dest_rot = (*la)->rot;
		else
		{
			tmp_A = (*la)->next;
			while (tmp_A->start == false)
			{
				if (tmp_A->i == dest)
					tmp_B->dest_rot = tmp_A->rot;
				tmp_A = tmp_A->next;
			}
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

//changer de strat : on execute les rotates indiquee par le node choisi
//reecrire do rotate 
//virer rr et rrr de la struct move 
//virer la struct move ?
//
t_move optimise_best_move(t_move move, t_list *la, t_list *lb)
{
	t_list *tmp_A;
	t_list *tmp_B;

	if (move.candidate == lb->i)
	{
		move.dest = lb->dest;
		if (move.dest == la->i)
		{
			if (la->rot >= 0)
				move.ra = la->rot;
			else
				move.rra = la->rot * -1;
		}
		else 
		{
			tmp_A = la->next;
			while (!tmp_A->start)
			{
				if (move.dest == tmp_A->i)
				{
					//si on a deux rotations +
					if (tmp_A->rot >= 0 && lb->rot >= 0)
					{
						if (tmp_A->rot > lb->rot)
						{
							move.rr = lb->rot;
							move.ra = tmp_A->rot - move.rr;
						}
						else
						{
							move.rr = tmp_A->rot;
							move.rb = lb->rot - move.rr;
						}
					}
					else if (tmp_A->rot < 0 && lb->rot < 0)
					{
						if (tmp_A->rot < lb->rot)
						{
							move.rrr = lb->rot * -1;
							move.rra = tmp_A->rot * -1 - move.rrr;
						}
						else
						{
							move.rrr = tmp_A->rot * -1;
							move.rrb = lb->rot * -1 - move.rrr;
						}
					}
				}
				tmp_A = tmp_A->next;
			}
		}
	}
	else 
	{
		tmp_B = lb->next;
		while (!tmp_B->start)
		{
			if (move.candidate == lb->i)
			{
				move.dest = lb->dest;
				if (move.dest == la->i)
				{
					if (la->rot >= 0)
						move.ra = la->rot;
					else
						move.rra = la->rot * -1;
				}
				else 
				{
					tmp_A = la->next;
					while (!tmp_A->start)
					{
						if (move.dest == tmp_A->i)
						{
							//si on a deux rotations +
							if (tmp_A->rot >= 0 && tmp_B->rot >= 0)
							{
								if (tmp_A->rot > tmp_B->rot)
								{
									move.rr = tmp_B->rot;
									move.ra = tmp_A->rot - move.rr;
								}
								else
								{
									move.rr = tmp_A->rot;
									move.rb = tmp_B->rot - move.rr;
								}
							}
							else if (tmp_A->rot < 0 && tmp_B->rot < 0)
							{
								if (tmp_A->rot < tmp_B->rot)
								{
									move.rrr = tmp_B->rot * -1;
									move.rra = tmp_A->rot * -1 - move.rrr;
								}
								else
								{
									move.rrr = tmp_A->rot * -1;
									move.rrb = tmp_B->rot * -1 - move.rrr;
								}
							}
						}
					}
				}
			}
			tmp_B = tmp_B->next;
		}
	}
	return (move);
}

/* int init_cheaper(int dest, t_list *l) */
/* { */
/* 	t_list *cheaper; */
/**/
/* 	if ((*l)->i == dest) */
/* 		cheaper = *l; */
/* 	else */
/* 	{ */
/* 		cheaper = (*l)->next; */
/* 		while (!cheaper->start) */
/* 		{ */
/* 			if ((*l)->i == dest) */
/* 				break ; */
/* 		cheaper = cheaper->next; */
/* 		} */
/* 	} */
/* 	cheaper->candidate = 0; */
/* 	cheaper->dest = 0; */
/* 	cheaper->ra = 0; */
/* 	cheaper->rra = 0; */
/* 	cheaper->rb = 0; */
/* 	cheaper->rrb = 0; */
/* } */

void print_candidate(t_list node)
{
    printf("\nCANDIDATE :\n");
    printf("i = %d\n", node.i);
    printf("dest = %d\n", node.dest);
    printf("rot = %d\n", node.rot);
    printf("dest_rot = %d\n\n", node.dest_rot);
}

int get_cheaper_insertion(t_list **la, t_list **lb)
{
	int cheaper;
	t_list *tmp;
	int min_cost;
	
	/* init_cheaper(&cheaper); */

	min_cost = (*lb)->cost;
	cheaper = (*lb)->i;
	tmp = (*lb)->next;
	while (!tmp->start)
	{
		if (tmp->cost < min_cost)
		{
			min_cost = tmp->cost;
			cheaper = tmp->i;
		}
		tmp = tmp->next;
	}
	/* cheaper = optimise_best_move(cheaper, *la, *lb); */
	/* print_move(cheaper); */
	return (cheaper);	
}

int get_cheaper_and_dest_to_top(t_list **la, t_list **lb, int cheaper)
{
	t_list *candidate;
	t_list *dest;

	if ((*lb)->i == cheaper)
		candidate = *lb;
	else
	{
		candidate = (*lb)->next;
		while (!candidate->start)
		{
			if (candidate->i == cheaper)
				break ;
			candidate = candidate->next;
		}
	}
	if ((*la)->i == candidate->dest)
		dest = *la;
	else
	{
		dest = (*la)->next;
		while (!dest->start)
		{
			if (candidate->dest == dest->i)
				break ;
			dest = dest->next;
		}
	}
	//on a nos deux nodes a faire remonter
	printf("getting %d and %d up\n", candidate->i, dest->i);
	while (candidate->rot > 0 && dest->rot > 0)
	{
		rr(la, lb);
		candidate->rot--;
		dest->rot--;
	}
	while (candidate->rot < 0 && dest->rot < 0)
	{
		rrr(la, lb);
		candidate->rot++;
		dest->rot++;
	}
	while (candidate->rot > 0)
	{
		rb(lb);
		candidate->rot--;
	}
	while (candidate->rot < 0)
	{
		rrb(lb);
		candidate->rot++;
	}
	while (dest->rot > 0)
	{
		ra(la);
		dest->rot--;
	}
	while (dest->rot < 0)
	{
		rra(la);
		dest->rot++;
	}

}

int insert_cheaper(t_list **la, t_list **lb)
{
	int cheaper;

	get_dests (la, lb); // on cherche a quel endroit on doit situer le node B dans A
	get_rots (la); // on setup les rots pour chaque nodes
	get_rots (lb); // on setup les rots pour chaque nodes
	get_dest_rots(la, lb);
	get_costs(lb); // on peut donc calculer le coups pour chaque node B
	printf("=========================================\n");
	printf("la :\n");
	print_lst2(*la);
	printf("lb :\n");
	print_lst2(*lb);

	if (lst_size(*lb) > 1)	
		cheaper = get_cheaper_insertion(la, lb);
	else
		cheaper = (*lb)->i;
	get_cheaper_and_dest_to_top(la, lb, cheaper);
	/* do_rotates(la, lb, &move); */
	pa(la, lb);
	printf("la :\n");
	print_lst2(*la);
	printf("lb :\n");
	print_lst2(*lb);
	/* sleep(1); */
	return (0);
}

int final_rotate(t_list **la)
{
	t_list *tmp;

	tmp = (*la)->next;
	while(!tmp->start)
	{
		if (tmp->i == 0)
			break;
		tmp = tmp->next;
	}
	if (tmp->pos > lst_size(*la) / 2)
	{
		while ((*la)->i != 0)
			rra(la);
	}
	else 
	{
		while ((*la)->i != 0)
			ra(la);
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
		while (lb)
			insert_cheaper(&la, &lb);
		final_rotate(&la);
	}
	printf("\n========================\n");
	printf("la :\n");
	print_lst2(la);
	printf("lb :\n");
	print_lst2(lb);
	if (is_sorted_check(la))
		printf("\nLIST SORTED\n");
	free_list(&la);
	free_list(&lb);
	return (0);
}
