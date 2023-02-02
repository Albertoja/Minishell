/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:13:02 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/02 13:35:55 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_all *head, char **envp)
{
	t_all	*first = head;
	t_all	*second = head->next;
	int		pip[2];
	pid_t	slave1;
	pid_t	slave2;

	if(first->next != NULL)
		first->next->cmds = NULL;
	pipe(pip);
	slave1 = fork();
	if(slave1 < 0)
		error("Errror: Fork of slave 1");
	else if(slave1 == 0)
		ft_slave1(first,pip, envp);
	slave2 = fork();
	if(slave2 < 0)
		error("Errror: Fork of slave 2");
	else if(slave2 == 0)
		ft_slave2(second,pip, envp);
	close(pip[0]);
	close(pip[1]);
	waitpid(slave1, NULL, 0);
	waitpid(slave2, NULL, 0);
	
}

void	ft_slave1(t_all *head, int pip[2], char *envp[])
{
	char	**cmd;
	char	*path;
	int		fd;

	fd = open(head->files[0], O_RDONLY, 0644);
	dup2(pip[1], 1);
	close(pip[0]);
	dup2(fd, 0);
	cmd = ft_split(*head->cmds, ' ');
	path = get_path(cmd[0], envp);
	if (fd == -1)
		error("Error: Can Not Read the Input File\n");
	if (execve(path, cmd, envp) == -1)
		error("ERROR: BAD EXECVE 1\n");
}

void	ft_slave2(t_all *head, int pip[2], char *envp[])
{
	char	**cmd;
	char	*path;
	int		fd;

	fd = open(head->files[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(pip[0], 0);
	close(pip[1]);
	dup2(fd, 1);
	cmd = ft_split(*head->cmds, ' ');
	path = get_path(cmd[0], envp);
	printf("%s", path);
	if (fd == -1)
		error("Error: Can Not Read the Output File\n");
	if (execve(path, cmd, envp) == -1)
		error("ERROR: BAD EXECVE 2\n");
}