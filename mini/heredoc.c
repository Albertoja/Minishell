/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:29:16 by magonzal          #+#    #+#             */
/*   Updated: 2023/03/22 19:32:23 by magonzal         ###   ########.fr       */
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
		input = readline(YELLOW">"RESET);
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

static void	ft_writeheredoc(char *limiter, int *pfd)
{
	size_t	len;
	char	*line;

	len = ft_strlen(limiter);
	while (limiter)
	{
		line = readline(YELLOW">"RESET);
		if (!line || g_interactive == 3)
		{
			close(pfd[0]);
			close(pfd[1]);
			g_interactive = 0;
			exit(1);
		}
		if (!ft_strncmp(line, limiter, len))
		{
			close(pfd[0]);
			close(pfd[1]);
			g_interactive = 0;
			exit(0);
		}
		ft_putstr_fd(line, pfd[1]);
		ft_putstr_fd("\n", pfd[1]);
		free(line);
	}
}

void	heredocpip(t_all *head, int i, int out)
{
	int		pfd[2];
	pid_t	pid;

	dup2(out, STDIN_FILENO);
	if (pipe(pfd) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		g_interactive = 2;
		ft_writeheredoc(head->files[i], pfd);
	}
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	wait(NULL);
	signals_handlers();
}
