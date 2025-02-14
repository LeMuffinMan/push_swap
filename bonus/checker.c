/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:11:56 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/14 12:30:00 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "checker.h"
#include "../libft/include/libft.h"
#include <limits.h>
//header a part ?

static void	swap_elements(int *tab, unsigned int p1, unsigned int p2)
{
	int	tmp;

	tmp = tab[p1];
	tab[p1] = tab[p2];
	tab[p2] = tmp;
}

static void	bubble_sort(int *tab, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - 1)
		{
			if (tab[j] > tab[j + 1])
				swap_elements(tab, j, j + 1);
			j++;
		}
		i++;
	}
}

static void	sort_int_tab(int *tab, unsigned int size)
{
	if (size <= 1)
		return ;
	bubble_sort(tab, size);
}

int	*lst_to_array(t_stack **la, int size)
{
	int		*array;
	int		i;
	t_stack	*tmp;

	array = malloc(sizeof(int) * size);
	if (!array)
	{
		free_list(la);
		return (NULL);
	}
	array[0] = (*la)->n;
	i = 1;
	tmp = (*la)->next;
	while (!tmp->start)
	{
		array[i] = tmp->n;
		i++;
		tmp = tmp->next;
	}
	sort_int_tab(array, i);
	return (array);
}

int	is_digits_or_sign(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] != '-' && s[i] != '+' && (s[i] > '9' || s[i] < '0'))
			return (1);
		i++;
	}
	return (0);
}

static void	add_first_node(t_stack **lst, t_stack *new, int n)
{
	*lst = new;
	new->prev = new;
	new->n = n;
	new->start = TRUE;
	new->next = new;
}

// libft a integrer !!
void	add_back(t_stack **lst, int n)
{
	t_stack	*ptr;
	t_stack	*new;

	//fuites ici si le malloc foire !
	new = malloc(sizeof(t_stack));
	if (new == NULL)
	{
		//free les deux ? quoi d'autre ?
	  free_list(lst);
	  exit (1);
	}
	if (*lst == NULL)
		add_first_node(lst, new, n);
	else
	{
		ptr = (*lst)->prev; 
		ptr->next = new;   
		(*lst)->prev = new;
		new->prev = ptr; 
		new->next = *lst;
		new->n = n;
		new->start = FALSE;
	}
}

