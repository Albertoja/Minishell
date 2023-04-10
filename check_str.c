/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:44 by aespinos          #+#    #+#             */
/*   Updated: 2023/04/10 16:02:29 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_pipe2(char *str, int aux)
{
	while (str[aux])
	{
		if (str[aux] == ' ' || (str[aux] >= 9 && str[aux] <= 13))
			aux++;
		else
			break ;
	}
	return (aux);
}

char	*ft_errpipe(char *str)
{
	printf("minishell: syntax error near unexpected token `|'\n");
	free(str);
	return (ft_strdup(" "));
}

char	*ft_check_pipe(char *str)
{
	int	aux;

	aux = 0;
	while (str[aux] == ' ' || (str[aux] >= 9 && str[aux] <= 13))
		aux++;
	if (str[aux] == '|')
		return (ft_errpipe(str));
	while (str[aux])
	{
		if (str[aux] == '|')
		{
			aux++;
			aux = ft_check_pipe2(str, aux);
			if (str[aux] == '|')
				return (ft_errpipe(str));
			if (!str[aux])
				return (ft_endpipe(str));
		}
		aux++;
	}
	return (str);
}

char	*check_str(char *str)
{
	int		aux;
	char	quot;

	aux = 0;
	if (!str)
		return (NULL);
	while (str[aux])
	{
		if (str[aux] == 34 || str[aux] == 39)
		{
			quot = str[aux];
			aux++;
			while (str[aux] && str[aux] != quot)
				aux++;
			if (str[aux] != quot)
				return (ft_endquotes(str, quot));
		}
		aux++;
	}
	str = ft_check_pipe(str);
	str = ft_check_red(str);
	return (str);
}
