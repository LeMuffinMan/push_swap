#include <stdlib.h>
#include "push_swap.h"

int	ft_atoi(const char *nptr, t_list *l)
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
	if (n > 2147483647 || n < -2147483648)
		invalid_input(l, NULL, NULL);
	return (n);
}


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

//a revoir
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

int ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		i++;
	return (i);
}

void	free_splited(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		i++;
	}
	free(splited);
}
