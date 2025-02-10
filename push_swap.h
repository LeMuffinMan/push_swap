/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:54:46 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/30 14:15:31 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP
# define PUSH_SWAP

#include <stdbool.h>
#include <stddef.h>


#define PIVOT 1

typedef struct s_list // s_list / t_list ?
{
  struct s_list *prev;
  bool          start; // IL FAUT DEFINE LE BOOL ?
  int           n;
  int           i;
  int pos; 
  int rot; // positive ou negative : 
  int cost;
  int pivot;
  int dest;
  int dest_rot;
  struct s_list *next;
} t_list;

//a ranger
void	get_index(t_list **l, int *array);
int *get_pivots(t_list *la, int num_chunks); 

//get_nodes_to_top.c
int get_cheaper_and_dest_to_top(t_list **la, t_list **lb, int cheaper);

//pa.c && pb.c
void pa(t_list **la, t_list **lb);
void pb(t_list **la, t_list **lb);

//debug A virer
void print_candidate(t_list node);

//gets.c
int get_cheaper_insertion(t_list **la, t_list **lb);
int get_cheaper_and_dest_to_top(t_list **la, t_list **lb, int cheaper);
void	get_index(t_list **l, int *array);
int get_costs(t_list **lb);
int get_min_index(t_list **l);
int get_max_index(t_list **l);
int get_dests(t_list **la, t_list **lb);
int get_dest_rots(t_list **la, t_list **lb);
int get_rots(t_list **l);


//my_algo
int	partition_stacks(t_list **la, t_list **lb);
int optimise_rotations(t_list *node);
int insert_cheaper(t_list **la, t_list **lb);
int final_rotate(t_list **la);

//size_3_sort.c
void	inverted_size_3_sort(t_list **l);
void	size_3_sort(t_list **la); // pour pile de 2 ou 3

//utils.c // a trier et statiquer 
void free_list(t_list **l);
void print_lst(t_list *l);
void print_lst2(t_list *l);
void add_back(t_list **lst, int n);
int lst_size(t_list *l);
int	*lst_to_array(t_list **la, int size);
int is_sorted_check(t_list *la);
void print_init_lst(t_list *l); // a virer 
void	sort_int_tab(int *tab, unsigned int size);
int	*lst_to_array(t_list **la, int size);
// t_list *lst_last(t_list *lst);

//ops.c
void ra(t_list **l);
void rb(t_list **l);
void rr(t_list **la, t_list **lb);
void rra(t_list **l);
void rrb(t_list **l);
void rrr(t_list **la, t_list **lb);
void sa(t_list **l);
void sb(t_list **l);
void ss(t_list **la, t_list **lb);
void pa(t_list **la, t_list **lb);
void pb(t_list **lb, t_list **la); 

//parsing.c //voir avec la libft ?
int	ft_atoi(const char *nptr);
char **ft_split(const char *s, char c);
t_list *fill_list(char **splitted);
int get_position(t_list **l);

//init.c : revoir ce qu'il faut mettre en static 
int init_stack(t_list **l, int ac, char **av);
int	duplicate_checker(t_list *l);
void	free_splited(char **splited);

#endif
