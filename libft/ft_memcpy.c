/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:12:07 by aespinos          #+#    #+#             */
/*   Updated: 2022/02/06 20:44:29 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	char		*p1;
	const char	*p2;

	p1 = dst;
	p2 = src;
	if (NULL == dst && NULL == src)
		return (dst);
	if (n)
	{
	n++;
		while (--n > 0)
		{
			*p1++ = *p2++;
		}
	}
	return (dst);
}
