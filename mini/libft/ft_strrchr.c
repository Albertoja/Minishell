/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:25:52 by aespinos          #+#    #+#             */
/*   Updated: 2022/06/22 18:39:55 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
		a++;
	while (a != 0)
	{
		if (s[a] == (unsigned char) c)
			return ((char *)s + a);
		if (((char *)s)[a] == c)
			return ((char *)s + a);
		a--;
	}
	if (s[a] == (unsigned char)c)
		return ((char *)(s + a));
	else
		return (NULL);
}
