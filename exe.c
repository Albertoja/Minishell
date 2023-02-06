/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:46:32 by magonzal          #+#    #+#             */
/*   Updated: 2023/01/27 12:56:36 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe(t_all *first, char **envp)
{
	if (!first->next->cmds)
	{
		if (!first->dir)
		{
			if (is_builtin(first->cmds[0]) == 1)
				ft_builtins(first, envp);
			else
				execmd(first, envp);
		}
		else
			redirections(first, envp);
	}
	else
	{
		pipex(first, envp);
	}
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
	int		fd;
	char	*path;

	if (first->dir[0] == '1')
	{
		fd = open(first->files[0], O_RDONLY, 0644);
		if (fd == -1)
			error("Error: Can Not Read the Input File");
		dup2(fd, 0);
		path = get_path(first->cmds[0], envp);
		execve(path, &first->cmds[0], envp);
		close(fd);
	}
	else if (first->dir[0] == '2')
	{
		fd = open(first->files[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			error("Error: Can Not Read the Output File");
		dup2(fd, 1);
		path = get_path(first->cmds[0], envp);
		execve(path, &first->cmds[0], envp);
		close(fd);
	}
	else if (first->dir[0] == '3')
	{
		printf("HEREDOC nu lo hice :(");
	}
	else if (first->dir[0] == '4')
	{
		fd = open(first->files[0], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			error("Error: Can Not Read the Input File");
		dup2(fd, STDOUT_FILENO);
		path = get_path(first->cmds[0], envp);
		execve(path, &first->cmds[0], envp);
		close(fd);
	}
}

int	is_builtin(char *command)
{
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
