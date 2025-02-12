#include "push_swap.h"
#include <stdlib.h>

//libft ???

void	free_list(t_list **l)
{
	t_list	*tmp;
	t_list	*next_node;

	tmp = *l;
	if (!*l)
		return ;
	(*l)->prev->next = NULL;
	while (tmp)
	{
		next_node = tmp->next;
		free(tmp);
		tmp = next_node;
	}
	*l = NULL;
}

//a returiliser pour pa pb ?
static void add_first_node(t_list **lst, t_list *new, int n)
{
		*lst = new;
		new->prev = new;
		new->n = n;
		new->start = true;
		new->next = new;
}

//libft a integrer !!
void	add_back(t_list **lst, int n)
{
	t_list	*ptr;
	t_list	*new;

	new = NULL;
	new = malloc(sizeof(t_list));
	/* if (new == NULL) */
	/*   lst_clear(*lst); */
	if (*lst == NULL)
		add_first_node(lst, new, n);
	else
	{
		ptr = (*lst)->prev; // on est sur le dernier de la liste
		ptr->next = new; //next etait sur la tete : on le passe sur le nouveau node 
		(*lst)->prev = new;
		new->prev = ptr; //le precedent du new, est l'ancien dernier 
		new->next = *lst;
		new->n = n;
		new->start = false;
	}  
}

int lst_size(t_list *l)
{
	t_list *ptr;
	int i;

	if (l == NULL)
		return (0);
	ptr = l;
	if (ptr->next == ptr)
		return (1);
	i = 1;
	ptr = ptr->next;
	while (ptr->start != true)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

//renvoyer un booleen
int is_sorted_check(t_list *la)
{
	t_list *tmp;

	tmp = la;
	while (tmp->n < tmp->next->n)
		tmp = tmp->next;
	if (tmp->next != la)
		return (0);
	return (1);
}

