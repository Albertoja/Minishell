/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:13:02 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/13 18:16:10 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex(t_all *head, char **envp, int status)
{
	t_all	*first = head;
	t_all	*second = head->next;
	int		pip[2];
	pid_t	slave1;
	pid_t	slave2;

	if(first->next->cmds)
		first->next->cmds = NULL;
	pipe(pip);
	slave1 = fork();					//doubles forks when going again on exe
	if(slave1 < 0)
		error("Errror: Fork of slave 1");
	else if(slave1 == 0)
	{
		dup2(pip[1], 1);
		close(pip[0]);
		exe(first, envp, status);
	}
	slave2 = fork();					//doubles forks when going again on exe
	if(slave2 < 0)
		error("Errror: Fork of slave 2");
	else if(slave2 == 0)
	{
		dup2(pip[0], 0);
		close(pip[1]);
		exe(second, envp, status);
	}
	close(pip[0]);
	close(pip[1]);
	waitpid(slave1, NULL, 0);
	waitpid(slave2, NULL, 0);
	return(status);
}
