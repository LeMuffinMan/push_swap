/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:03:41 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/13 14:31:37 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

void rra(t_stack **l) {
  if (*l == NULL || *l == (*l)->next)
    return;
  (*l)->prev->start = TRUE;
  (*l)->start = FALSE;
  *l = (*l)->prev;
  write(1, "rra\n", 4);
}

void rrb(t_stack **l) {
  if (*l == NULL || *l == (*l)->next)
    return;
  (*l)->prev->start = TRUE;
  (*l)->start = FALSE;
  *l = (*l)->prev;
  write(1, "rrb\n", 4);
}

void rrr(t_stack **la, t_stack **lb) {
  if (*la == NULL || *la == (*la)->next)
    return;
  (*la)->prev->start = TRUE;
  (*la)->start = FALSE;
  *la = (*la)->prev;
  if (*lb == NULL || *lb == (*lb)->next)
    return;
  (*lb)->prev->start = TRUE;
  (*lb)->start = FALSE;
  *lb = (*lb)->prev;
  write(1, "rrr\n", 4);
}
