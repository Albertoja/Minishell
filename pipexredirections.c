/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexredirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:29:32 by magonzal          #+#    #+#             */
/*   Updated: 2023/03/23 20:32:30 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipexinputredirection(t_all *aux, int i)
{
	int	fd;

	fd = open(aux->files[i], O_RDONLY, 0644);
	if(fd == -1)
	{
		ft_error("could not open file", aux->files[i]);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	pipexoutpuredirection(t_all *aux, int i)
{
	int	fd;

	fd = open(aux->files[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(fd == -1)
	{
		ft_error("could not open file", aux->files[i]);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	pipexappendredirection(t_all *aux, int i)
{
	int	fd;

	fd = open(aux->files[i], O_RDWR | O_CREAT | O_APPEND, 0644);
	if(fd == -1)
	{
		ft_error("could not open file", aux->files[i]);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
