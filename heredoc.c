/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:29:16 by magonzal          #+#    #+#             */
/*   Updated: 2023/03/06 19:36:56 by mario            ###   ########.fr       */
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


void	heredocpipaux(t_all *a, int out)
{	
	char *l = " ";
	while (l != NULL && ft_strncmp(l, a->files[0], ft_strlen(a->files[0])) != 0)
	{
		l = readline("");
		if (ft_strncmp(l, a->files[0], strlen(a->files[0])) == 0)
		{
			free(l);
			exit(0);
		}
		write(out,">",1);
		write(out, l, ft_strlen(l));
		write(out, "\n", 1);
		free(l);
	}
}


void	heredocpip(t_all *aux, int out)
{
	int fd[2];
	pipe(fd);
	pid_t pid;
	
	pid = fork();
	if (pid == -1)
		ft_error("ERROR: error on Fork", "\n");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		heredocpipaux(aux,out);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