int	lst_size(t_stack *l)
{
	t_stack	*ptr;
	int		i;

	if (l == NULL)
		return (0);
	ptr = l;
	if (ptr->next == ptr)
		return (1);
	i = 1;
	ptr = ptr->next;
	while (ptr->start != TRUE)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

int skip_spaces(const char *nptr)
{
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	return (0);
}

int	ft_atoi_limits_check(const char *nptr, t_stack *l)
{
	char			sign;
	long long int	n;

	n = 0;
	sign = ' ';
	skip_spaces(nptr);
	if (*nptr == '-' || *nptr == '+')
	{
		sign = *nptr;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		n += *nptr - '0';
		nptr++;
		if (*nptr >= '0' && *nptr <= '9')
			n *= 10;
	}
	if (sign == '-')
		n *= -1;
	if (n > 2147483647 || n < -2147483648)
		invalid_input(l, NULL, NULL);
	return (n);
}

int	invalid_input(t_stack *l, int *array, char **s)
{
	if (s)
		ft_free(s);
	if (array)
		free(array);
	if (l)
		free(l);
	write(2, "Error\n", 6);
	exit(1);
}

static t_stack	*fill_list(char **splitted)
{
	t_stack	*l;
	int		i;
	int		n;
	int		size;
	int		*array;

	l = NULL;
	i = 0;
	while (splitted[i])
	{
		if (is_digits_or_sign(splitted[i]))
			invalid_input(l, NULL, NULL);
		n = ft_atoi_limits_check(splitted[i], l);
		add_back(&l, n);
		i++;
	}
	size = lst_size(l);
	array = lst_to_array(&l, size);
	free(array);
	return (l);
}

static int	duplicate_checker(t_stack *l)
{
	t_stack	*n1;
	t_stack	*n2;

	n1 = l;
	n2 = l->next;
	while (1)
	{
		while (1)
		{
			if (n2->n == n1->n && n1 != n2)
				return (1);
			n2 = n2->next;
			if (n2->start)
				break ;
		}
		n1 = n1->next;
		if (n1->start)
			break ;
	}
	return (0);
}

int	init_stack(t_stack **l, int ac, char **av)
{
	char	**splitted;

	if (ac == 1 || !av[1][0])
		exit(1);
	else if (ac == 2)
	{
		splitted = ft_split(av[1], ' ');
		if (splitted[1] == NULL)
			invalid_input(NULL, NULL, splitted);
		*l = fill_list(splitted);
		ft_free(splitted);
		if (duplicate_checker(*l))
			invalid_input(*l, NULL, NULL);
	}
	else if (ac > 2)
	{
		av++;
		*l = fill_list(av);
		if (duplicate_checker(*l))
			invalid_input(*l, NULL, NULL);
	}
	return (0);
}

void	free_list(t_stack **l)
{
	t_stack	*tmp;
	t_stack	*next_node;

	if (!l || !*l)
		return ;
	tmp = *l;
	(*l)->prev->next = NULL;
	while (tmp)
	{
		next_node = tmp->next;
		free(tmp);
		tmp = next_node;
	}
	*l = NULL;
}

int	is_sorted_check(t_stack *la)
{
	t_stack	*tmp;

	if (!la)
		return (0);
	tmp = la;
	while (tmp->n < tmp->next->n)
		tmp = tmp->next;
	if (tmp->next != la)
		return (0);
	return (1);
}

int execute_push(char *op, t_stack **la, t_stack **lb)
{
  if (!ft_strncmp(op,  "pa\n", 3))
    push(la, lb);
  else if (!ft_strncmp(op,  "pb\n", 3))
    push(lb, la);
  else
    return(1);
  return (0);
}
int execute_rotations(char *op, t_stack **la, t_stack **lb)
{
  if (!ft_strncmp(op,  "ra\n", 3)) //revoir les params
    ra(la);
  else if (!ft_strncmp(op,  "rb\n", 3))
    rb(lb);
  else if (!ft_strncmp(op,  "rr\n", 3))
    rr(la, lb);
  else if (!ft_strncmp(op,  "rra\n", 4)) //revoir les params
    rra(la);
  else if (!ft_strncmp(op,  "rrb\n", 4))
    rrb(lb);
  else if (!ft_strncmp(op,  "rrr\n", 4))
    rrr(la, lb);
  else 
    return (1);
  return (0);
}

int execute_swap(char *op, t_stack **la, t_stack **lb)
{
  if (!ft_strncmp(op,  "sa\n", 3))
    sa(la);
  else if (!ft_strncmp(op,  "sb\n", 3))
    sb(lb);
  else if (!ft_strncmp(op,  "ss\n", 3))
    ss(la, lb);
  else
    return(1);
  return (0);
}

  //les executes un par un
  //securiser les ss / rr /rrr
int execute_ops(char *op, t_stack **la, t_stack **lb)
{
  if (execute_rotations(op, la, lb))
  {
  	if (execute_swap(op, la, lb))
  	{
  		if (execute_push(op, la, lb))
  			return (1);
  			//en cas d'erreur il faut tout free
  	}
  }
  return (0);
}
// execute_ops.c
// write / printf ?
// revoir le free tout si error
// revoir les tests a faire sur le checker
// securiser ops
// fuiiiiites
//
//

//attend les moves en input
int get_ops(t_stack **la, t_stack **lb)
{
  char *op;

  //STDIN_FILENO // 0 ? revoir fds !
  op = get_next_line(0);
	while (op != NULL)
	{
		if (execute_ops(op, la, lb))
		{
			write(2, "Error\n", 6);
			free(op);
			return (1);
		}
		free(op);
		op = get_next_line(0);
	}
	free(op);
	return(0);
}

int main (int ac, char **av)
{
	t_stack	*la;
	t_stack *lb;
	
	la = NULL;
 	lb = NULL; 

	if (ac <= 1)  
		exit (1);
	init_stack(&la, ac, av);
  if (get_ops(&la, &lb))
  {
		free_list(&la);
		free_list(&lb);
  	exit(1);
  }
  if (is_sorted_check(la) && lb == NULL)
    write(1, "OK\n", 3);
  else
    write(1, "KO\n", 3);
	free_list(&la);
	free_list(&lb);
	return (0);
}
