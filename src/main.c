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

// debug.c a virer a la fin
// get_cheaper_instertion.c : header 42
// get_min_max_index.c : header 42
// get_nodes_to_top.c : header 42
// my_algo.c : is_setup a revoir ajouter header
// pa.c : header 42
// parsing.c : libft + edgecases / input cases a revoir + ranger
// pb.c : ranger comme pa 
// reverse_rotations.c : header42
// rotations.c : header42
// size_3_sort.c : renommer fichier et makefile + header42
// swap.c : header 42 : faire dossier ops
// update_list_infos.c : header 42 +  
// utils : ranger + libft plus clean 
//
// split : gerer plus de sep que juste ' ' ?
//
// init.c done
//

int	main(int ac, char **av)
{
	t_list	*la;
	t_list *lb;
	int size;
	int median;

	la = NULL;
 	lb = NULL; 
	if (ac <= 1)  
		exit (1);
	init_stack(&la, ac, av);
	if (lst_size(la) <= 3)
		easy_cases(&la);
	else
	{
		size = lst_size(la);
		median = size / 2;
		partition_stacks(&la, &lb, median, size);
		easy_cases(&la);
		while (lb)
			insert_cheaper(&la, &lb);
		final_rotate(&la);
	}
	free_list(&la);
	free_list(&lb);
	return (0);
}
