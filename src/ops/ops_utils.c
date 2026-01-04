/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:31:43 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/14 10:58:33 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void stack_empty_case(t_stack **l, t_stack **tmp) {
  (*tmp)->prev = *tmp;
  (*tmp)->start = TRUE;
  (*tmp)->next = *tmp;
  *l = *tmp;
}

void take_out_stack_top(t_stack **la, t_stack **lb, t_stack **node) {
  t_stack *last;

  last = (*lb)->prev;
  (*lb)->start = FALSE;
  *lb = (*lb)->next;
  (*lb)->start = TRUE;
  (*lb)->prev = last;
  last->next = *lb;
  (*node)->next = *la;
}

void stack_one_node_case(t_stack **l, t_stack **tmp) {
  (*l)->next = *tmp;
  (*l)->prev = *tmp;
  (*l)->next->next = *(l);
  (*l)->prev->prev = *(l);
  (*l)->start = FALSE;
  (*l)->next->start = TRUE;
  *l = *tmp;
}

void plug_on_stack(t_stack **l, t_stack **tmp) {
  (*l)->prev->next = *tmp;
  (*tmp)->prev = (*l)->prev;
  (*l)->prev = (*tmp);
  (*tmp)->next = *l;
  (*l)->start = FALSE;
  *l = *tmp;
  (*tmp)->start = TRUE;
}
