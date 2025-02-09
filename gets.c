#include "push_swap.h"

int get_cheaper_insertion(t_list **la, t_list **lb)
{
	int cheaper;
	t_list *tmp;
	int min_cost;
	
	/* init_cheaper(&cheaper); */

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
	/* cheaper = optimise_best_move(cheaper, *la, *lb); */
	/* print_move(cheaper); */
	return (cheaper);	
}

//renommer rotate stacks ranger avec execute_insertion
//deux sous fonctions : get cheaper to top B + get dest to top A
//subdiviser pour les rot / rev rot
int get_cheaper_and_dest_to_top(t_list **la, t_list **lb, int cheaper)
{
	t_list *candidate;
	t_list *dest;

	if ((*lb)->i == cheaper)
		candidate = *lb;
	else
	{
		candidate = (*lb)->next;
		while (!candidate->start)
		{
			if (candidate->i == cheaper)
				break ;
			candidate = candidate->next;
		}
	}
	if ((*la)->i == candidate->dest)
		dest = *la;
	else
	{
		dest = (*la)->next;
		while (!dest->start)
		{
			if (candidate->dest == dest->i)
				break ;
			dest = dest->next;
		}
	}
	//on a nos deux nodes a faire remonter
	/* printf("getting %d and %d up\n", candidate->i, dest->i); */
	while (candidate->rot > 0 && dest->rot > 0)
	{
		rr(la, lb);
		candidate->rot--;
		dest->rot--;
	}
	while (candidate->rot < 0 && dest->rot < 0)
	{
		rrr(la, lb);
		candidate->rot++;
		dest->rot++;
	}
	while (candidate->rot > 0)
	{
		rb(lb);
		candidate->rot--;
	}
	while (candidate->rot < 0)
	{
		rrb(lb);
		candidate->rot++;
	}
	while (dest->rot > 0)
	{
		ra(la);
		dest->rot--;
	}
	while (dest->rot < 0)
	{
		rra(la);
		dest->rot++;
	}

}

//faire une recursive ? 
//ou un while (1) avec un break sur == start true en fin de while ?
void	get_index(t_list **l, int *array)
{
	//si size < p ca peut poser soucis
	int		i;
	int 	p;
	t_list	*tmp;
	int		size;

	p = PIVOT; // a opti
	size = lst_size(*l);
	i = 0;
	tmp = *l;
	while (i < size)
	// si je met juste array[i] : si il vaut 0 la boucle s'arrete
	{
		if (tmp->n == array[i])
		{
			tmp->i = i;
			tmp->pivot = i / (size / p); // Calcul du pivot
			break ;
		}
		i++;
	}
	i = 0;
	tmp = (*l)->next;
	while (tmp->start == false)
	{
		i = 0;
		while (i < size)
		{
			if (tmp->n == array[i])
			{
				tmp->i = i;
				tmp->pivot = i / (size / p); // Calcul du pivot
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}


int get_costs(t_list **lb)
{
/* le coup est le nombre de rot de tmp et de sa cible */ 
	t_list *tmp;
	
	//revoir les couts : + et - a repenser ?
	(*lb)->cost = optimise_rotations(*lb);
	/* printf("i = %d | cost = %d\n", (*lb)->i, (*lb)->cost); */
	tmp = (*lb)->next;
	while (tmp->start == false)
	{
		tmp->cost = optimise_rotations(tmp);
	/* printf("i = %d | cost = %d\n", tmp->i, tmp->cost); */
		tmp = tmp->next;
	}
}


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

//recusrive ou while avec if de fin
int get_dests(t_list **la, t_list **lb)
{
	t_list *tmp_A;
	t_list *tmp_B;
	int max_index;
	int min_index;

	max_index = get_max_index(la);
	min_index = get_min_index(la);
	/* printf("max = %d | min = %d\n", max_index, min_index); */
	(*lb)->dest = max_index;
	if ((*lb)->i > max_index)
		(*lb)->dest = min_index;
	else if ((*la)->i > (*lb)->i && (*la)->i < (*lb)->dest)
		(*lb)->dest = (*la)->i;
	tmp_A = (*la)->next;
	while (tmp_A->start == false && (*lb)->dest != min_index)
	{
		if (tmp_A->i > (*lb)->i && tmp_A->i < (*lb)->dest)
			(*lb)->dest = tmp_A->i;
		tmp_A = tmp_A->next;
	}
	/* printf("i = %d | dest = %d\n", (*lb)->i, (*lb)->dest); */
	tmp_B = (*lb)->next;
	while (tmp_B->start == false)
	{
		tmp_B->dest = max_index;
		if (tmp_B->i > max_index)
			tmp_B->dest = min_index;
		else if ((*la)->i > tmp_B->i && (*la)->i < tmp_B->dest)
			tmp_B->dest = (*la)->i;
		tmp_A = (*la)->next;
		while (tmp_A->start == false && tmp_B->dest != min_index)
		{
			if (tmp_A->i > tmp_B->i && tmp_A->i < tmp_B->dest)
				tmp_B->dest = tmp_A->i;
			tmp_A = tmp_A->next;
		}
		/* printf("i = %d | dest = %d\n", tmp_B->i, tmp_B->dest); */
		tmp_B = tmp_B->next;
	}
}

//recusrive ou while avec if de fin
int get_dest_rots(t_list **la, t_list **lb)
{
	t_list *tmp_A;
	t_list *tmp_B;
	int rot;
	int dest;

	dest = (*lb)->dest;
	if ((*la)->i == dest)
		(*lb)->dest_rot = (*la)->rot;
	else
	{
		tmp_A = (*la)->next;
		while (tmp_A->start == false)
		{
			if (tmp_A->i == dest)
				(*lb)->dest_rot = tmp_A->rot;
			tmp_A = tmp_A->next;
		}
	}
	tmp_B = (*lb)->next;
	while (tmp_B->start == false)
	{
		dest = tmp_B->dest;
		if ((*la)->i == dest)
			tmp_B->dest_rot = (*la)->rot;
		else
		{
			tmp_A = (*la)->next;
			while (tmp_A->start == false)
			{
				if (tmp_A->i == dest)
					tmp_B->dest_rot = tmp_A->rot;
				tmp_A = tmp_A->next;
			}
		}
		tmp_B = tmp_B->next;
	}
	
}


int get_rots(t_list **l)
{
	t_list *tmp;
	int rot;
	
	(*l)->rot = 0;
	tmp = (*l)->next;
	rot = 1;
	while (tmp->start == false)
	{
		if (rot > lst_size(*l) / 2)
			rot = (lst_size(*l) - rot) * -1; 
		tmp->rot = rot;
		rot++;
		tmp = tmp->next;
	}
}
