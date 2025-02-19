/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:54:46 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/15 17:35:04 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define TRUE 1
# define FALSE 0

typedef char		t_bool;

typedef struct s_stack
{
	struct s_stack	*prev;
	t_bool			start;
	int				n;
	int				i;
	int				pos;
	int				rot;
	int				cost;
	int				dest;
	int				dest_rot;
	struct s_stack	*next;
}					t_stack;

// my_algo
// easy_cases.c
void				easy_cases(t_stack **la);
// get_cheaper_insertion.c
void				get_costs(t_stack **lb);
int					get_cheaper_insertion(t_stack **l);
int					optimise_rotations(t_stack *node);
// get_nodes_to_top.c
void				get_nodes_to_top(t_stack **la, t_stack **lb, int cheaper);
// my_algo.c
void				partition_stacks(t_stack **la, t_stack **lb, int median,
						int size);
int					insert_cheaper(t_stack **la, t_stack **lb);
void				final_rotate(t_stack **la);
int					my_algo(t_stack **la, t_stack **lb, int size, int median);

// update_list_infos.c
void				get_index(t_stack **l, int *array);
void				get_dests(t_stack **la, t_stack **lb, int max_index,
						int min_index);
void				get_dest_rots(t_stack **la, t_stack **lb);
void				get_rots(t_stack **l);
int					get_position(t_stack **l);

// ops
// push on stack.c
void				pa(t_stack **la, t_stack **lb);
void				pb(t_stack **lb, t_stack **la);
// reverse_rotations.c
void				rra(t_stack **l);
void				rrb(t_stack **l);
void				rrr(t_stack **la, t_stack **lb);
// rotations.c
void				ra(t_stack **l);
void				rb(t_stack **l);
void				rr(t_stack **la, t_stack **lb);
// swap.c
void				sa(t_stack **l);
void				sb(t_stack **l);
void				ss(t_stack **la, t_stack **lb);
// ops_utils.c
void				stack_empty_case(t_stack **l, t_stack **tmp);
void				take_out_stack_top(t_stack **la, t_stack **lb,
						t_stack **node);
void				stack_one_node_case(t_stack **l, t_stack **tmp);
void				plug_on_stack(t_stack **l, t_stack **tmp);

// utils
// array_utils.c
int					*lst_to_array(t_stack **la, int size);
// get_min_max_index.c
int					get_min_index(t_stack **l);
int					get_max_index(t_stack **l);
// list_utils.c
void				free_list(t_stack **l);
void				add_back(t_stack **lst, int n);
int					lst_size(t_stack *l);
int					is_sorted_check(t_stack *la);
// utils.c
int					is_digits_or_sign(char *s);
int					ft_atoi_limits_check(const char *nptr, t_stack *l);

// init.c
int					init_stack(t_stack **l, int ac, char **av);
int					invalid_input(t_stack *l, int *array, char **s);
int					init_step_2(t_stack **l);

#endif
