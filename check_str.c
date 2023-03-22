/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:44 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/15 17:03:20 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_pipe(char *str)
{
	int	aux;

	aux = 0;
	while (str[aux] == ' ' || (str[aux] >= 9 && str[aux] <= 13))
		aux++;
	if (str[aux] == '|')
		ft_error("pipe suelto", NULL);
	while (str[aux])
	{
		if (str[aux] == '|')
		{
			aux++;
			while (str[aux])
			{
				if (str[aux] == ' ' || (str[aux] >= 9 && str[aux] <= 13))
					aux++;
				else
					break ;
			}
			if (!str[aux])
				return (ft_endpipe(str));
		}
		aux++;
	}
	return (str);
}

int	ft_rederror(char *straux, int cont)
{
	cont++;
	while (straux[cont])
	{
		if (straux[cont] == ' ')
			cont++;
		else
			return (1);
	}
	return (0);
}

char	*ft_check_red2(char *str, int cont)
{
	if (!ft_rederror(str, cont))
		return (ft_errorred(str, 1));
	else
	{
		cont++;
		if (str[cont] == '<')
			return (ft_errorred(str, 2));
		if (str[cont] == '>')
		{
			if (!str[cont + 1])
				return (ft_errorred(str, 1));
		}
	}
	return (str);
}

char	*ft_check_red(char *str)
{
	int	cont;

	cont = -1;
	while (str[++cont] && str && str != NULL)
	{
		if (str[cont] == '<')
		{
			if (!ft_rederror(str, cont))
				return (ft_errorred(str, 1));
			else
			{
				cont++;
				if (str[cont] == '>')
					return (ft_errorred(str, 2));
				if (str[cont] == '<')
				{
					if (!str[cont + 1])
						return (ft_errorred(str, 1));
				}
			}
		}
		else if (str[cont] == '>')
			str = ft_check_red2(str, cont);
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
