#include "push_swap.h"

int get_cheaper_insertion(t_list **la, t_list **lb)
{
	int cheaper;
	t_list *tmp;
	int min_cost;
	
	min_cost = (*lb)->cost;
	cheaper = (*lb)->i;
	tmp = (*lb)->next;
	while (!tmp->start)
	{
		if (tmp->cost < min_cost)
		{
			min_cost = tmp->cost;
			cheaper = tmp->i;
		}
		tmp = tmp->next;
	}
	return (cheaper);	
}

int optimise_rotations(t_list *node)
{
	int rot;
	int dest_rot;

		rot = node->rot;
		dest_rot = node->dest_rot;
	if (rot >= 0 && dest_rot < 0)
		return (rot + dest_rot * -1);
	if (rot < 0 && dest_rot >= 0)
		return (rot * -1 + dest_rot);
	if (rot >= 0 && dest_rot >= 0)
	{
		if (rot >= dest_rot)
			return (rot);
		else 
			return (dest_rot);
	}
	if (rot < 0 && dest_rot < 0)
	{
		if (rot * -1 >= dest_rot * -1)
			return (rot * -1);
		else 
			return (dest_rot * -1);
	}
}

int get_costs(t_list **lb)
{
	t_list *tmp;
	
	(*lb)->cost = optimise_rotations(*lb);
	tmp = (*lb)->next;
	while (tmp->start == false)
	{
		tmp->cost = optimise_rotations(tmp);
		tmp = tmp->next;
	}
}



