/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:42:44 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/25 17:44:34 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredocaux(int *fd_len, t_all *f, char **envp, int *pip);

int	outputredirection(t_all *f, char **envp)
{
	char	*path;
	int		fd;
	int		status;
	pid_t	pid;

	fd = 0;
	pid = fork();
	if (pid == 0)
	{
		fd = open(f->files[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			error("Error: Can Not Read the Output File");
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

int	inputredirection(t_all *f, char **envp)
{
	char	*path;
	int		fd;
	int		status;
	pid_t	pid;

	fd = 0;
	pid = fork();
	if (pid == 0)
	{
		fd = open(f->files[0], O_RDONLY, 0644);
		if (fd == -1)
			error("Error: Can Not Read the Input File");
		dup2(fd, STDIN_FILENO);
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
			error("Error: Can Not Read the Input File");
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

int	heredoc(t_all *f, char **envp)
{
	int		pip[2];
	int		fd_len[2];
	int		status;
	pid_t	pid;
	char	*deli;

	deli = f->files[0];
	fd_len[1] = ft_strlen(deli);
	if (pipe(pip) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		fd_len[0] = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd_len[0] == -1)
			error("Error: Can Not Read the Input File\n");
		heredocaux(fd_len, f, envp, pip);
	}
	close(pip[1]);
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]);
	waitpid(pid, &status, 0);
	return (0);
}

void	heredocaux(int *fd_len, t_all *f, char **envp, int *pip)
{
	char	*input;
	int		a;

	a = 0;
	while (a == 0)
	{
		input = readline(">");
		if (!ft_strncmp(input, f->files[0], fd_len[1]))
		{
			close(pip[0]);
			close(pip[1]);
			a = 1;
			fd_len[0] = open("/tmp/file1", O_RDONLY, 0644);
			dup2(fd_len[0], STDIN_FILENO);
			if (execve(get_path(f->cmds[0], envp), &f->cmds[0], envp) == -1)
				ft_error("command not found", f->cmds[0]);
		}
		else
		{
			write(fd_len[0], input, ft_strlen(input));
			write(fd_len[0], "\n", 1);
			free(input);
		}
	}
}
