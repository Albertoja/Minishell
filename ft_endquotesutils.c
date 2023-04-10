/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endquotesutils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:48:40 by aespinos          #+#    #+#             */
/*   Updated: 2023/04/04 20:48:59 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quote(char *input, char a)
{
	int	cont;
	int	ret;

	cont = -1;
	ret = 0;
	while (input[++cont])
	{
		if (input[cont] == a)
		{
			if (ret == 0)
				ret = 1;
			else if (ret == 1)
				ret = 0;
		}
	}
	return (ret);
}
