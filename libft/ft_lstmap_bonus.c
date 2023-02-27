/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:17:57 by aespinos          #+#    #+#             */
/*   Updated: 2022/02/06 20:42:12 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*old;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	new = 0;
	while (lst)
	{
		old = ft_lstnew(f(lst->content));
		if (!old)
		{	
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, old);
		lst = lst->next;
	}
	return (new);
}
