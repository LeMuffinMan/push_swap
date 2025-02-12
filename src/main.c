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
// init.c ranger diviser et clean
// my_algo.c : clean et partition / pivot opti
// pa.c : header 42
// parsing.c : libft + edgecases / input cases a revoir + ranger
// pb.c : ranger comme pa 
// reverse_rotations.c : header42
// rotations.c : header42
// size_3_sort.c : ranger cleaner + header42
// swap.c : header 42 : faire dossier ops
// update_list_infos.c : header 42 + clean et pivot a virer 
// utils : ranger + libft plus clean 
//
// split : gerer plus de sep que juste ' ' ?

int	main(int ac, char **av)
{
	t_list	*la;
	t_list *lb;

	la = NULL;
 	lb = NULL; 
	if (ac <= 1)  
		exit (1);
	init_stack(&la, ac, av);
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
	free_list(&la);
	free_list(&lb);
	return (0);
}
