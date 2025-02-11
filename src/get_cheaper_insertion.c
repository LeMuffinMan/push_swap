#include "push_swap.h"

int get_cheaper_insertion(t_list **l)
{
	int cheaper;
	t_list *tmp;
	int min_cost;
	
	min_cost = (*l)->cost;
	cheaper = (*l)->i;
	tmp = (*l)->next;
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
	return (0); // revoir ce return en cas d'aucune condition
}

void get_costs(t_list **lb)
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



