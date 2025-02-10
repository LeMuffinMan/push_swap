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
//
// Voir le pivot opti
//

int	main(int ac, char **av)
{
	t_list	*la;

	la = NULL;
	t_list *lb = NULL; 
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
		/* partition_in_B(&la, &lb); */
		size_3_sort(&la);
		while (lb)
			insert_cheaper(&la, &lb);
		final_rotate(&la);
	}
	/* printf("\n========================\n"); */
	/* printf("la :\n"); */
	/* print_lst2(la); */
	/* printf("lb :\n"); */
	/* print_lst2(lb); */
	/* if (is_sorted_check(la)) */
	/* 	printf("\nLIST SORTED\n"); */
	free_list(&la);
	free_list(&lb);
	return (0);
}
