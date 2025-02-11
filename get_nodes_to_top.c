#include "push_swap.h"

static void get_node_by_index(t_list **l, int index, t_list **node)
{
	if ((*l)->i == index)
		(*node) = *l;
	else
	{
		(*node) = (*l)->next;
		while (!(*node)->start)
		{
			if ((*node)->i == index)
				break ;
			*node = (*node)->next;
		}
	}
}


static void do_combine_rotates(t_list **la, t_list **lb, t_list **candidate, t_list **dest)
{
while ((*candidate)->rot > 0 && (*dest)->rot > 0)
	{
		rr(la, lb);
		(*candidate)->rot--;
		(*dest)->rot--;
	}
	while ((*candidate)->rot < 0 && (*dest)->rot < 0)
	{
		rrr(la, lb);
		(*candidate)->rot++;
		(*dest)->rot++;
	}
}


static void do_single_rotates(t_list **la, t_list **lb, t_list **candidate, t_list **dest)
{
	while ((*candidate)->rot > 0)
	{
		rb(lb);
		(*candidate)->rot--;
	}
	while ((*candidate)->rot < 0)
	{
		rrb(lb);
		(*candidate)->rot++;
	}
	while ((*dest)->rot > 0)
	{
		ra(la);
		(*dest)->rot--;
	}
	while ((*dest)->rot < 0)
	{
		rra(la);
		(*dest)->rot++;
	}
}

void get_cheaper_and_dest_to_top(t_list **la, t_list **lb, int cheaper)
{
	t_list *candidate;
	t_list *dest;

	get_node_by_index(lb, cheaper, &candidate);
	get_node_by_index(la, candidate->dest, &dest);
	do_combine_rotates(la, lb, &candidate, &dest);
	do_single_rotates(la, lb, &candidate, &dest);
}
