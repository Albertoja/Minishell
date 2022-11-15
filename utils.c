/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:53:17 by aespinos          #+#    #+#             */
/*   Updated: 2022/10/25 18:03:15 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		cont;

	cont = 0;
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

size_t	ft_strlen(const char *s)
{
	size_t	nb;
	{
		nb = 0;
		while (*s != '\0')
		{
			s++;
			nb++;
		}
		return (nb);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	cont;

	cont = 0;
	if (!s)
		return (NULL);
	if (*s == '\0' || start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (cont < len)
	{
		str[cont] = s[start + cont];
		cont++;
	}
	str[cont] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	else
		return (NULL);
}
