/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:57 by aespinos          #+#    #+#             */
/*   Updated: 2022/11/23 19:21:50 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count(char const *s, char c, int i)
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

int	ft_countwords(char const *s, char c)
{
	int		i;
	int		cont;
	char	aux;

	i = 0;
	cont = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
				i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
		{
			if (s[i] == 34 || s[i] == 39)
			{
				aux = s[i++];
				while (s[i] != aux)
					i++;
			}
			i++;
		}
		cont++;
	}
	return (cont);
}

char	**ft_splitaux(char **str, const char *s, char c, int a)
{
	int		*i;
	int		pal;

	pal = ft_countwords(s, c);
	i = malloc(sizeof(int) * 2);
	i[0] = 0;
	while (pal--)
	{
		str[i[0]] = (char *)malloc(sizeof(char) * (ft_count(s, c, a) + 1));
		if (!str[i[0]])
		{
			ft_free_matrix(str);
			return (NULL);
		}
		i[1] = 0;
		while (s[a] != '\0' && s[a] != c)
			hello_norminette(str, s, &i, &a);
		str[i[0]][i[1]] = '\0';
		while (s[a] == c && s[a])
			a++;
		i[0]++;
	}
	str[i[0]] = NULL;
	free(i);
	return (str);
}

char	**ft_split_pipe(char const *s, char c)
{
	int		a;
	char	**str;

	a = 0;
	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!str)
		return (NULL);
	while (s[a] == c)
		a++;
	return (ft_splitaux(str, s, c, a));
}
