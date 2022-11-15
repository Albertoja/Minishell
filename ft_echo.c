/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:57:26 by aespinos          #+#    #+#             */
/*   Updated: 2022/11/02 15:57:41 by aespinos         ###   ########.fr       */
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

void	ft_echo(char **str)
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
		printf("%s", str[cont]);
		cont++;
	}
	if (sw == 0)
		printf("\n");
}
