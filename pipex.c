/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:13:02 by magonzal          #+#    #+#             */
/*   Updated: 2023/03/02 18:07:10 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	select_redirection_pipex(t_all *aux, int out)
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
		else if (aux->dir[0] == '3')
			heredocpip(aux, out);
	}
}

void	declare(t_all *aux, int *in_out_all_act, int status)
{
	in_out_all_act[0] = dup(STDIN_FILENO);
	in_out_all_act[1] = dup(STDOUT_FILENO);
	in_out_all_act[2] = ft_lstsize(aux) - 1;
	in_out_all_act[3] = 1;
	in_out_all_act[4] = status;
}

void	pipex2(t_all *aux, char **envp, int *pip, int *in_out_all_act)
{
	close(pip[0]);
	dup2(in_out_all_act[0], STDIN_FILENO);
	dup2(pip[1], STDOUT_FILENO);
	close(pip[1]);
	if (in_out_all_act[3] == in_out_all_act[2] )
	{
		dup2(pip[0], STDIN_FILENO);
		dup2(in_out_all_act[1], STDOUT_FILENO);
	}
	if (is_builtin(aux->cmds[0]) == 1)
	{
		if (in_out_all_act[3] != in_out_all_act[2])
			dup2(pip[1], STDOUT_FILENO);
		ft_builtins(aux, envp, &in_out_all_act[4]);
	}
	else
	{
		select_redirection_pipex(aux, in_out_all_act[1]);
		if (execve(get_path(aux->cmds[0], envp), aux->cmds, envp) == -1)
			ft_error("EPX : command not found", aux->cmds[0]);
	}
	exit(0);
}

void	closepip(int *pip)
{
	close(pip[1]);
	close(pip[0]);
	dup2(dup(STDOUT_FILENO), STDOUT_FILENO);
}

void	pipex(t_all *aux, char **envp, int *status)
{
	int		pip[2];
	int		in_out_all_act[5];
	pid_t	pid;

	declare(aux, in_out_all_act, *status);
	while (aux && in_out_all_act[3] <= in_out_all_act[2])
	{
		pipe(pip);
		pid = fork();
		if (pid == -1)
			ft_error("ERROR: error on Fork", "\n");
		if (pid == 0)
			pipex2(aux, envp, pip, in_out_all_act);
		else
		{
			close(pip[1]);
			waitpid(pid, &in_out_all_act[4], 0);
			close(in_out_all_act[0]);
			in_out_all_act[0] = pip[0];
			aux = aux->next;
		}
		in_out_all_act[3]++;
	}
	closepip(pip);
	status = &in_out_all_act[4];
}
