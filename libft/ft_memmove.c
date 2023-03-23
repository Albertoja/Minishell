/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:15:08 by aespinos          #+#    #+#             */
/*   Updated: 2022/02/06 20:44:50 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	cont;

	cont = 0;
	if (NULL == dst && NULL == src)
		return (dst);
	if (dst <= src)
	{
		while (cont < len)
		{
			(((char *)dst)[cont]) = (((char *)src)[cont]);
			cont++;
		}
	}
	else
	{
		while (len > 0)
		{
			(((char *)dst)[len - 1]) = (((char *)src)[len - 1]);
			len--;
		}
	}
	return (dst);
}
