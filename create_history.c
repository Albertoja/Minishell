/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:47:51 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/29 18:03:54 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_history2(int fd)
{
	char	*line;
	char	*aux;

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
}

void	ft_read_history(char **env)
{
	int		fd;
	char	*home;
	int		a;

	a = -1;
	home = ft_search_home(env);
	if (home)
	{
		while (++a <= 4)
			home++;
		home = ft_strjoinm(home, "/.history");
		fd = open(home, O_CREAT | O_RDWR, 0644);
		free(home);
		if (fd == -1)
			return ;
		ft_read_history2(fd);
		close (fd);
	}
}

void	ft_create_history(char *input, char **env)
{
	int		fd;
	char	*home;
	int		a;

	a = -1;
	home = ft_search_home(env);
	if (home)
	{
		while (++a <= 4)
			home++;
		home = ft_strjoinm(home, "/.history");
		fd = open(home, O_CREAT | O_RDWR | O_APPEND, 0644);
		free(home);
		if (fd == -1)
			return ;
		ft_putstr_fd(input, fd);
		ft_putchar_fd('\n', fd);
		ft_putstr_fd(input, fd);
		ft_putchar_fd('\n', fd);
		close(fd);
	}
	add_history(input);
}
