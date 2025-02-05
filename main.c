/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:49:41 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/31 14:16:40 by oelleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

// installer le vizuallizer pour tester
// adapter code au vizu
// implementer quick sort
// radix ?
//
////tester les ints min et les ints max TODO

/* The goal is to sort in ascending order numbers into stack a. */

// /!\ un seul arg part en vrille : un cas d'erreur e
// cas sur peu d'arguments : mois de 3 ca bug

// d'abord : verifier les doublons
// verifier si j'ai plus d'un element e
// hardcoder de 2 a 5 elements

void	homegrown_algo(t_list *la) // pour pile de 2 ou 3
								// lui passer *la ou **la ?
{
	if (lst_size(la) == 2) // si on a deux chiffres a trier
	{
		printf("sa\n");
		swap(&la);
	}
	else if (lst_size(la) == 3)
	{
		if (la->n > la->next->n && la->n < la->next->next->n
			&& la->next->n < la->next->next->n) // 2 1 3
		{
			printf("sa\n");
			swap(&la);
		}
		else if (la->n > la->next->n && la->n > la->next->next->n
			&& la->next->n < la->n && la->next->n > la->next->next->n) // 3 2 1
		{
			printf("ra\n");
			rotate(&la);
			printf("sa\n");
			swap(&la);
		}
		else if (la->n > la->next->n && la->n > la->next->next->n
			&& la->next->n < la->n && la->next->n < la->next->next->n) // 3 1 2
		{
			printf("ra\n");
			rotate(&la);
		}
		else if (la->n < la->next->n && la->n < la->next->next->n
			&& la->next->n > la->n && la->next->n > la->next->next->n) // 1 3 2
		{
			printf("sa\n");
			swap(&la);
			printf("ra\n");
			rotate(&la);
		}
		else if (la->n < la->next->n && la->n > la->next->next->n
			&& la->next->n > la->n && la->next->n > la->next->next->n) // 2 3 1
		{
			printf("rra\n");
			reverse_rotate(&la);
		}
	}
}

// revoir ma fonction is sorted !
int	is_desc_sorted(t_list *l)
{
	t_list	*tmp;
	int		n;

	if (l == NULL || l == l->next)
		return (0);
	tmp = l;
	n = tmp->n;
	tmp = tmp->next;
	while (tmp != l)
	{
		if (tmp->n > n)
			return (1);
		n = tmp->n;
		tmp = tmp->next;
	}
	return (0); // 0 = sorted
}

#include <unistd.h>

void	insertion_sort(t_list **la, t_list **lb)
{

	/* printf("------------ insertion sort ------------\n"); */
	while (*la != NULL) // tant que ma pile a n'est pas vide
	{
		if (lst_size(*lb) > 1 && (*la)->n < (*lb)->n && (*la)->n > (*lb)->prev->n) // si n < 1er et n > dernier : on cherche sa place
		{
    	t_list *tmp;

    	tmp = (*lb)->next;
			while ((*la)->n < tmp->n)
				tmp = tmp->next;

    	// Effectuer des rotations pour amener la bonne position en haut de lb
    	while (*lb != tmp)
    	{
    		printf("rb\n");
        rotate(lb); // On fait tourner jusqu'à la bonne position
      }
      	//
			push(lb, la);
			printf("pb\n");
			/* printf("\nlb :\n"); */
			/* print_lst(*lb); */
			/* printf("[is_desc_sorted(*lb) == %d]\n", is_desc_sorted(*lb)); */
			/* printf("\n"); */
			/*  */

      while ((*lb)->n < (*lb)->prev->n)
      	reverse_rotate(lb);
		}
		else 
		{
			push(lb, la); // on push le premier element dans b
			printf("pb\n");
			/* printf("\nlb :\n"); */
			/* print_lst(*lb); */
			/* printf("[is_desc_sorted(*lb) == %d]\n", is_desc_sorted(*lb)); */
			/* printf("\n"); */
			
		}		// a partir de deux elements on commence la tambouille
		if (lst_size(*lb) > 1)
		{
			// si le new est inferieur au dernier : on le met en dernier
			if ((*lb)->n < (*lb)->prev->n)
			{
				rotate(lb);
				printf("rb\n");
				/* printf("\nlb :\n"); */
				/* print_lst(*lb); */
				/* printf("\n"); */
				/* printf("[is_desc_sorted(*lb) == %d]\n", is_desc_sorted(*lb)); */
			}
			if ((*lb)->n < (*lb)->next->n)
			{
				swap(lb);
				printf("sb\n");
				/* printf("\nlb :\n"); */
				/* print_lst(*lb); */
				/* printf("\n"); */
			}
		}
	}
	while (*lb != NULL)
	{
		push(la, lb);
		printf("pa\n");
	}
}


