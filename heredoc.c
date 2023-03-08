/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:29:16 by magonzal          #+#    #+#             */
/*   Updated: 2023/03/07 19:07:53 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_all *f, char **envp, int *status)
{
	int		pip[2];
	int		fd_len[2];
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
			printf("Error: Can Not Read the Input File");
		heredocaux(fd_len, f, envp, pip);
	}
	else
		while (waitpid(-1, NULL, WUNTRACED) == -1)
			close(fd_len[0]);
	waitpid(pid, status, 0);
	close(pip[0]);
	close(pip[1]);
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

void	heredocpipaux(t_all *a, int fd)
{
	char	*l;

	while (ft_strncmp(l, a->files[0], ft_strlen(a->files[0])) != 0)
	{
		l = readline(">");
		if (ft_strncmp(l, a->files[0], strlen(a->files[0])) == 0)
		{
			free(l);
			exit(0);
		}
		ft_putstr_fd(l, fd);
		ft_putstr_fd("\n", fd);
		free(l);
	}
}

void	heredocpip(t_all *aux, int out)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		ft_error("ERROR: error on Fork", "\n");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(out, STDOUT_FILENO);
		close(out);
		heredocpipaux(aux, fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
