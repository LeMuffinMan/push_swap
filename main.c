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
	while (array[i] != '\0') //si je met juste array[i] : si il vaut 0 la boucle s'arrete
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
		while (array[i])
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

// on veut garder 3 valeurs a gauche : on envoie a droite en pretriant
// tant que size A > 3
// si n == min || n == max : ra
// si > pivot : pb et rb
// esle pb

// a tester
// quoi faire qund count sont egaux ? prend la derniere je capte pas pourquoi ?
int	get_moves_count(t_list *la, t_list *lb, int i)
{
	t_list	*tmp;
	int		count;
	int		j;
	int size;

	size = lst_size(lb);
	tmp = lb;
	j = 0; // un pour push
	// cb de rota pour faire monter i en haut de lb ?
	while (tmp->i != i) //ajouter une borne ?
	{
		tmp = tmp->next;
		j++; // j ++ pour chaque rotations
	}
	if (j > size / 2)
		j = size - j; // on peut acceder au milieu en rotatant dans l'autre sens
	// ici, j = le nombre de rotation / rrotation pour avoir i en haut de lb
	if (i == la->i - 1)
	{
		/* printf("i = %d | count = %d\n", i, j); */
		return (j + 1); // si on doit le push simplement : count = rotations + push
	}
	tmp = la->next;
	count = 1; // le premier est pas bon donc on a une rotation au moins a faire
	while (tmp->start == false)
		// tant qu'on n'a pas fait le tour de la sans trouver ou mettre i
	{
		if (i == tmp->i - 1) // ajouter le + 1 !!
			break ;
		count++;
		tmp = tmp->next;
	}
	if (count > size / 2)
		count = size - count;
	count += j;
	/* printf("i = %d | count = %d | j = %d\n", i, count, j); */
	return (count + 1);
}

int	get_cheaper_i(t_list **la, t_list **lb)
{
	t_list	*tmp;
	int		i;
	int		cheaper;

	tmp = *lb;
	cheaper = get_moves_count(*la, *lb, tmp->i);
	tmp = tmp->next;
	while (tmp->start == false)
	{
		if (get_moves_count(*la, *lb, tmp->i) < cheaper)
			cheaper = tmp->i;
		tmp = tmp->next;
	}
	/* printf("cheaper = %d\n", cheaper); */
	return (cheaper);
}

