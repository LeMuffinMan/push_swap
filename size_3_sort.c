#include "push_swap.h"


//a reecrire

void	size_3_sort(t_list **la) // pour pile de 2 ou 3
								// lui passer *la ou **la ?
{
	if (lst_size(*la) == 2) // si on a deux chiffres a trier
	{
		sa(la);
	}
	else if (lst_size(*la) == 3)
	{
		if ((*la)->n > (*la)->next->n && (*la)->n < (*la)->next->next->n
			&& (*la)->next->n < (*la)->next->next->n) // 2 1 3
		{
			sa(la);
		}
		else if ((*la)->n > (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n < (*la)->n
			&& (*la)->next->n > (*la)->next->next->n) // 3 2 1
		{
			ra(la);
			sa(la);
		}
		else if ((*la)->n > (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n < (*la)->n
			&& (*la)->next->n < (*la)->next->next->n) // 3 1 2
		{
			ra(la);
		}
		else if ((*la)->n < (*la)->next->n && (*la)->n < (*la)->next->next->n
			&& (*la)->next->n > (*la)->n
			&& (*la)->next->n > (*la)->next->next->n) // 1 3 2
		{
			sa(la);
			ra(la);
		}
		else if ((*la)->n < (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n > (*la)->n
			&& (*la)->next->n > (*la)->next->next->n) // 2 3 1
		{
			rra(la);
		}
	}
}

// reecrire is sorted sur ce modele
void	inverted_size_3_sort(t_list **l)
{
	int	a;
	int	b;
	int	c;

	/* print_lst(*l); */
	a = (*l)->i;
	b = (*l)->next->i;
	c = (*l)->prev->i;
	if (lst_size(*l) == 2 && a < b)
		sb(l);
	else if (lst_size(*l) == 3)
	{
		if (a < b && b < c && b < c) // 1 2 3 -> sb + rrb
		{
			sb(l);
			rrb(l);
		}
		else if (a < b && a < c && b > c) // 1 3 2 -> rb
			rb(l);
		else if (a > b && a < c && b < c) // 2 1 3 -> rrb
			rrb(l);
		else if (a < b && a > c && b > c) // 2 3 1 -> sb
			sb(l);
		else if (a > b && a > c && b < c) // 3 1 2 -> sb + rb
		{
			sb(l);
			rb(l);
		}
	}
}

