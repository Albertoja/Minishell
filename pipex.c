/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:13:02 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/15 18:46:59 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	selectredirectionpipex(t_all *aux);

int		pipex(t_all *head, char **envp)
{
	t_all	*aux;
	pid_t	pid;
	int		pip[2];
	int		status;
	int		fd;

	fd = 0;
	aux = head;
	while (aux && aux->next != NULL)
	{
		pipe(pip);
		if ((pid = fork()) == -1)
			ft_error("ERROR: error on Fork","\n");
		else if (pid == 0)
		{
			dup2(fd, 0);
			if (aux->next)
				dup2(pip[1], 1);
			selectredirectionpipex(aux);
			if (execve(get_path(aux->cmds[0], envp), &aux->cmds[0], envp) == -1)
				ft_error("EPX : command not found", aux->cmds[0]);
			exit(0);
			return (127);
		}
		else
		{
			wait(&status);
			close(pip[1]);
			fd = pip[0];
			aux = aux->next;
		}
	}
	return(status);
}

void	selectredirectionpipex(t_all *aux)
{
	int fd;
	
	if (aux->dir)
	{
		if (aux->dir[0] == '2')
		{
			fd = open(aux->files[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(fd, 1);
			close(fd);
		}
		else if(aux->dir[0] == '1')
		{
			fd = open(aux->files[0], O_RDONLY, 0644);
			dup2(fd, 0);
			close(fd);
		}
		else if(aux->dir[0] == '4')
		{
			fd = open(aux->files[0], O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(fd, 1);
			close(fd);
		}
	}
}