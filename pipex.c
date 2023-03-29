/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:13:02 by magonzal          #+#    #+#             */
/*   Updated: 2023/03/27 15:20:49 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	select_redirection_pipex(t_all *aux, int *pip, int *out)
{
	int	i;

	i = -1;
	while (aux->files && aux->files[++i])
	{
		if (aux->dir[i] == '2')
			pipexoutpuredirection(aux, i);
		else if (aux->dir[i] == '1')
			pipexinputredirection(aux, i);
		else if (aux->dir[i] == '4')
			pipexappendredirection(aux, i);
		else if (aux->dir[i] == '3')
			ft_readheredoc(aux, i, out[0]);
	}
	if (aux->next != NULL && (!ft_strchr(aux->dir, '2')
			&& !ft_strchr(aux->dir, '4')))
		dup2(pip[1], STDOUT_FILENO);
	else if (!ft_strchr(aux->dir, '2')
		&& !ft_strchr(aux->dir, '4'))
		dup2(out[0], STDOUT_FILENO);
}

void	childprocess(t_all *aux, char **envp, int *status, int *pip)
{
	int	out[2];

	out[0] = dup(STDOUT_FILENO);
	out[1] = dup(STDIN_FILENO);
	select_redirection_pipex(aux, pip, out);
	close(pip[0]);
	close(pip[1]);
	if (is_builtin(aux->cmds[0]) == 1)
	{
		ft_builtins(aux, envp, status);
		exit(0);
	}
	if (execve(get_path(aux->cmds[0], envp), aux->cmds, envp) == -1)
	{
		ft_error("EPX command not found", aux->cmds[0]);
		exit(127);
	}
}

void	pipex(t_all *head, char **envp, int *status)
{
	int		pip[2];
	t_all	*aux;
	pid_t	pid;
	int		cmd_nbr;

	cmd_nbr = 0;
	aux = head;
	pid = 0;
	while (aux)
	{
		pipe(pip);
		pid = fork();
		if (pid == -1)
			ft_error("ERROR: error on Fork", "\n");
		if (pid == 0)
			childprocess(aux, envp, status, pip);
		if (aux->next != NULL)
			dup2(pip[0], STDIN_FILENO);
		close(pip[0]);
		close(pip[1]);
		aux = aux->next;
	}
	close(STDIN_FILENO);
	while (waitpid(-1, NULL, WUNTRACED) != -1)
		cmd_nbr++;
}
