/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:08:40 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/30 17:37:28 by oelleaum         ###   ########lyon.fr   */
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
