/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:42:44 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/28 13:51:44 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	outputredirectionaux(t_all *f, char **envp, char *path, int *i)
{
	while (f->files[i[1]])
	{
		i[0] = open(f->files[i[1]], O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(i[0], STDOUT_FILENO);
		(i[1])++;
	}
	if (execve(path, &f->cmds[0], envp) == -1)
	{
		free(path);
		ft_error("execve error", f->cmds[0]);
	}
}

void	outputredirection(t_all *f, char **envp, int *status)
{
	char	*path;
	int		i[2];
	pid_t	pid;

	i[0] = 0;
	i[1] = 0;
	path = get_path(f->cmds[0], envp);
	if (!path)
	{
		free(path);
		ft_error("command not found", f->cmds[0]);
		*status = 127;
	}
	else
	{
		pid = fork();
		if (pid == 0)
			outputredirectionaux(f, envp, path, i);
		else
			while (waitpid(-1, NULL, WUNTRACED) == -1)
				close(i[0]);
		free(path);
		waitpid(pid, status, 0);
	}
}

void	inputredirectionaux(t_all *f, char **envp, int *status, int fd)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		path = get_path(f->cmds[0], envp);
		if (execve(path, &f->cmds[0], envp) == -1)
		{
			ft_error("command not found", f->cmds[0]);
		}
	}
	else
	{
		while (waitpid(-1, NULL, WUNTRACED) == -1)
			close(fd);
	}
	waitpid(pid, status, 0);
}

void	inputredirection(t_all *f, char **envp, int *status)
{
	int		fd;
	char	*path;

	path = get_path(f->cmds[0], envp);
	if (!path)
	{
		ft_error("command not found", f->cmds[0]);
		*status = 127;
	}
	else
	{
		fd = open(f->files[0], O_RDONLY, 0644);
		if (fd == -1)
		{
			printf("minishell : %s Can Not Read the Input File\n", f->files[0]);
			*status = 127;
		}
		else
		{
			inputredirectionaux(f, envp, status, fd);
		}
	}
}

int	outputappendredirection(t_all *f, char **envp)
{
	char	*path;
	int		fd;
	int		status;
	pid_t	pid;

	fd = 0;
	pid = fork();
	if (pid == 0)
	{
		fd = open(f->files[0], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			ft_error("Error: Can Not Read the Input File", "\n");
		dup2(fd, STDOUT_FILENO);
		path = get_path(f->cmds[0], envp);
		if (execve(path, &f->cmds[0], envp) == -1)
			ft_error("command not found", f->cmds[0]);
	}
	else
	{
		while (waitpid(-1, NULL, WUNTRACED) == -1)
			close(fd);
	}
	waitpid(pid, &status, 0);
	return (status);
}
