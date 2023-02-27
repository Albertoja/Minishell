/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:57:27 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/14 17:10:23 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_noquotes_files(char *str, char a)
{
	str++;
	while (*str != a)
		str++;
	return (str);
}

char	*ft_quotes_files(char *str, char a)
{
	char	*ret;
	int		cont;

	cont = 0;
	while (str[cont] && str[cont] != a)
		cont++;
	ret = malloc(sizeof(char) * (cont + 1));
	cont = 0;
	while (*str && *str != a)
		ret[cont++] = *str++;
	ret[cont] = '\0';
	return (ret);
}

char	*ft_in_files(char *str)
{
	char	*ret;

	while (*str == '<' || *str == '>' || *str == ' ')
		str++;
	if (*str == '"')
		return (ft_quotes_files(++str, '"'));
	else
		return (ft_quotes_files(str, ' '));
	return (ret);
}

char	**search_files(char *str)
{
	char	*str_aux[2];
	char	**ret;

	str_aux[0] = NULL;
	while (*str)
	{
		if (*str == '<' || *str == '>')
		{
			while (*str == '<' || *str == '>' || *str == ' ')
				str++;
			str_aux[1] = ft_in_files(str);
			if (!str_aux[0])
				str_aux[0] = ft_strdup(str_aux[1]);
			else
				str_aux[0] = ft_strjoin(str_aux[0], str_aux[1]);
			str_aux[0] = ft_strjoin(str_aux[0], "|");
			free(str_aux[1]);
		}
		if (*str == '"')
			str = ft_noquotes_files(str, '"');
		str++;
	}
	ret = ft_split_pipe(str_aux[0], '|');
	free (str_aux[0]);
	return (ret);
}
