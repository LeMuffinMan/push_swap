#include "push_swap.h"
#include <stdlib.h>

//static ou libft ?

static void	swap_elements(int *tab, unsigned int p1, unsigned int p2)
{
	int tmp = tab[p1];
	tab[p1] = tab[p2];
	tab[p2] = tmp;
}

static void	bubble_sort(int *tab, unsigned int size)
{
	unsigned int i = 0;
	unsigned int j = 0;

	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (tab[j] > tab[j + 1])
				swap_elements(tab, j, j + 1);
			j++;
		}
		i++;
	}
}



static void	sort_int_tab(int *tab, unsigned int size)
{
	if (size <= 1)
		return ;
	bubble_sort(tab, size);
}

int	*lst_to_array(t_list **la, int size)
{
	int	*array;
	int	i;
	t_list *tmp;

	array = (int *)malloc(sizeof(int) * size); //revoir ca 
	if (!array)
		return (NULL);
	array[0] = (*la)->n;
	i = 1;
	tmp = (*la)->next;
	while (tmp->start == false)
	{
		array[i] = tmp->n;
		i++;
		tmp = tmp->next;
	}
	sort_int_tab(array, i);
	return (array);
}

