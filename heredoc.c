/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:29:16 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/28 17:30:12 by aespinos         ###   ########.fr       */
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
		g_interactive = 2;
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

void	heredocauxpip(int *fd_len, t_all *f, int *in_out_all_act, int *pip)
{
	char	*input;
	int		a;

	a = 0;
	while (a == 0)
	{
		dup2(in_out_all_act[1], STDOUT_FILENO);
		dup2(pip[1],STDOUT_FILENO);
		close(pip[1]);
		input = readline(">");
		if (!ft_strncmp(input, f->files[0], fd_len[1]))
		{
			a = 1;
			fd_len[0] = open("/tmp/file1", O_RDONLY, 0644);
			dup2(fd_len[0], STDIN_FILENO);
		}
		else
		{
			//printf(">%s\n",input);
			write(fd_len[0], input, ft_strlen(input));
			write(fd_len[0], "\n", 1);
			free(input);
		}
	}
}

void	heredocpip(t_all *f, int *in_out_all_act, int *pip)
{
	int		fd_len[2];
	char	*deli;

	deli = f->files[0];
	fd_len[1] = ft_strlen(deli);
	fd_len[0] = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd_len[0] == -1)
		printf("Error: Can Not Read the Input File");
	heredocauxpip(fd_len, f, in_out_all_act,pip);
	
}
