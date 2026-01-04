/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_on_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:03:27 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/14 10:54:48 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

void pa(t_stack **la, t_stack **lb) {
  t_stack *tmp;

  if (*lb == NULL)
    return;
  tmp = *lb;
  if (tmp == (*tmp).next)
    *lb = NULL;
  else
    take_out_stack_top(la, lb, &tmp);
  if (*la == NULL)
    stack_empty_case(la, &tmp);
  else if (*la == (*la)->next && *la == (*la)->prev)
    stack_one_node_case(la, &tmp);
  else
    plug_on_stack(la, &tmp);
  write(1, "pa\n", 3);
}

void pb(t_stack **lb, t_stack **la) {
  t_stack *tmp;

  if (*lb == NULL)
    return;
  tmp = *lb;
  if (tmp == (*tmp).next)
    *lb = NULL;
  else
    take_out_stack_top(la, lb, &tmp);
  if (*la == NULL)
    stack_empty_case(la, &tmp);
  else if (*la == (*la)->next && *la == (*la)->prev)
    stack_one_node_case(la, &tmp);
  else
    plug_on_stack(la, &tmp);
  write(1, "pb\n", 3);
}
