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

void	pipex(t_all *head, char **envp, int *pip)
{
	t_all	*first = head;
	t_all	*second = head->next;
	pid_t	slave1;
	pid_t	slave2;

	pipe(pip);
	slave1 = fork();
	if(slave1 < 0)
		error("Errror: Fork of slave 1\n");
	else if(slave1 == 0)
		exe(first, envp, pip);
	slave2 = fork();
	if(slave2 < 0)
		error("Errror: Fork of slave 2\n");
	else if(slave2 == 0)
		exe(second, envp, pip);
	close(pip[0]);
	close(pip[1]);
	waitpid(slave1, NULL, 0);
	waitpid(slave2, NULL, 0);
	
}