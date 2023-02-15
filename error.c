/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:46 by aespinos          #+#    #+#             */
/*   Updated: 2023/01/12 15:49:11 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str, char *straux)
{
	printf("minishell: %s: %s\n", straux, str);
}

void	hello_norminette(char **str, char const *s, int **i, int *a)
{
	char	aux;

	if (s[*a] == 34 || s[*a] == 39)
	{
		aux = s[*a];
		str[(*i)[0]][((*i)[1])++] = s[*a];
		(*a)++;
		while (s[*a] != aux)
		{
			str[(*i)[0]][((*i)[1])++] = s[*a];
			(*a)++;
		}
	}
	str[(*i)[0]][((*i)[1])++] = s[*a];
	(*a)++;
}
