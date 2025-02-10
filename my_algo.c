#include "push_swap.h"
#include <stdio.h>
#include <unistd.h>

//diviser partition stacks 
//recursive ?

//revoir le partitionnement et supprimer j si necessaire

//voir sur le vizualizer
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

int	partition_stacks(t_list **la, t_list **lb)
{
	t_list *tmp;
	int count;
	int size;
	int p;
	int j;

	p = PIVOT; // a opti
	j = 0;
	size = lst_size(*la);
	count = 0;
	tmp = *la;
	j = 0;
	while (lst_size(*la) > 3 && !is_A_setup(*la)) // opti a faire ici
	{
	/* printf("la :\n"); */
	/* print_lst2(*la); */
	/* printf("lb :\n"); */
	/* print_lst2(*lb); */
	/* sleep(1); */
		if (tmp->i == size - 1 || tmp->pivot > j)
			ra(la);
		else if (tmp->pivot <= j)
		{	
			/* if (j == p) // a deplacer ? */
			/* 	break ; */
			count++;
			if (count >= size / p)
			{
				j++;
				count = 0;
			}
			pb(la, lb);
			if ((*lb)->i <= size / 2)
			{
				if (tmp->next->i == size - 1 || tmp->next->pivot > j)
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
	/* printf("=========================================\n"); */
	/* printf("la :\n"); */
	/* print_lst2(*la); */
	/* printf("lb :\n"); */
	/* print_lst2(*lb); */

	//deplacer cette condition plus bas
	if (lst_size(*lb) > 1)	
		cheaper = get_cheaper_insertion(la, lb);
	else
		cheaper = (*lb)->i;
	//faire une fonction execute_insertion
	////diviser en bring_cheaper to top
	///bring dest top top
	get_cheaper_and_dest_to_top(la, lb, cheaper);
	/* do_rotates(la, lb, &move); */
	pa(la, lb);
	/* printf("la :\n"); */
	/* print_lst2(*la); */
	/* printf("lb :\n"); */
	/* print_lst2(*lb); */
	/* sleep(1); */
	return (0);
}

//recusrive ou while avec if de fin
int final_rotate(t_list **la)
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

