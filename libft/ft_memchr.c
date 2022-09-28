/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:11:07 by aespinos          #+#    #+#             */
/*   Updated: 2022/01/20 16:11:07 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	cont;
	char	*tmp;

	cont = 0;
	tmp = (char *)s;
	while (cont < n)
	{
		if (tmp[cont] == (char)c)
			return (tmp + cont);
		cont++;
	}
	return (0);
}
