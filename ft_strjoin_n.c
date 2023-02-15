/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:36:07 by aespinos          #+#    #+#             */
/*   Updated: 2023/01/19 19:36:08 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_strjoin_n(char *str1, char *str2, int n)
{
	int		cont;
	char	*ret;
	char	*aux;

	cont = 0;
	aux = malloc(sizeof(char) * (n + 1));
	while (n--)
	{
		aux[cont] = str2[cont];
		cont++;
	}
	aux[cont] = '\0';
	if (!str1)
		return (aux);
	ret = ft_strjoin(str1, aux);
	free (aux);
	return (ret);
}
