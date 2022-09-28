/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:41:16 by aespinos          #+#    #+#             */
/*   Updated: 2022/06/22 18:41:04 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*a;

	if (lst || new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		a = ft_lstlast(*lst);
		a->next = new;
	}
	else
		return ;
}
