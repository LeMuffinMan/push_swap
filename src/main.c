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
#include <stdlib.h>

//my_algo
	//easy_cases : header 42
	//get_cheaper_instertion : header 42
	//get_nodes_to_top : header 42 
	//my_algo.c : revoir is_a_setup + header 42 
	//update_list_infos : header 42 

//ops : write ??
 	//pa : combiner avec addfirstnode ? header 42
	//pb : sur le modelee de pa + header 42
  //tous : ft_printf ou write !

//utils
  //array_utils static ou libft ? header
	//lst_utils : clean + booleen ? + libft + header
  //debug a virer
  //get_min_max : header 42
  //libft modifiee ?

//main.c : renommer ?
//libft : integrer 
//init.c : done
//
// split : gerer plus de sep que juste ' ' ?
//
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
