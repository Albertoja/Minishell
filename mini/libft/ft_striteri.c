/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:54:30 by aespinos          #+#    #+#             */
/*   Updated: 2022/02/07 16:55:48 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	a;

	if (!s || !f)
		return ;
	if (s || f)
	{
		a = 0;
		while (*s)
		{
			(*f)(a, s);
			a++;
			s++;
		}
	}
	else
		return ;
}
