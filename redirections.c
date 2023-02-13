/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:42:44 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/08 17:31:00 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	outputredirection(t_all *first, char **envp)
{
	char	*path;
	int		fd;

	fd = 0;
	if (fork() == 0)
	{
		fd = open(first->files[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			error("Error: Can Not Read the Output File");
		dup2(fd, STDOUT_FILENO);
		path = get_path(first->cmds[0], envp);
		if (execve(path, &first->cmds[0], envp) == -1)
			ft_error("command not found", first->cmds[0]);
	}
	else
	{
		while (waitpid(-1, NULL, WUNTRACED) == -1)
			close(fd);
	}
}

void	inputredirection(t_all *first, char **envp)
{
	char	*path;
	int		fd;

	fd = 0;
	if (fork() == 0)
	{
		fd = open(first->files[0], O_RDONLY, 0644);
		if (fd == -1)
			error("Error: Can Not Read the Input File");
		dup2(fd, STDIN_FILENO);
		path = get_path(first->cmds[0], envp);
		if (execve(path, &first->cmds[0], envp) == -1)
			ft_error("command not found", first->cmds[0]);
	}
	else
	{
		while (waitpid(-1, NULL, WUNTRACED) == -1)
			close(fd);
	}
}

void	outputappendredirection(t_all *first, char **envp)
{
	char	*path;
	int		fd;

	fd = 0;
	if (fork() == 0)
	{
		fd = open(first->files[0], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
			error("Error: Can Not Read the Input File");
		dup2(fd, STDOUT_FILENO);
		path = get_path(first->cmds[0], envp);
		if (execve(path, &first->cmds[0], envp) == -1)
			ft_error("command not found", first->cmds[0]);
	}
	else
	{
		while (waitpid(-1, NULL, WUNTRACED) == -1)
			close(fd);
	}
}

void	heredoc(t_all *first, char **envp)
{
	int		pip[2];
	int		len;
	char	*delimeter;
	char	*input;
	char	*path;
	pid_t	pid;
	int	fd;

	delimeter = first->files[0];
	len = ft_strlen(delimeter);
	
	if (pipe(pip) == -1)
		exit(1);
	pid = fork();
	if(pid == 0)
	{
		g_interactive = 2;
		fd = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		while(1)
		{
			input = readline(">");
			if (!ft_strncmp(input, delimeter, len))
			{
				close(pip[0]);
				close(pip[1]);
				exit(0);
			}
			write(fd, input, ft_strlen(input));
			write(fd,"\n", 1);
			free(input);
		}
		path = get_path(first->cmds[0], envp);

	}
	close(pip[1]);
	dup2(pip[0], STDIN_FILENO);
	close(pip[0]);
	waitpid(pid, NULL, 0);
	
}
