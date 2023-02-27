/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:46:32 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/27 15:23:15 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe(t_all *first, char **envp, int status)
{
	t_all	*aux;

	aux = first;
	if (first->cmds[0])
	{
		if (!first->next->cmds)
		{
			if (!first->dir)
			{
				if (is_builtin(first->cmds[0]) == 1)
					status = ft_builtins(first, envp, status);
				else
					status = execmd(first, envp);
			}
			else
				status = redirections(first, envp);
		}
		else
			status = pipex(aux, envp);
	}
	return (status);
}

int	execmd(t_all *first, char **envp)
{
	int		pid;
	int		status = 0;
	char	*path;

	path = get_path(first->cmds[0], envp);
	if (!path)
	{
		ft_error("command not found", first->cmds[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
		if (execve(path, &first->cmds[0], envp) == -1)
			ft_error("command not found", first->cmds[0]);
	waitpid(pid, &status, 0);
	return (status);
}

int	redirections(t_all *first, char **envp)
{
	int	status;

	status = 0;
	if (first->dir[0] == '1')
		status = inputredirection(first, envp);
	else if (first->dir[0] == '2')
		status = outputredirection(first, envp);
	else if (first->dir[0] == '3')
		status = heredoc(first, envp);
	else if (first->dir[0] == '4')
		status = outputappendredirection(first, envp);
	return (status);
}

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "exit", 10) == 0)
		return (1);
	if (ft_strncmp(command, "echo", 10) == 0)
		return (1);
	if (ft_strncmp(command, "cd", 10) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 10) == 0)
		return (1);
	if (ft_strncmp(command, "env", 10) == 0)
		return (1);
	if (ft_strncmp(command, "export", 10) == 0)
		return (1);
	if (ft_strncmp(command, "unset", 10) == 0)
		return (1);
	return (0);
}
