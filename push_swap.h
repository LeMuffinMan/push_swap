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

typedef struct s_list
{
  struct s_list *prev;
  bool          start;
  int           n;
  struct s_list *next;
} t_list;


//utils.c
void free_list(t_list **l);
// void print_lst(t_list *l);
void print_lst(t_list *l);
t_list *lst_last(t_list *lst);
void add_back(t_list **lst, int n);


//ops.c
void rotate(t_list **l);
void rotate_both(t_list **la, t_list **lb);
void reverse_rotate(t_list **l);
void reverse_rotate_both(t_list **la, t_list **lb);
void swap(t_list **l);
void swap_both(t_list **la, t_list **lb);
void push(t_list **la, t_list **lb);

//parsing.c
int	ft_atoi(const char *nptr);
char **ft_split(const char *s, char c);
t_list *fill_list(char **splitted);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// t_list *split_int(char **av);
// int	ft_isdigit(int c);

//init.c
int init_stack(t_list **l, char **av);
void init_stackb(t_list **l);
