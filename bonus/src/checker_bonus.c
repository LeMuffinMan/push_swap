/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:11:56 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/15 17:33:58 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/checker_bonus.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	t_stack	*la;
	t_stack	*lb;

	la = NULL;
	lb = NULL;
	if (ac <= 1)
		exit(1);
	init_stack(&la, ac, av);
	if (get_ops(&la, &lb))
	{
		free_list(&la);
		free_list(&lb);
		exit(1);
	}
	if (is_sorted_check(la) && lb == NULL)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_list(&la);
	free_list(&lb);
	return (0);
}
