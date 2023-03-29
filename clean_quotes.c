/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:45:37 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/28 19:55:50 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_no_quotes(char *str)
{
	int		i;
	char	com;
	int		a;
	int		b;

	a = 0;
	b = 0;
	i = 0;
	a = ft_strlen(str);
	while (b < a)
	{
		if (str[b] == 34 || str[b] == 39)
		{
			com = str[b++];
			while (str[b] && str[b] != com)
			{
				i++;
				b++;
			}
		}
		if (str[b++])
			i++;
	}
	return (i);
}

char	*copy_no_quotes(char *str)
{
	char	*aux;
	int		i;
	char	com;

	i = 0;
	aux = malloc(count_no_quotes(str) + 1);
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			com = *str++;
			while (*str && *str != com)
				aux[i++] = *str++;
		}
		if (*str != com)
			aux[i++] = *str;
		str++;
	}
	aux[i] = '\0';
	return (aux);
}

char	**ft_clean_quotes(char **files)
{
	char	*aux;
	int		i;

	i = -1;
	if (!files)
		return (NULL);
	while (files[++i])
	{
		aux = copy_no_quotes(files[i]);
		free(files[i]);
		files[i] = aux;
	}
	return (files);
}
