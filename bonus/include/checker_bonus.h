/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:39:07 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/15 17:28:59 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
#define CHECKER_BONUS_H
#include "../../libft/include/libft.h"
#define TRUE 1
#define FALSE 0

typedef char t_bool;

typedef struct s_stack {
  struct s_stack *prev;
  t_bool start;
  int n;
  int i;
  struct s_stack *next;
} t_stack;

typedef char t_bool;

size_t ft_strlengnl(const char *s);
char *ft_strjoin_protected(char *s1, char const *s2);
char *ft_strchr_protected(const char *s, int c);
void *ft_memmove(void *dest, const void *src, size_t n);
char *get_next_line(int fd);
void ft_bzero(void *s, size_t n);

// ops
void push(t_stack **la, t_stack **lb);
void reverse_rotations(t_stack **l);
void rotations(t_stack **l);
void swap(t_stack **l);

// array_utils
void sort_int_tab(int *tab, unsigned int size);

// execute_ops.c
int execute_push(char *op, t_stack **la, t_stack **lb);
int execute_rotations(char *op, t_stack **la, t_stack **lb);
int execute_swap(char *op, t_stack **la, t_stack **lb);
int execute_ops(char *op, t_stack **la, t_stack **lb);
int get_ops(t_stack **la, t_stack **lb);

// init.c
int invalid_input(t_stack *l, int *array, char **s);
int init_stack(t_stack **l, int ac, char **av);

// lst_utils.c
void add_back(t_stack **lst, int n);
int lst_size(t_stack *l);
void free_list(t_stack **l);
int *lst_to_array(t_stack **la, int size);

// utils.c
int is_digits_or_sign(char *s);
int skip_spaces(const char *nptr);
int ft_atoi_limits_check(const char *nptr, t_stack *l);
int is_sorted_check(t_stack *la);

// ops_utils_bonus.c
void stack_empty_case(t_stack **l, t_stack **tmp);
void take_out_stack_top(t_stack **la, t_stack **lb, t_stack **node);
void stack_one_node_case(t_stack **l, t_stack **tmp);
void plug_on_stack(t_stack **l, t_stack **tmp);

#endif
