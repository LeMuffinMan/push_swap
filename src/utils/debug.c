#include "push_swap.h"
#include <stdio.h> // a virer

//a virer en fin

void print_candidate(t_list node)
{
    printf("\nCANDIDATE :\n");
    printf("i = %d\n", node.i);
    printf("dest = %d\n", node.dest);
    printf("rot = %d\n", node.rot);
    printf("dest_rot = %d\n\n", node.dest_rot);
}

void	print_lst(t_list *l)
{
	t_list	*ptr;
	int		i;

	i = 1;
	if (l == NULL)
	{
		printf("list is empty\n");
		return ;
	}
	ptr = l;
	printf("node #%d = %d | index = %d | rot = %d | pivot = %d | cost = %d | dest = %d | start = %d\n", ptr->pos, ptr->n, ptr->i, ptr->rot, ptr->pivot, ptr->cost, ptr->dest, ptr->start);
	ptr = ptr->next;
	while (ptr->start == false)
	{
		i++;
	printf("node #%d = %d | index = %d | rot = %d | pivot = %d | cost = %d | dest = %d\n", ptr->pos, ptr->n, ptr->i, ptr->rot, ptr->pivot, ptr->cost, ptr->dest);
		ptr = ptr->next;
	}
}

void	print_lst2(t_list *l)
{
	t_list	*ptr;
	int		i;

	i = 1;
	if (l == NULL)
	{
		printf("list is empty\n");
		return ;
	}
	ptr = l;
	printf("node #%d = %d | index = %d | rot = %d | pivot = %d | cost = %d | dest = %d | start = %d\n", ptr->pos, ptr->n, ptr->i, ptr->rot, ptr->pivot, ptr->cost, ptr->dest, ptr->start);
	ptr = ptr->next;
	while (ptr->start == false)
	{
		i++;
	printf("node #%d = %d | index = %d | rot = %d | pivot = %d | cost = %d | dest = %d\n", ptr->pos, ptr->n, ptr->i, ptr->rot, ptr->pivot, ptr->cost, ptr->dest);
		ptr = ptr->next;
	}
}
