/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:55:59 by aespinos          #+#    #+#             */
/*   Updated: 2022/08/30 19:05:46 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, char const *s2)
{
	size_t	i;
	size_t	k;
	size_t	len1;
	size_t	len2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	k = -1;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	while (++i < len1)
		str[i] = s1[i];
	while (++k < len2)
	{
		str[i] = s2[k];
		i++;
	}
	str[i] = '\0';
	free((void *)s1);
	return (str);
}
