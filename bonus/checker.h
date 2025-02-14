/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:39:07 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/14 13:22:00 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS
# define PUSH_SWAP_BONUS
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define TRUE 1
# define FALSE 0

//revoir les includes
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../includes/push_swap.h" 

typedef char		t_bool;

size_t	ft_strlengnl(const char *s);
char	*ft_strjoin_protected(char *s1, char const *s2);
char	*ft_strchr_protected(const char *s, int c);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*get_next_line(int fd);
void	ft_bzero(void *s, size_t n);

//ops
void	push(t_stack **la, t_stack **lb);

#endif
