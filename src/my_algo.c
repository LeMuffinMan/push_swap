#include "push_swap.h"
#include <stdio.h>
#include <unistd.h>

int is_A_setup(t_list *la)
{
	int min;
	t_list *tmp;
	t_list *min_node;

	min = get_min_index(&la);
	tmp = la;
	while (tmp->i != min)
	{
		tmp = tmp->next;
		if (tmp->start)
			break ;
	}
	min_node = tmp;
	while (1)
	{
		if (tmp->next->i < tmp->i)
			break ;
		tmp = tmp->next;
	}
	if (tmp->next == min_node)
		return (1);
	return (0);
}

void	partition_stacks(t_list **la, t_list **lb)
{
	t_list *tmp;
	int size;
	int median;

	size = lst_size(*la);
	median = size / 2;
	tmp = *la;
	while (lst_size(*la) > 3 && !is_A_setup(*la))
	{
		if (tmp->i == size - 1)
			ra(la);
		else
		{	
			pb(la, lb);
			if ((*lb)->i <= median)
			{
				if (tmp->next->i == size - 1)
					rr(la, lb);
				else
					rb(lb);
			}
		}
		tmp = tmp->next;
	}
}

int insert_cheaper(t_list **la, t_list **lb)
{
	int cheaper;

	//une fonction update_lists
	get_dests (la, lb); // on cherche a quel endroit on doit situer le node B dans A
	get_rots (la); // on setup les rots pour chaque nodes
	get_rots (lb); // on setup les rots pour chaque nodes
	get_dest_rots(la, lb);
	get_costs(lb); // on peut donc calculer le coups pour chaque node B
	get_position(la);
	get_position(lb);

	//deplacer cette condition plus bas
	if (lst_size(*lb) > 1)	
		cheaper = get_cheaper_insertion(lb);
	else
		cheaper = (*lb)->i;
	//faire une fonction execute_insertion
	////diviser en bring_cheaper to top
	///bring dest top top
	get_cheaper_and_dest_to_top(la, lb, cheaper);
	pa(la, lb);
	return (0);
}

void final_rotate(t_list **la)
{
	t_list *tmp;

	tmp = (*la)->next;
	while(!tmp->start)
	{
		if (tmp->i == 0)
			break;
		tmp = tmp->next;
	}
	if (tmp->pos > lst_size(*la) / 2)
	{
		while ((*la)->i != 0)
			rra(la);
	}
	else 
	{
		while ((*la)->i != 0)
			ra(la);
	}	
}

