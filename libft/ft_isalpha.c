/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:08:52 by aespinos          #+#    #+#             */
/*   Updated: 2022/01/20 16:08:52 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	int	y;
	{
		y = 0;
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		{
			y = 1;
		}
		return (y);
	}
}
