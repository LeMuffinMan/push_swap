/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:49:41 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/14 13:11:32 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

int is_sorted(t_stack *la) {
  t_stack *tmp;

  tmp = la;
  while (1) {
    if (tmp->i > tmp->next->i && tmp->next->start == FALSE)
      return (1);
    tmp = tmp->next;
    if (tmp->start)
      break;
  }
  return (0);
}

int main(int ac, char **av) {
  t_stack *lb;
  t_stack *la;
  int size;
  int median;

  la = NULL;
  lb = NULL;
  if (ac <= 1 || init_stack(&la, ac, av) || !is_sorted(la))
    free_list(&la);
  else if (lst_size(la) <= 3)
    easy_cases(&la);
  else {
    size = lst_size(la);
    median = size * 0.5;
    my_algo(&la, &lb, size, median);
  }
  free_list(&la);
  free_list(&lb);
  return (0);
}
