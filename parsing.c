/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:08:40 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/30 16:04:17 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h> // a virer
#include <stdlib.h>

// ARG="4 56 -3 56" 54 -5
// a gerer !



static int	count_strs(const char *s, char c)
{
	int	strs;
	int	i;

	i = 0;
	strs = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			strs++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (strs);
}

static void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
}

static char	*ft_strdup_custom(char *s, int start, char c)
{
	int		i;
	int		len;
	char	*dup;

	i = start;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (len--)
		dup[i++] = s[start++];
	dup[i] = '\0';
	return (dup);
}

static char	**fill_splited(char **splited, const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i])
		{
			splited[j] = ft_strdup_custom((char *)s, i, c);
			if (splited[j] == NULL)
			{
				ft_free(splited);
				return (NULL);
			}
			j++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	splited[j] = NULL;
	return (splited);
}

char	**ft_split(char const *s, char c)
{
	//passer d'un double tableau a une liste 
	char	**splited;

	if (!s)
		return (NULL);
	splited = malloc(sizeof(char *) * ((count_strs(s, c)) + 1));
	if (!splited)
		return (NULL);
	return (fill_splited(splited, s, c));
}

t_list *fill_list(char **splitted) // revenir pour declarer ici la liste pas dans le main 
{
	t_list *l;
	int i;
	int n;

	l = NULL;
	i = 0;
	while (splitted[i])
	{
		n = atoi(splitted[i]);
		add_back(&l, n);
		i++;
	}
	return (l);
}







/* int	ft_isdigit(int c) */
/* { */
/* 	if (c >= '0' && c <= '9') */
/* 		return (1); */
/* 	else */
/* 		return (0); */
/* } */
/**/
/* char	*ft_substr(char const *s, unsigned int start, size_t len) */
/* { */
/* 	unsigned int	i; */
/* 	char			*res; */
/**/
/* 	i = 0; */
/* 	while (i < start && s[i] != '\0') */
/* 		i++; */
/* 	start = i; */
/* 	while (s[i] != '\0' && len > i - start) */
/* 		i++; */
/* 	len = i - start; */
/* 	res = malloc(sizeof(char) * (len + 1)); */
/* 	if (res == NULL) */
/* 		return (NULL); */
/* 	i = 0; */
/* 	while (s[start + i] != '\0' && len > 0) */
/* 	{ */
/* 		res[i] = s[start + i]; */
/* 		i++; */
/* 		len--; */
/* 	} */
/* 	res[i] = 0; */
/* 	printf("res = %s\n", res); */
/* 	return (res); */
/* } */

/* t_list	*split_int(char **av) */
/* { */
/* 	int		i; */
/* 	int		j; */
/* 	int		sign; */
/* 	int		n_int; */
/* 	char	*n_char; */
/* 	t_list	*l; */
/**/
/* 	i = 0; */
/* 	j = 0; */
/* 	sign = 1; */
/* 	while (av[1][i]) */
/* 	{ */
/* 		while (!(ft_isdigit(av[1][i])) && av[1][i]) */
/* 			i++; */
/* 		j = i; */
/* 		while (ft_isdigit(av[1][j]) && av[1][i]) */
/* 			j++; */
/* 		 printf("j = %d | i = %d | j - i = %d\n", i, j, (j - i)); */ 
/* 		n_char = ft_substr(av[1], i, j - i); */
/* 		 printf("n_char = %s\n", n_char); */ 
/* 		n_int = atoi(n_char) * sign; */
/* 		 printf("n = %d\n", n_int);  */ 
/* 		free(n_char); */
/* 		// is doublon ? */
/* 		 l = lst_new(n) ajouter un node pour chaque int et le relier   */ 
/* 		i = i + j; */
/* 	} */
/* 	return (l); */
/* } */

int	ft_atoi(const char *nptr)
{
	char			sign;
	long long int	n;

	n = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		sign = *nptr;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		n += *nptr - '0';
		nptr++;
		if (*nptr >= '0' && *nptr <= '9')
			n *= 10;
	}
	if (sign == '-')
		n *= -1;
	return (n);
}

// INIT !
// on doit creer la liste en respectant l'ordre dans lequel on recoit les int
// donc on add back pour que le premier arg soit le premier de la pile
/* add_back(&l, atoi(av[i]) */

// creer une liste de 5 elements
// chaque element a
//  - un next vers le suivant
//  - un prev vers le precedent
// Le next du dernier element pointe vers le premier
// le prev du premier elment pointe vers le dernier
//
