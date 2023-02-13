/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:46:32 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/13 18:15:52 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe(t_all *first, char **envp, int status)
{
	if (!first->next->cmds)
	{
		if (!first->dir)
		{
			if (is_builtin(first->cmds[0]) == 1)
				status = ft_builtins(first, envp, status);
			else
				execmd(first, envp);
		}
		else
			redirections(first, envp);
	}
	else
	{
		status = pipex(first, envp, status);
	}
	return(status);
}

void	execmd(t_all *first, char **envp)
{
	int		pid;
	int		status;
	char	*path;

	pid = fork();
	path = get_path(first->cmds[0], envp);
	if (pid == 0)
		if (execve(path, &first->cmds[0], envp) == -1)
			ft_error("command not found", first->cmds[0]);
	waitpid(pid, &status, 0);
}

void	redirections(t_all *first, char **envp)
{
	if (first->dir[0] == '1')
		inputredirection(first, envp);
	else if (first->dir[0] == '2')
		outputredirection(first, envp);
	else if (first->dir[0] == '3')
		heredoc(first,envp);
	else if (first->dir[0] == '4')
		outputappendredirection(first, envp);
}

int	is_builtin(char *command)
{
	if (!command)
		return(0);
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
