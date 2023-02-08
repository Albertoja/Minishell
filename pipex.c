/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:13:02 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/06 18:04:37 by magonzal         ###   ########.fr       */
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
		exe(first, envp);
	}
	slave2 = fork();					//doubles forks when going again on exe
	if(slave2 < 0)
		error("Errror: Fork of slave 2");
	else if(slave2 == 0)
	{
		dup2(pip[0], 0);
		close(pip[1]);
		exe(second, envp);
	}
	close(pip[0]);
	close(pip[1]);
	waitpid(slave1, NULL, 0);
	waitpid(slave2, NULL, 0);
	
}
