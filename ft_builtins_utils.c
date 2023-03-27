/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:51:34 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/27 16:22:37 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_tolow(char	*str)
{
	int		cont;
	char	*ret;

	ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	cont = 0;
	while (str[cont])
	{
		ret[cont] = ft_tolower(str[cont]);
		cont++;
	}
	ret[cont] = '\0';
	return (ret);
}
