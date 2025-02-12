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

//my_algo
  //easy_cases.c
void	easy_cases(t_list **la); // pour pile de 2 ou 3
  //get_cheaper_insertion
void get_costs(t_list **lb);
int get_cheaper_insertion(t_list **l);
int optimise_rotations(t_list *node);
  //get_nodes_to_top
void get_nodes_to_top(t_list **la, t_list **lb, int cheaper);
  //my_algo
void	partition_stacks(t_list **la, t_list **lb, int median, int size);
int insert_cheaper(t_list **la, t_list **lb);
void final_rotate(t_list **la);
  //update_list_infos.c
void	get_index(t_list **l, int *array);
void get_dests(t_list **la, t_list **lb);
void get_dest_rots(t_list **la, t_list **lb);
void get_rots(t_list **l);
int get_position(t_list **l);

//ops
  //pa.c
void pa(t_list **la, t_list **lb);
  //pb.c
void pb(t_list **lb, t_list **la); 
 //reverse_rotations.c
void rra(t_list **l);
void rrb(t_list **l);
void rrr(t_list **la, t_list **lb);
  //rotations.c
void ra(t_list **l);
void rb(t_list **l);
void rr(t_list **la, t_list **lb);
  //swap.c
void sa(t_list **l);
void sb(t_list **l);
void ss(t_list **la, t_list **lb);


//utils
  //array_utils.c
int	*lst_to_array(t_list **la, int size);
  //get_min_max_index.c
int get_min_index(t_list **l);
int get_max_index(t_list **l);
  //list_utils.c
void free_list(t_list **l);
void add_back(t_list **lst, int n);
int lst_size(t_list *l);
int is_sorted_check(t_list *la);




//a ranger
void	get_index(t_list **l, int *array);
int *get_pivots(t_list *la, int num_chunks); 



//pa.c && pb.c
void pa(t_list **la, t_list **lb);
void pb(t_list **la, t_list **lb);

//debug A virer
void print_candidate(t_list node);

//gets.c


//my_algo
//size_3_sort.c

//utils.c // a trier et statiquer 
void print_lst(t_list *l);

int is_digits_or_sign(char *s);
// t_list *lst_last(t_list *lst);

//ops.c


//parsing.c //voir avec la libft ?
int	ft_atoi(const char *nptr, t_list *l);
char **ft_split(const char *s, char c);
t_list *fill_list(char **splitted);
void	free_splited(char **splited);

//init.c : revoir ce qu'il faut mettre en static 
int init_stack(t_list **l, int ac, char **av);
int invalid_input(t_list *l, int *array, char **s);
int init_step_2(t_list **l);

#endif
