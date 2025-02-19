/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:32:38 by oelleaum          #+#    #+#             */
/*   Updated: 2025/02/13 14:05:04 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>

int	is_digits_or_sign(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] != '-' && s[i] != '+' && (s[i] > '9' || s[i] < '0'))
			return (1);
		i++;
	}
	return (0);
}

int	skip_spaces(const char *nptr)
{
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	return (0);
}

int	ft_atoi_limits_check(const char *nptr, t_stack *l)
{
	char			sign;
	long long int	n;

	n = 0;
	sign = ' ';
	skip_spaces(nptr);
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
	if (n > 2147483647 || n < -2147483648)
		invalid_input(l, NULL, NULL);
	return (n);
}
