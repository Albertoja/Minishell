/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:08:42 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/25 12:40:23 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_all *lst)
{
	int	cont;

	cont = 0;
	while (lst)
	{
		lst = lst->next;
		cont++;
	}
	return (cont);
}
