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

#include <stdbool.h>
#include <stddef.h>

typedef struct s_list // s_list / t_list ?
{
  struct s_list *prev;
  bool          start; // IL FAUT DEFINE LE BOOL ?
  int           n;
  int           i;
  int pos; // Todo
  int rot; // positive ou negative : 
           // pour opti : on check comment avoir au top dest et candidate 
           // en combinant ou non les rot 
           // ra et rb parfois plus rentable que rr rrr ?
  int cost;
  int pivot;
  int dest;
  int dest_rot;
  struct s_list *next;
} t_list;

typedef struct s_move
{
  int candidate;
  int dest;
  int rr;
  int rrr;
  int ra;
  int rb;
  int rra;
  int rrb;
} t_move;

//a ranger
void	get_index(t_list **l, int *array);

//utils.c // a trier et statiquer 
void free_list(t_list **l);
void print_lst(t_list *l);
void print_lst2(t_list *l);
void add_back(t_list **lst, int n);
int lst_size(t_list *l);
int	*lst_to_array(t_list **la, int size);
int is_sorted_check(t_list *la);
void print_init_lst(t_list *l); // a virer 
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
