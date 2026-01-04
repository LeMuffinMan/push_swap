/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_cases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:02:33 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/13 14:02:37 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void one_operation_cases(t_stack **la) {
  if ((*la)->n > (*la)->next->n && (*la)->n < (*la)->next->next->n &&
      (*la)->next->n < (*la)->next->next->n)
    sa(la);
  else if ((*la)->n < (*la)->next->n && (*la)->n > (*la)->next->next->n &&
           (*la)->next->n > (*la)->n && (*la)->next->n > (*la)->next->next->n)
    rra(la);
  else if ((*la)->n > (*la)->next->n && (*la)->n > (*la)->next->next->n &&
           (*la)->next->n < (*la)->n && (*la)->next->n < (*la)->next->next->n)
    ra(la);
}

void easy_cases(t_stack **la) {
  if (lst_size(*la) == 2)
    sa(la);
  else if (lst_size(*la) == 3) {
    one_operation_cases(la);
    if ((*la)->n > (*la)->next->n && (*la)->n > (*la)->next->next->n &&
        (*la)->next->n < (*la)->n && (*la)->next->n > (*la)->next->next->n) {
      ra(la);
      sa(la);
    } else if ((*la)->n < (*la)->next->n && (*la)->n < (*la)->next->next->n &&
               (*la)->next->n > (*la)->n &&
               (*la)->next->n > (*la)->next->next->n) {
      sa(la);
      ra(la);
    }
  }
}
