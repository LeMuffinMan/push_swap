/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:28:36 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/30 16:04:35 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h> // a virer 
//
int init_stack(t_list **l, char **av)
{
  int i;
  int j;
  char **splitted;

  j = 0;
  i = 0;
  if (!av[1][0])
    return (-1);
  splitted = ft_split(av[1], ' '); // penser a gerer plus de sep : tout ce qui n'est pas un - + ou un digit *l ?
  *l = fill_list(splitted);
  i = 0;
  return (0);
}

//a virer 

void init_stackb(t_list **l)
{
  int i;

  i = -6;
  while (++i < 0)
    add_back(l, i);
}

