/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:57 by aespinos          #+#    #+#             */
/*   Updated: 2023/01/25 16:12:58 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_countpipe(char const *s, char c, int i)
{
	int		a;
	char	aux;

	a = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		if (s[i] == 34 || s[i] == 39)
		{
			aux = s[i];
			i++;
			a++;
			while (s[i] != aux)
			{
				i++;
				a++;
			}
		}
		a++;
		i++;
	}
	return (a);
}

int	ft_countwordspipe(char const *s, char c)
{
	int		i;
	int		cont;
	char	aux;

	i = 0;
	cont = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
				i++;
		if (s[i] == '\0')
			break ;
		while (s[i] && s[i] != c)
		{
			if (s[i] == 34 || s[i] == 39)
			{
				aux = s[i++];
				while (s[i] && s[i] != aux)
					i++;
			}
			i++;
		}
		cont++;
	}
	return (cont);
}

char	**ft_splitauxpipe(char **str, const char *s, char c, int a)
{
	int		i;
	int		j;
	int		pal;
	char	aux;

	pal = ft_countwordspipe(s, c);
	i = 0;
	while (pal--)
	{
		str[i] = (char *)malloc(sizeof(char) * (ft_countpipe(s, c, a) + 1));
		j = 0;
		while (s[a] != '\0' && s[a] != c)
		{
			if (s[a] == 34 || s[a] == 39)
			{
				aux = s[a];
				str[i][j++] = s[a++];
				while (s[a] != aux)
					str[i][j++] = s[a++];
			}
			str[i][j++] = s[a++];
		}
		str[i][j] = '\0';
		while (s[a] == c && s[a])
			a++;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split_pipe(char const *s, char c)
{
	int		a;
	char	**str;

	a = 0;
	if (!s || !*s || s == NULL)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_countwordspipe(s, c) + 1));
	if (!str)
		return (NULL);
	while (s[a] == c)
		a++;
	return (ft_splitauxpipe(str, s, c, a));
}
