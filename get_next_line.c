/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:00:18 by aespinos          #+#    #+#             */
/*   Updated: 2022/06/23 18:44:06 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <stdio.h>

int	ft_endlen(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	return (i);
}

char	*ft_textsave(char *text)
{
	size_t	i;
	size_t	len;
	size_t	tlen;
	char	*textaux;

	i = 0;
	len = ft_endlen(text);
	if (!text[len])
	{
		free(text);
		return (NULL);
	}
	tlen = ft_strlen(text);
	textaux = (char *)malloc(sizeof(char) * (tlen - len + 1));
	if (!textaux)
		return (NULL);
	while (len + i < tlen)
	{
		textaux[i] = text[i + len];
		i++;
	}
	textaux[i] = '\0';
	free(text);
	return (textaux);
}

char	*ft_returnline(char *textaux)
{
	char	*line;
	int		cont;

	line = (char *)malloc(sizeof(char) * (ft_strlen(textaux) + 1));
	cont = 0;
	if (textaux[0] == '\n')
	{
		line[0] = '\n';
		line[1] = '\0';
		return (line);
	}
	while (textaux[cont] != '\n' && textaux[cont] != '\0')
	{
		line[cont] = textaux[cont];
		cont++;
	}
	if (textaux[cont] == '\n')
	{
		line[cont] = '\n';
		cont++;
	}
	line[cont] = '\0';
	return (line);
}

char	*ft_read(int fd, char *text, int a)
{
	char	*line;

	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	while (!ft_strchr(text, '\n') && a == BUFFER_SIZE)
	{
		a = read(fd, line, BUFFER_SIZE);
		if (a == -1)
		{
			free(line);
			return (NULL);
		}
		if (a != 0)
		{
			line[a] = '\0';
			if (!text)
				text = ft_strdup(line);
			else
				text = ft_strjoin(text, line);
		}
	}
	free (line);
	return (text);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*textaux;
	int			a;

	a = BUFFER_SIZE;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1000)
		return (NULL);
	text = ft_read(fd, text, a);
	if (!text)
		return (NULL);
	textaux = ft_returnline(text);
	text = ft_textsave(text);
	return (textaux);
}
