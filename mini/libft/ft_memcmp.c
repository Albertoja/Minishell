/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:11:51 by aespinos          #+#    #+#             */
/*   Updated: 2022/01/21 13:04:23 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	cont;

	cont = 0;
	while (cont < n)
	{
		if (((unsigned char *)s1)[cont] != ((unsigned char *)s2)[cont])
			return (((unsigned char *)s1)[cont] - ((unsigned char *)s2)[cont]);
		cont++;
	}
	return (0);
}
