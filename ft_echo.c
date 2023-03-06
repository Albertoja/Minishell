/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:57:26 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/27 16:47:28 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_compare_n(char *str)
{
	int	cont;

	cont = 0;
	if (str[cont] != '-')
		return (0);
	cont++;
	while (str[cont])
	{
		if (str[cont] == 'n')
			cont++;
		else
			return (0);
	}
	return (1);
}

int	ft_echo(char **str)
{
	int	cont;
	int	sw;

	sw = 0;
	cont = 1;
	while (str[cont] && ft_compare_n(str[cont]) == 1)
	{
		cont++;
		sw++;
	}
	while (str[cont])
	{
		write(1, str[cont], ft_strlen(str[cont]));
		if (str[cont + 1])
			write(1, " ", 1);
		cont++;
	}
	if (sw == 0)
		write(1, "\n", 1);
	return (0);
}
