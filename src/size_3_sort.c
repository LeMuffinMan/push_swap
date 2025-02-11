#include "push_swap.h"

static void one_operation_cases(t_list **la)
{
		if ((*la)->n > (*la)->next->n && (*la)->n < (*la)->next->next->n
			&& (*la)->next->n < (*la)->next->next->n) // 2 1 3
			sa(la);
		else if ((*la)->n < (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n > (*la)->n
			&& (*la)->next->n > (*la)->next->next->n) // 2 3 1
			rra(la);
		else if ((*la)->n > (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n < (*la)->n
			&& (*la)->next->n < (*la)->next->next->n) // 3 1 2
			ra(la);
}

//renomer : upt to 3 size sort
void	size_3_sort(t_list **la) // pour pile de 2 ou 3
{
	if (lst_size(*la) == 2) // si on a deux chiffres a trier
		sa(la);
	else if (lst_size(*la) == 3)
	{
		one_operation_cases(la);
		if ((*la)->n > (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n < (*la)->n
			&& (*la)->next->n > (*la)->next->next->n) // 3 2 1
		{
			ra(la);
			sa(la);
		}
		else if ((*la)->n < (*la)->next->n && (*la)->n < (*la)->next->next->n
			&& (*la)->next->n > (*la)->n
			&& (*la)->next->n > (*la)->next->next->n) // 1 3 2
		{
			sa(la);
			ra(la);
		}
	}
}


