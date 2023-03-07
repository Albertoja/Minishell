/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:47:51 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/07 18:06:41 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_history(void)
{
	int		fd;
	char	*line;
	char	*aux;

	fd = open(".history", O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	if (line)
		aux = ft_substr(line, 0, ft_strlen(line) - 1);
	while (line)
	{
		add_history(aux);
		free(line);
		free(aux);
		line = get_next_line(fd);
		if (line)
			aux = ft_substr(line, 0, ft_strlen(line) - 1);
	}
	close (fd);
}

void	ft_create_history(char *input)
{
	int	fd;

	fd = open(".history", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return ;
	add_history(input);
	ft_putstr_fd(input, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}
