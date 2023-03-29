/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:46:32 by magonzal          #+#    #+#             */
/*   Updated: 2023/03/29 17:45:36 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**exe(t_all *first, char **envp, int *status)
{
	t_all	*aux;

	aux = first;
	if (!first->dir && !first->next)
	{
		if (is_builtin(first->cmds[0]) == 1)
			envp = ft_builtins(first, envp, status);
		else
			execmd(first, envp, status);
	}
	else
		pipex(aux, envp, status);
	return (envp);
}

int	checkaccess(t_all *first, char	*path)
{
	if (access(first->cmds[0], 0) == 0)
	{
		path = first->cmds[0];
		return (0);
	}
	return (1);
}

void	execmd(t_all *first, char **envp, int *status)
{
	pid_t	pid;
	int		i;
	char	*path;

	path = NULL;
	i = checkaccess(first, path);
	path = get_path(first->cmds[0], envp);
	if (!path)
	{
		ft_error("path not found", first->cmds[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, &first->cmds[0], envp) == -1)
		{
			ft_error("command not found", first->cmds[0]);
			*status = 127;
			exit(127);
		}
	}
	waitpid(pid, status, 0);
	if (i != 0)
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
	char	*aux;
	int		ret;

	ret = 0;
	aux = ft_tolow(command);
	if (!aux)
		return (1);
	if (ft_strncmp(aux, "exit", 10) == 0)
		ret = 1;
	if (ft_strncmp(aux, "echo", 10) == 0)
		ret = 1;
	if (ft_strncmp(aux, "cd", 10) == 0)
		ret = 1;
	if (ft_strncmp(aux, "pwd", 10) == 0)
		ret = 1;
	if (ft_strncmp(aux, "env", 10) == 0)
		ret = 1;
	if (ft_strncmp(aux, "export", 10) == 0)
		ret = 1;
	if (ft_strncmp(aux, "unset", 10) == 0)
		ret = 1;
	free(aux);
	return (ret);
}
