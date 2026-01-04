/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:45:08 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/15 17:15:49 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/checker_bonus.h"

static void swap_elements(int *tab, unsigned int n1, unsigned int n2) {
  int tmp;

  tmp = tab[n1];
  tab[n1] = tab[n2];
  tab[n2] = tmp;
}

static void bubble_sort(int *tab, unsigned int size) {
  unsigned int i;
  unsigned int j;

  i = 0;
  j = 0;
  while (i < size) {
    j = 0;
    while (j < size - 1) {
      if (tab[j] > tab[j + 1])
        swap_elements(tab, j, j + 1);
      j++;
    }
    i++;
  }
}

void sort_int_tab(int *tab, unsigned int size) {
  if (size <= 1)
    return;
  bubble_sort(tab, size);
}
