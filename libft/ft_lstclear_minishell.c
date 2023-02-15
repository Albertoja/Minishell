/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_minishell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:52:56 by aespinos          #+#    #+#             */
/*   Updated: 2023/01/23 18:04:57 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_minishell(t_all **lst)
{
	t_all	*temp;

	if (!*lst)
		return ;
	temp = *lst;
	*lst = NULL;
	while (temp)
	{
		if (temp->cmds)
			ft_free_matrix(temp->cmds);
		if (temp->files)
			ft_free_matrix(temp->files);
		if (temp->dir)
			free(temp->dir);
		free(temp);
		temp = temp->next;
	}
}
