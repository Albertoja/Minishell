/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:18:44 by aespinos          #+#    #+#             */
/*   Updated: 2022/11/17 18:46:06 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		cont;

	cont = 0;
	if (!s1 || s1 == NULL || !*s1)
		return (0);
	dst = malloc(ft_strlen(s1) + 1);
	if (!dst)
		return (0);
	while (s1[cont])
	{	
		dst[cont] = s1[cont];
		cont++;
	}
	dst[cont] = '\0';
	return (dst);
}
