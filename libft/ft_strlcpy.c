/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:23:28 by aespinos          #+#    #+#             */
/*   Updated: 2022/01/21 13:04:54 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	cont;
	size_t	count;

	cont = 0;
	while (src[cont] != '\0')
		cont++;
	if (dstsize == 0)
		return (cont);
	count = 0;
	while (src[count] != '\0' && count < (dstsize - 1))
	{
		dst[count] = src[count];
		count++;
	}
	dst[count++] = '\0';
	return (cont);
}
