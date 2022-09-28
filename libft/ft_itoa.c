/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:37:19 by aespinos          #+#    #+#             */
/*   Updated: 2022/02/06 20:37:52 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_counter(long int a)
{
	int	i;

	i = 0;
	if (a == 0 || a < 0)
		i++;
	while (a != 0)
	{
		a /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*number;
	long int	a;
	int			i;
	int			j;

	a = n;
	j = 0;
	i = ft_counter(a);
	number = malloc(sizeof(char) * (i + 1));
	if (!number)
		return (NULL);
	if (n < 0)
	{
		a = -a;
		number[0] = '-';
		j++;
	}
	number[i] = '\0';
	while (i > j)
	{
		number[i - 1] = a % 10 + '0';
		a /= 10;
		i--;
	}
	return (number);
}
