/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:42:13 by aespinos          #+#    #+#             */
/*   Updated: 2023/01/10 16:04:43 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmds_len(char *str)
{
	int	len;
	int	cont;

	cont = 0;
	len = 0;
	while (str[cont])
	{
		while (str[cont] && str[cont] != '<' && str[cont] != '>')
		{
			len++;
			cont++;
		}
		while (str[cont] && (str[cont] == '<' || str[cont] == '>'))
			cont++;
		while (str[cont] && str[cont] == ' ')
			cont++;
		if (str[cont] && str[cont] == '"')
		{
			while (str[++cont] && str[cont] != '"')
				cont++;
		}
		while (str[cont] && str[cont] != ' ')
			cont++;
	}
	return (len);
}

int	search_cmds3(char *str, int cont)
{
	while (str[cont] && (str[cont] == '<' || str[cont] == '>'))
		cont++;
	while (str[cont] && str[cont] == ' ')
		cont++;
	if (str[cont] && str[cont] == '"')
	{
		cont++;
		while (str[cont] && str[cont] != '"')
			cont++;
	}
	while (str[cont] && str[cont] != ' ')
		cont++;
	return (cont);
}

char	*search_cmds2(char *str, int len)
{
	char	*ret;
	int		cont;
	int		cont2;

	cont = 0;
	cont2 = 0;
	ret = malloc(sizeof(char) * (len + 1));
	while (str[cont])
	{
		while (str[cont] && str[cont] != '<' && str[cont] != '>')
		{
			ret[cont2] = str[cont];
			cont2++;
			cont++;
		}
		cont = search_cmds3(str, cont);
	}
	ret[cont2] = '\0';
	return (ret);
}

char	**search_cmds(char *str)
{
	char	*straux;
	int		len;
	int		lenaux;
	char	**ret;

	if (!str || !*str)
		return (0);
	ret = NULL;
	len = 0;
	lenaux = 0;
	len = ft_cmds_len(str);
	straux = search_cmds2(str, len);
	ret = ft_split_pipe(straux, ' ');
	free(straux);
	return (ret);
}
