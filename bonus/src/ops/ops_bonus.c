/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_on_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:03:27 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/15 16:49:50 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/checker_bonus.h"

void push(t_stack **la, t_stack **lb) {
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
}

void swap(t_stack **l) {
  int tmp;

  if (*l == NULL || *l == (*l)->next)
    return;
  tmp = (*l)->n;
  (*l)->n = (*l)->next->n;
  (*l)->next->n = tmp;
  tmp = (*l)->i;
  (*l)->i = (*l)->next->i;
  (*l)->next->i = tmp;
}

void rotations(t_stack **l) {
  if (*l == NULL || *l == (*l)->next)
    return;
  (*l)->start = FALSE;
  (*l)->next->start = TRUE;
  *l = (*l)->next;
}

void reverse_rotations(t_stack **l) {
  if (*l == NULL || *l == (*l)->next)
    return;
  (*l)->prev->start = TRUE;
  (*l)->start = FALSE;
  *l = (*l)->prev;
}
