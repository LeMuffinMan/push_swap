#include "push_swap.h"

//a revoir !!
static int is_A_setup(t_list *la)
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

void	partition_stacks(t_list **la, t_list **lb, int median, int size)
{
	t_list *tmp;

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

	get_dests (la, lb);
	get_rots (la);
	get_rots (lb);
	get_dest_rots(la, lb);
	get_costs(lb); 
	get_position(la);
	get_position(lb);
  cheaper = get_cheaper_insertion(lb);
	get_nodes_to_top(la, lb, cheaper);
	pa(la, lb);
	return (0);
}

void final_rotate(t_list **la)
{
	t_list *tmp;

	get_position(la);
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