int get_rot_dir(t_list *l, int index, int size)
{
	t_list *tmp;
	int i;

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

//reecrire is sorted sur ce modele
void inverted_size_3_sort(t_list **l)
{
	/* print_lst(*l); */
	int a;
	int b;
	int c;

	a = (*l)->i;
	b = (*l)->next->i;
	c = (*l)->prev->i;
	if (lst_size(*l) == 2 && a < b)
		sb(l);
	else if (lst_size(*l) == 3)
	{
		if (a < b && b < c && b < c)         // 1 2 3 -> sb + rrb
		{
			sb(l);
			rrb(l);
		}
		else if (a < b && a < c && b > c)    // 1 3 2 -> rb
			rb(l);
		else if (a > b && a < c && b < c)    // 2 1 3 -> rrb
			rrb(l);
		else if (a < b && a > c && b > c)    // 2 3 1 -> sb
			sb(l);
		else if (a > b && a > c && b < c)    // 3 1 2 -> sb + rb
		{
			sb(l);
			rb(l);
		}
	}
}

void	sort(t_list **la, t_list **lb)
{
	int	median;
	int	size_A;
	int	size_B;
	int	*array;
	int	i;

	size_A = lst_size(*la);
	array = lst_to_array(la, size_A);
	median = array[size_A / 2]; // faire une structure qui contient ces infos ?
	/* get_index(la, array); */
	free(array);
	/* printf("min = %d | max = %d | median = %d\n", min, max, median); */
	while (lst_size(*la) > 3)
	{
		/* printf("(*la)->i = %d | size_A = %d\n", (*la)->i, size_A); */
		if ((*la)->i == 0) // on a le min
			ra(la);
		else if ((*la)->i == size_A - 1) // on a le max
			ra(la);
		else if ((*la)->i == size_A / 2)
			ra(la);
		else
		{
			if ((*la)->i > size_A / 2)
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
	//on push le moins cher possible dans A a chaque fois
	while (lst_size(*lb) > 3)
	{
		//recuperer une structure de get_cheaper : 
		//le i a move
		//avant quel i dans la
		//apres quel i dans la 
			//ma boucle devient : while ((*la)->i != i + 1 et (*la)->prev-> != i - 1)
		i = get_cheaper_i(la, lb);
		/* printf("la :\n"); */
		/* print_lst(*la); */
		/* printf("lb :\n"); */
		/* print_lst(*lb); */

		//optimiser ici : get_cheaper me ramene le meilleur indice pour 
			//rotate B
			//rotate A
			//push A
		//SI je rotate A et B dans le meme sens je veux en profiter
		if (get_rot_dir(*la, i + 1, size_A) > 0)
		{
			//boucle infinie ici pour quelques nb de valeurs
			while ((*la)->i != (i + 1) && (*la)->prev->i != (i - 1))
				ra(la);
		}
		else if (get_rot_dir(*la, i + 1, size_A) < 0)
		{
			while ((*la)->i != i + 1)
				rra(la);
		}
		size_B = lst_size(*lb);
		if (get_rot_dir(*lb, i, size_B) > 0)
		{
			while ((*lb)->i != i)
				rb(lb);
		}
		else if (get_rot_dir(*lb, i + 1, size_B) < 0)
		{
			while ((*lb)->i != i)
				rrb(lb);
		}
		pa(la, lb);
	}
	inverted_size_3_sort(lb); //ici : optimiser pour tourner en meme temps
	//tourner a pour avoir le bon emplacement pour push
	if (get_rot_dir(*la, (*lb)->i + 1, size_A) > 0)
	{
		while ((*la)->i != (*lb)->i + 1)
			ra(la);
	}
	else if (get_rot_dir(*la, (*lb)->i + 1, size_A) < 0)
	{
		while ((*la)->i != (*lb)->i + 1)
			rra(la);
	}
	while (*lb)
		pa(la, lb);
	if (get_rot_dir(*la, 0, lst_size(*la)) > 0)
	{
		while ((*la)->i != 0)
			ra(la);
	}
	else if (get_rot_dir(*la, 0, lst_size(*la)) < 0)
	{
		while ((*la)->i != 0)
			rra(la);
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
		exit(1);
	}
	init_stack(&la, ac, av);
	/* printf("list_size(*lb) = %d\n", lst_size(lb)); */
	/* printf("==========================\nstack initialized :\n"); */
	/* print_lst(la); */
	/* printf("==========================\n\n"); */
	/* partition_setup(&la, &lb); */
	/* printf("la :\n"); */
	/* print_lst(la); */
	/* printf("lb :\n"); */
	/* print_lst(lb); */
	if (lst_size(la) <= 3)
		size_3_sort(&la);
	else
		sort(&la, &lb);
	/* 	insertion_sort(&la, &lb); */
	/* printf("\n========================\n"); */
	/* printf("la :\n"); */
	/* print_lst(la); */
	/* printf("la->n = %d start = %d | la->next->n = %d  start =
		%d  | la->prev->n = %d  start = %d\n", la->n, la->start, la->next->n,
		la->next->start, la->prev->n, la->prev->start); */
	/* printf("lb :\n"); */
	/* print_lst(lb); */
	//revoir is sorted .....
	/* if (is_sorted_check(la)) */
	/* 	printf("\nLIST SORTED\n"); */
	free_list(&la);
	free_list(&lb);
	return (0);
}
// dans fractol je declare une struct : ici je declare un pointeur sur la struct :
// C'EST POUR CA QUE envoyer &l ici peut etre recupere en **lst
