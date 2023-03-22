/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexredirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:29:32 by magonzal          #+#    #+#             */
/*   Updated: 2023/03/15 17:00:58 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipexinputredirection(t_all *aux, int i)
{
	int	fd;

	fd = open(aux->files[i], O_RDONLY, 0644);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	pipexoutpuredirection(t_all *aux, int i)
{
	int	fd;

	fd = open(aux->files[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	pipexappendredirection(t_all *aux, int i)
{
	int	fd;

	fd = open(aux->files[i], O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
