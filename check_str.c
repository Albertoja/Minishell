/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:44 by aespinos          #+#    #+#             */
/*   Updated: 2022/10/18 20:13:02 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_pipe(char *str)
{
	int	aux;

	aux = 0;
	while (str[aux] == ' ' || (str[aux] >= 9 && str[aux] <= 13))
		aux++;
	if (str[aux] == '|')
		ft_error("pipe suelto");
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
				ft_error("pipe suelto");
		}
		aux++;
	}
}

void	check_str(char *str)
{
	int	aux;

	aux = 0;
	while (str[aux])
	{
		if (str[aux] == 34)
		{
			aux++;
			while (str[aux] && str[aux] != 34)
				aux++;
			if (str[aux] != 34)
				ft_error("comillas no cerradas");
		}
		if (str[aux] == 39)
		{
			aux++;
			while (str[aux] && str[aux] != 39)
				aux++;
			if (str[aux] != 39)
				ft_error("comillas no cerradas");
		}
		aux++;
	}
	ft_check_pipe(str);
}
