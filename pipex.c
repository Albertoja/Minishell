/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:13:02 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/27 15:04:52 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	select_redirection_pipex(t_all *aux)
{
	int	fd;

	if (aux->dir)
	{
		if (aux->dir[0] == '2')
		{
			fd = open(aux->files[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (aux->dir[0] == '1')
		{
			fd = open(aux->files[0], O_RDONLY, 0644);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (aux->dir[0] == '4')
		{
			fd = open(aux->files[0], O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
}

int	pipex(t_all *aux, char **envp)
{
	int		pip[2];
	int		fd_in_out[2];
	int		status;
	int		cmdnbr[2];
	pid_t	pid;

	fd_in_out[0] = dup(STDIN_FILENO);
	fd_in_out[1] = dup(STDOUT_FILENO);
	cmdnbr[1] = ft_lstsize(aux) - 1;
	cmdnbr[0] = 1;
	while (aux && cmdnbr[0] <= cmdnbr[1])
	{
		pipe(pip);
		pid = fork();
		if (pid == -1)
			ft_error("ERROR: error on Fork", "\n");
		if (pid == 0)
		{
			close(pip[0]);
			dup2(fd_in_out[0], STDIN_FILENO);
			dup2(pip[1], STDOUT_FILENO);
			close(pip[1]);
			if (cmdnbr[0] == cmdnbr[1])
			{
				dup2(pip[0], STDIN_FILENO);
				dup2(fd_in_out[1], STDOUT_FILENO);
			}
			if (is_builtin(aux->cmds[0]) == 1)
			{
				if (cmdnbr[0] != cmdnbr[1])
					dup2(pip[1], STDOUT_FILENO);
				ft_builtins(aux, envp, status);
			}
			else
			{
				select_redirection_pipex(aux);
				if (execve(get_path(aux->cmds[0], envp), aux->cmds, envp) == -1)
					ft_error("EPX : command not found", aux->cmds[0]);
			}
			exit(0);
		}
		else
		{
			close(pip[1]);
			waitpid(pid, &status, 0);
			close(fd_in_out[0]);
			fd_in_out[0] = pip[0];
			aux = aux->next;
		}
		cmdnbr[0]++;
	}
	close(pip[1]);
	close(pip[0]);
	dup2(dup(STDOUT_FILENO), STDOUT_FILENO);
	return (0);
}
