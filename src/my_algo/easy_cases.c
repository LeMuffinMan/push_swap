#include "push_swap.h"

static void one_operation_cases(t_list **la)
{
		if ((*la)->n > (*la)->next->n && (*la)->n < (*la)->next->next->n
			&& (*la)->next->n < (*la)->next->next->n)
			sa(la);
		else if ((*la)->n < (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n > (*la)->n
			&& (*la)->next->n > (*la)->next->next->n)
			rra(la);
		else if ((*la)->n > (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n < (*la)->n
			&& (*la)->next->n < (*la)->next->next->n) 
		ra(la);
}

void	easy_cases(t_list **la) 
{
	if (lst_size(*la) == 2) 
		sa(la);
	else if (lst_size(*la) == 3)
	{
		one_operation_cases(la);
		if ((*la)->n > (*la)->next->n && (*la)->n > (*la)->next->next->n
			&& (*la)->next->n < (*la)->n
			&& (*la)->next->n > (*la)->next->next->n) 
		{
			ra(la);
			sa(la);
		}
		else if ((*la)->n < (*la)->next->n && (*la)->n < (*la)->next->next->n
			&& (*la)->next->n > (*la)->n
			&& (*la)->next->n > (*la)->next->next->n) 
		{
			sa(la);
			ra(la);
		}
	}
}


