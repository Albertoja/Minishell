/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:10:32 by aespinos          #+#    #+#             */
/*   Updated: 2022/06/22 18:39:17 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_start(char const *s1, char const *set)
{
	size_t	a;
	size_t	b;
	size_t	cont;

	a = 0;
	b = 0;
	cont = 0;
	while (s1[a] && set[b])
	{
		if (s1[a] != set[b])
		{
			b++;
			if (!set[b])
				break ;
		}
		else
		{
			cont++;
			a++;
			b = 0;
		}	
	}
	return (cont);
}

size_t	ft_end(char const *s1, char const *set)
{
	size_t	a;
	size_t	b;
	size_t	cont;
	size_t	len;

	a = 0;
	b = 0;
	cont = 0;
	len = ft_strlen(s1);
	while (set[b] && a < len)
	{
		if (s1[len - 1 - a] != set[b])
		{
			b++;
			if (!set[b])
				break ;
		}
		else
		{
			cont++;
			a++;
			b = 0;
		}	
	}
	return (cont);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	a;
	size_t	len;
	char	*str;

	a = -1;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1) - (ft_start(s1, set) + ft_end(s1, set));
	if (ft_strlen(s1) < ft_start(s1, set) + ft_end(s1, set))
		len = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (len > ++a)
		str[a] = s1[ft_start(s1, set) + a];
	str[a] = '\0';
	return (str);
}
