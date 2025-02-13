#include "push_swap.h"
//header a part ?

//attend les moves en input
int get_ops(t_list **la, t_list **lb)
{
  char *op;

  //STDIN_FILENO // 0 ? revoir fds !
  op = get_next_line(0);
	while (op != NULL)
	{
		if (!check_op(op, la, lb))
		{
			get_next_line(0);
			return ;
		}
		free(op);
		op = get_next_line(0);
	}
	free(op);
}

int execute_push(char *op, t_list **la, t_list **lb)
{
  if (strncmp(op,  "pa\n", 3))
    pa(la, lb);
  else if (strncmp(op,  "pb\n", 3))
    pb(la, lb);
  else
    return(1);
  return (0);
}
int execute_rotations(char *op, t_list **la, t_list **lb)
{
  if (strncmp(op,  "ra\n", 3)) //revoir les params
    ra(la);
  else if (strncmp(op,  "rb\n", 3))
    rb(lb);
  else if (strncmp(op,  "rr\n", 3))
    rr(la, lb);
  else if (strncmp(op,  "rra\n", 4)) //revoir les params
    rra(la);
  else if (strncmp(op,  "rrb\n", 4))
    rrb(lb);
  else if (strncmp(op,  "rrr\n", 4))
    rrr(la, lb);
  else 
    return (1);
  return (0);
}

int execute_swap(char *op, t_list **la, t_list **lb)
{
  if (strncmp(op,  "sa\n", 3))
    sa(la);
  else if (strncmp(op,  "sb\n", 3))
    sb(lb);
  else if (strncmp(op,  "ss\n", 3))
    ss(la, lb);
  else
    return(1);
  return (0);
}

  //les executes un par un
  //securiser les ss / rr /rrr
int execute_ops(char *op, t_list **la, t_list **lb)
{
  if (!execute_rotations(op, la, lb) && execute_swap(op, la, lb) && execute_push(op, la, lb))
    return (1); //en cas d'erreur, il faut tout free !
  else
    return (0);
}
// execute_ops.c

// imp gnl
// imp libft
// write / printf ?
// booleens
// revoir le free tout si error
// revoir les tests a faire sur le checker
// securiser ops
//
int main (char **ac, int av)
{
	t_list	*la;
	t_list *lb;
	
	la = NULL;
 	lb = NULL; 

	if (ac <= 1)  
		exit (1);
	init_stack(&la, ac, av);

  get_ops(la, lb);

  if (is_sorted_check(la) && lb == NULL)
    printf("OK\n");
  else
    printf("KO\n");

	free_list(&la);
	free_list(&lb);
	return (0);
}
