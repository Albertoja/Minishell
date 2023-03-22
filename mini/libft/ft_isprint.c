/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:09:45 by aespinos          #+#    #+#             */
/*   Updated: 2022/01/21 13:04:13 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	int	y;
	{
		y = 0;
		if (c >= 32 && c <= 126)
		{
			y = 1;
		}
		return (y);
	}
}
