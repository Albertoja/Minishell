/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:42:13 by aespinos          #+#    #+#             */
/*   Updated: 2023/04/03 19:34:11 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nm_red(char *str, int cont)
{
	while (str[cont] && (str[cont] == '>' || str[cont] == '<'))
		cont++;
	while (str[cont] && str[cont] == ' ')
		cont++;
	while (str[cont] && str[cont] != ' ')
		cont++;
	return (cont);
}

int	ft_cmds_len(char *str)
{
	int	len;
	int	cont;

	cont = 0;
	len = 0;
	while (str[cont])
	{
		while (str[cont] && str[cont] != '<' && str[cont] != '>'
			&& str[cont] != '"' && str[cont] != '\'')
		{
			cont++;
			len++;
		}
		if (str[cont] == '<' || str[cont] == '>')
			cont = ft_nm_red(str, cont);
		if (str[cont] == '"' || str[cont] == '\'')
		{
			len = len + (ft_jump(str, cont) - cont) + 1;
			cont = ft_jump(str, cont);
			cont++;
		}
	}
	return (len);
}

char	*search_cmds3(char *str, char *ret, int *cont, int *cont2)
{
	char	aux;

	aux = str[*cont];
	ret[(*cont2)++] = str[(*cont)++];
	while (str[*cont] && str[*cont] != aux)
		ret[(*cont2)++] = str[(*cont)++];
	if (str[*cont] == aux)
		ret[(*cont2)++] = str[(*cont)++];
	return (ret);
}

char	*search_cmds2(char *str, int len)
{
	char	*ret;
	int		cont[1];
	int		cont2[1];

	*cont = 0;
	*cont2 = 0;
	ret = malloc(sizeof(char) * (len + 1));
	while (str[*cont])
	{
		while (str[*cont] && str[*cont] != '<' && str[*cont] != '>'
			&& str[*cont] != '"' && str[*cont] != '\'')
			ret[(*cont2)++] = str[(*cont)++];
		if (str[*cont] == '<' || str[*cont] == '>')
			*cont = ft_nm_red(str, *cont);
		if (str[*cont] == '"' || str[*cont] == '\'')
			ret = search_cmds3(str, ret, cont, cont2);
	}
	ret[*cont2] = '\0';
	return (ret);
}

char	**search_cmds(char *str)
{
	char	*straux;
	int		len;
	char	**ret;

	if (!str || !*str)
		return (0);
	ret = NULL;
	len = 0;
	len = ft_cmds_len(str);
	straux = search_cmds2(str, len);
	ret = ft_split_pipe(straux, ' ');
	free(straux);
	return (ret);
}
