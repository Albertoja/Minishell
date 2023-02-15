/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:00:18 by aespinos          #+#    #+#             */
/*   Updated: 2022/12/01 17:58:37 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <stdio.h>

size_t	ft_linelen(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoingnl(const char *s1, char const *s2)
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
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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

static char	*ft_extraline(char *text)
{
	size_t	i;
	size_t	len;
	size_t	tlen;
	char	*exline;

	i = 0;
	len = ft_linelen(text);
	if (!text[len])
	{
		free(text);
		return (NULL);
	}
	tlen = ft_strlen(text);
	exline = (char *)malloc(sizeof(char) * (tlen - len + 1));
	if (!exline)
		return (NULL);
	while (len + i < tlen)
	{
		exline[i] = text[i + len];
		i++;
	}
	exline[i] = '\0';
	free(text);
	return (exline);
}

static char	*ft_line(char *text)
{
	size_t	i;
	size_t	len;
	char	*line;

	i = 0;
	if (!text[i])
		return (NULL);
	len = ft_linelen(text);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = text[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_read(int fd, char *text)
{
	ssize_t	nb;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	nb = 1;
	while (!ft_strchr(text, '\n') && nb != 0)
	{
		nb = read(fd, buffer, BUFFER_SIZE);
		if (nb == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[nb] = '\0';
		if (!text)
			text = ft_strdup(buffer);
		else
			text = ft_strjoingnl(text, buffer);
	}
	free(buffer);
	return (text);
}

char	*get_next_line(int fd)
{
	static char	*text[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	text[fd] = ft_read(fd, text[fd]);
	if (!text[fd])
		return (NULL);
	line = ft_line(text[fd]);
	text[fd] = ft_extraline(text[fd]);
	return (line);
}
