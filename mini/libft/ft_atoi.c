/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:14:44 by aespinos          #+#    #+#             */
/*   Updated: 2022/06/27 19:22:18 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static unsigned long long int	ft_check(unsigned long long int result, int sig)
{
	if (result > 9223372036854775807 && sig < 0)
		return (0);
	else if (result > 9223372036854775807 && sig > 0)
		return (-1);
	else
		return (result);
}

int	ft_atoi(const char *str)
{
	int						x;
	int						sig;
	unsigned long long int	result;
	{
		x = 0;
		sig = 1;
		result = 0;
		while (str[x] == ' ' || str[x] == '\t' || str[x] == '\n'
			|| str[x] == '\v' || str[x] == '\f' || str[x] == '\r')
			x++;
		while (str[x] == '+' || str[x] == '-')
		{
			if (str[x] == '-')
				sig = sig * (-1);
			if (str[x + 1] == '+' || str[x + 1] == '-')
				return (0);
			x++;
		}
		while (str[x] >= '0' && str[x] <= '9')
		{
			result = (str[x] - 48) + (result * 10);
			x++;
		}
		return ((int)ft_check(result, sig) * sig);
	}
}
