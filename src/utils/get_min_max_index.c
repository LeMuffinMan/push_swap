#include "push_swap.h"

int get_min_index(t_list **l)
{
	int min;
	t_list *tmp;

	min = (*l)->i;
	tmp = (*l)->next;
	while (!tmp->start)
	{
		if (tmp->i < min)
			min = tmp->i;
		tmp = tmp->next;
	}
	return (min);
}

int get_max_index(t_list **l)
{
	int max;
	t_list *tmp;

	max = (*l)->i;
	tmp = (*l)->next;
	while (!tmp->start)
	{
		if (tmp->i > max)
			max = tmp->i;
		tmp = tmp->next;
	}
	return (max);
}
