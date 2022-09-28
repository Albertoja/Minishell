/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:25:22 by aespinos          #+#    #+#             */
/*   Updated: 2022/01/21 13:05:18 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	cont_00;
	size_t	cont_01;
	size_t	sch;

	cont_00 = 0;
	cont_01 = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (cont_00 < len && haystack[cont_00])
	{
		if (haystack[cont_00] == needle[cont_01])
		{
			sch = cont_00;
			while (sch < len && haystack[sch] == needle[cont_01])
			{
				sch++;
				cont_01++;
				if (needle[cont_01] == '\0')
					return ((char *)haystack + cont_00);
			}
			cont_01 = 0;
		}
		cont_00++;
	}
	return (NULL);
}