void	swap_elements(int *tab, unsigned int p1, unsigned int p2)
{
	int tmp = tab[p1];
	tab[p1] = tab[p2];
	tab[p2] = tmp;
}

void	bubble_sort(int *tab, unsigned int size)
{
	unsigned int i = 0;
	unsigned int j = 0;

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

void	sort_int_tab(int *tab, unsigned int size)
{
	if (size <= 1)
		return ;
	bubble_sort(tab, size);
}
int	*lst_to_array(t_list **la, int size)
{
	int	*array;
	int	i;
	t_list *tmp;

	array = (int *)malloc(sizeof(int) * size); //revoir ca 
	if (!array)
		return (NULL);
	array[0] = (*la)->n;
	i = 1;
	tmp = (*la)->next;
	while (tmp->start == false)
	{
		array[i] = tmp->n;
		i++;
		tmp = tmp->next;
	}
	sort_int_tab(array, i);
	/* i = 0; */
	/* while (i < size) */
	/* { */
	/* 	printf("array[%d] = %d\n", i, array[i]); */
	/* 	i++; */
	/* } */
	return (array);
}

int is_lists_paritioned(t_list **la, t_list **lb, int median)
{
	t_list *tmp;

	/* if (!la || !lb) */
	/* 	return (1); */
	if ((*la && (*la)->n <= median) || (*lb && (*lb)->n > median))
		return (1);
	tmp = (*la)->next;
	while (tmp->start == false)
	{
		if (tmp->n <= median)
			return (1);
		tmp = tmp->next;
	}
	tmp = (*lb)->next;
	while (tmp->start == false)
	{
		if (tmp->n > median)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void partition_lists(t_list **la, t_list **lb, int median)
{
	if ((*la)->n <= median)
	{
		push(lb, la);
		printf("pb\n");
		/* printf("\nlb :\n"); */
		/* print_lst(*lb); */
		/* printf("[is_desc_sorted(*lb) == %d]\n", is_desc_sorted(*lb)); */
		/* printf("\n"); */
		/*  */

	}
	else 
	{
		rotate(la);
		printf("ra\n");
	}
}

int is_sorted_check(t_list *la)
{
	t_list *tmp;

	//securiser ?
	tmp = la;
	while (tmp->next != la)
	{
		if (tmp->n > tmp->next->n)
		{
			/* printf("list unsorted\n"); */
			return (1);
		}
		tmp = tmp->next;
	}
	/* printf("list sorted\n"); */
	return (0);
}

int is_B_ready(t_list *lb)
{
	t_list *tmp;
	t_list *max_node;
	int max;

	max = -2147483648;
	if (lb->n > max)
	{
		max = lb->n;
		max_node = lb;
	}
	tmp = lb->next;
	while (tmp->start == false)
	{
		if (tmp->n > max)
		{
			max = tmp->n;
			max_node = tmp;
		}
		tmp = tmp->next;
	}
	tmp = max_node;
	if (tmp->n < tmp->next->n)
		return (1);
	while (tmp->n > tmp->next->n)
		tmp = tmp->next;
	if (tmp->next != max_node)
		return (1);
	return (0);
}

int is_A_ready(t_list *la)
{
	t_list *tmp;
	t_list *min_node;
	int min;

	min = 2147483647;
	if (la->n < min)
	{
		min = la->n;
		min_node = la;
	}
	tmp = la->next;
	while (tmp->start == false)
	{
		if (tmp->n < min)
		{
			min = tmp->n;
			min_node = tmp;
		}
		tmp = tmp->next;
	}
	tmp = min_node;
	if (tmp->n > tmp->next->n)
		return (1);
	while (tmp->n < tmp->next->n)
		tmp = tmp->next;
	if (tmp->next != min_node)
		return (1);
	return (0);
}

int is_ready_to_push(t_list *lb)
{
	t_list *tmp;
	t_list max_node;
}


/* void sort(t_list **la, t_list **lb) */
/* { */
/* 	while (is_B_ready(lb)) */
/* 	{ */
/* 		if ((*lb)->n < (*lb)->next->n) */
/* 		{ */
/* 			if (is_A_ready(la) && (*la)->n > (*la)->next->n) */
/* 			{ */
/* 				swap_both(la, lb); */
/* 				printf("ss\n"); */
/* 			} */
/* 			else  */
/* 		{ */
/**/
/* 			} */
/* 		} */
/* 	} */
/* } */

void get_min_max(int *min, int *max, t_list *la, t_list *lb)
{
	t_list *tmp;
	
	//securiser ! 
	*min = la->n;
	tmp = la->next;
	while (tmp->start == false)
	{
		/* printf("tmp->start = %d\n", tmp->start); */
		if (tmp->n < *min)
			*min = tmp->n;
		tmp = tmp->next;
	}
	*max = lb->n;
	tmp = lb->next;
	while (tmp != lb)
	{
		if (tmp->n > *max)
			*max = tmp->n;
		tmp = tmp->next;
	}
}

int get_start_dir(t_list *l, int m)
{
	t_list *tmp;
	int i;

	i = 0;
	tmp = l->next;
	while (tmp != l)
	{
		i++;
		tmp = tmp->next;
	}
	if (i == 0)
		return (0); // on peut savoir si on est pret a push ici
	if (i > lst_size(l) / 2)
		return (-1); //si i est plus grand que sixe / 2 : je veux reverserotate
	else 
		return (1);
}

void sort(t_list **la, t_list **lb, int min, int max)
{

	/* printf("is_B_ready = %d | is_A_ready = %d\n", is_A_ready(*la), is_B_ready(*lb)); */
	while (is_A_ready(*la) || is_B_ready(*lb)) //tant que l'ordre n'est pas bon
	{
		if (is_A_ready(*la))
			printf("stack A not ready\n");
		else 
			printf("Stack A ready\n");
		if (is_B_ready(*lb))
			printf("stack B not ready\n");
		else 
			printf("Stack B ready\n");
		printf("la->n = %d | la->next->n = %d\n", (*la)->n, (*la)->next->n);
		if (is_B_ready(*lb) && (*lb)->n < (*lb)->next->n && (*lb)->next->n != max) //Si on doit trier B
		{
			if (is_A_ready(*la) && (*la)->n > (*la)->next->n && (*la)->next->n != min) // ET A 
			{
				swap_both(la, lb);
				printf("ss\n");
			}
			else //si Seulement B
			{
				swap(lb);
				printf("sb\n");
			}
		}
		else if (is_A_ready(*la) && (*la)->n > (*la)->next->n && (*la)->next->n != min) //si Seuelent A
		{
			swap(la);
			printf("sa\n");
		}
		if (is_A_ready(*la) && is_B_ready(*lb))
		{
			rotate_both(la, lb); // opti ici
			printf("rr\n");
		}
		else if (!is_A_ready(*la))
		{
			if (get_start_dir(*lb, max) > 0)
			{
				rotate_both(la, lb);
				printf("rr\n");
			}
			else
			{
				rotate(lb);
				printf("rb\n");
			}
		}
		else if (!is_B_ready(*lb))
		{
			if (get_start_dir(*lb, max) > 0)
			{
				rotate_both(la, lb);
				printf("rr\n");
			}
			else
			{
				rotate(la);
				printf("ra\n");
			}
		}
		printf("\nla :\n");
		print_lst(*la);
		printf("lb :\n");
		print_lst(*lb);
		printf("\n");
		sleep (1);
	}
	if (!(is_A_ready(*la)))
		printf("stack A ready : need to rotate ?\n");
	if (!(is_B_ready(*lb)))
		printf("stack B ready : need to rotate ?\n");
	while ((*la)->n != min || (*lb)->n != max) //tant qu'on n'est pas aligne
	{
		/* printf("rotating_stacks to final push\n"); */
		if ((*la)->n == min)
		{
			if (get_start_dir(*lb, max) > 0)
			{
				rotate(lb);
				printf("rb\n");
			}
			else if (get_start_dir(*lb, max < 0))
			{
				reverse_rotate(lb);
				printf("rrb\n");
			}
		}
		else if ((*lb)->n == max)
		{
			if (get_start_dir(*la, min) > 0)
			{
				rotate(la);
				printf("ra\n");
			}
			else if (get_start_dir(*la, min < 0))
			{
			reverse_rotate(la);
			printf("rra\n");
			}
		}
		else 
		{
			if (get_start_dir(*la, min) > 0 && get_start_dir(*lb, max) > 0)
			{
				rotate_both(la, lb);
				printf("rr\n");
			}
			else if (get_start_dir(*la, min) < 0 && get_start_dir(*lb, max) < 0)
			{
				reverse_rotate_both(la, lb);
				printf("rrr\n");
			}
		}
		printf("\nla :\n");
		print_lst(*la);
		printf("lb :\n");
		print_lst(*lb);
		printf("\n");
		sleep (1);
	}
	while (*lb) //tant b n'est pas vide 
	{
		push(la, lb);
		printf("pa\n");
	}
}

/* void sort(t_list **la, t_list **lb) */
/* { */
/* 		if (is_sorted_check(*la) && (*la)->n > (*la)->next->n) //il faut swaper a */
/* 		{ */
/* 			if ((*lb)->n < (*lb)->next->n) //il faut swaper b */
/* 			{ */
/* 				swap_both(la, lb); */
/* 				printf("ss\n"); */
/* 			} */
/* 			else  */
/* 			{ */
/* 				swap(la); */
/* 				printf("sa\n"); */
/* 			} */
/* 		} */
/* 		else if (is_desc_sorted(*lb) && (*lb)->n < (*lb)->next->n) */
/* 		{ */
/* 			swap(lb); */
/* 			printf("sb\n"); */
/* 		} */
/* 		else if (is_sorted_check(*la) && is_desc_sorted(*lb))  */
/* 		{ */
/* 			reverse_rotate_both(la, lb); */
/* 			printf("rrr\n"); */
/* 		} */
/* 		else if (is_sorted_check(*la)) */
/* 		{ */
/* 			reverse_rotate(la); */
/* 			printf("rra\n"); */
/* 		} */
/* 		else if (is_desc_sorted(*lb)) */
/* 		{ */
/* 			if ((*lb)->n > (*la)->next->n) */
/* 			{ */
/* 				reverse_rotate(lb); */
/* 				printf("rrb\n"); */
/* 			} */
/* 			else */
/* 			{ */
/* 				rotate(lb); */
/* 				printf("rb\n"); */
/* 			} */
/* 		} */
/* 		printf("la :\n"); */
/* 		print_lst(*la); */
/* 		printf("lb :\n"); */
/* 		print_lst(*lb); */
/* 		if (is_ready_to_push(lb)) */
/* 			printf("sorting lb\n"); */
/* 	else  */
/* 		printf("rotate to push LB !!!\n"); */
/* 		if (!is_sorted_check(*la) && !is_desc_sorted(*lb)) */
/* 			printf("lists SORTED !!\n"); */
/* 		else if (!is_sorted_check(*la)) */
/* 			printf("la sorted !!\n"); */
/* 		else if (!is_desc_sorted(*lb)) */
/* 			printf("lb sorted !!\n"); */
/* 	sleep (1); */
/* } */

int partition_setup(t_list **la, t_list **lb)
{
	int median;
	int size;
	int *array;
	int min;
	int max;

	size = lst_size(*la);
	array = lst_to_array(la, size);
	//array to free !
	median = array[size/2];
	free(array);
	/* printf("median = %d\n", median); */
	while (is_lists_paritioned(la, lb, median))
		partition_lists(la, lb, median);
	/* printf("partition done\n"); */
		/* printf("la :\n"); */
		/* print_lst(*la); */
		/* printf("lb :\n"); */
		/* print_lst(*lb); */
		get_min_max(&min, &max, *la, *lb);
	while (is_sorted_check(*la) || is_desc_sorted(*lb)) // revoir cette condition
		sort(la, lb, min, max);
}


void interstor(t_list **la, t_list **lb)
{
	//fin smalest(la)
	//
}

int	main(int ac, char **av)
{
	t_list	*la;

	// l'idee est de garder ce pointeur vers le 1er element de ma liste
	la = NULL;
	t_list *lb = NULL; // pb avec ma stack b au demarrage
	if (ac <= 1)       // ARG "1 5 -65" comme seul input ?
	{
		printf("ERROR : not enough arguments\n");
		// error a afficher dans certains cas seulement
		exit(1);
	}
	init_stack(&la, av);
	/* printf("list_size(*lb) = %d\n", lst_size(lb)); */
	/* printf("==========================\nstack initialized :\n"); */
	/* print_lst(la); */
	/* printf("==========================\n\n"); */

	partition_setup(&la, &lb);
	
	/* printf("la :\n"); */
	/* print_lst(la); */
	/* printf("lb :\n"); */
	/* print_lst(lb); */
	/* if (lst_size(la) <= 3) */
	/* 	homegrown_algo(la); */
	/* else */
	/* 	insertion_sort(&la, &lb); */
	printf("\n========================\n");
	print_lst(la);
	print_lst(lb);
	is_sorted_check(la);
	free_list(&la);
	free_list(&lb);
	return (0);
}
// dans fractol je declare une struct : ici je declare un pointeur sur la struct :
// C'EST POUR CA QUE envoyer &l ici peut etre recupere en **lst
/* t_list *a = NULL; */
/* t_list *b = NULL; */
/* t_list *ptr = NULL; */
/**/
/* (void)ptr; */
/* add_front(&a, 5); */
/* add_front(&a, 1); */
/*  printf("\n"); */
/* add_front(&b, 2); */
/* add_front(&b, 8); */
/*  add_back(&a, 1);  */
/* print_lst(a); */
/* printf("\n"); */
/* print_lst(b); */
/* ptr = lst_last(a); */
/* printf("\nlast = %d\n\n", ptr->n); */
/* print_rev_lst(a); */
/* printf("\n"); */
/* print_rev_lst(b); */
/**/
/* (*lst) */
/* *lst->next */
/**/
/* (**lst) */
/* (*lst)->next */
