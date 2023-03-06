/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:46:32 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/28 17:42:21 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**exe(t_all *first, char **envp, int *status)
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
					envp = ft_builtins(first, envp, status);
				else
					execmd(first, envp, status);
			}
			else
				redirections(first, envp, status);
		}
		else
			pipex(aux, envp, status);
	}
	return (envp);
}

void	execmd(t_all *first, char **envp, int *status)
{
	int		pid;
	char	*path;

	path = get_path(first->cmds[0], envp);
	if (!path)
	{
		ft_error("comand not found", first->cmds[0]);
		*status = 127;
	}
	else
	{
		pid = fork();
		if (pid == 0)
			if (execve(path, &first->cmds[0], envp) == -1)
				ft_error("command not found", first->cmds[0]);
		waitpid(pid, status, 0);
	}
	free(path);
}

void	redirections(t_all *first, char **envp, int *status)
{
	if (first->dir[0] == '1')
		inputredirection(first, envp, status);
	else if (first->dir[0] == '2')
		outputredirection(first, envp, status);
	else if (first->dir[0] == '3')
		heredoc(first, envp, status);
	else if (first->dir[0] == '4')
		*status = outputappendredirection(first, envp);
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
