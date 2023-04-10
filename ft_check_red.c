/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:26:57 by aespinos          #+#    #+#             */
/*   Updated: 2023/04/04 20:22:42 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_error_red(char *str)
{
	free(str);
	printf("minishell: syntax error near unexpected token\n");
	return (NULL);
}

int	ft_jump(char *str, int cont)
{
	char	aux;
	int		auxcont;

	auxcont = cont;
	aux = str[cont];
	cont++;
	while (str[cont])
	{
		if (str[cont] == aux)
			return (cont);
		cont++;
	}
	return (cont);
}

int	ft_check_any_after(char *str)
{
	int		cont;
	char	aux;

	cont = -1;
	while (str[++cont])
	{
		if (str[cont] == '"' || str[cont] == '\'')
			cont = ft_jump(str, cont);
		if (!str[cont])
			break ;
		if (str[cont] == '>' || str[cont] == '<')
		{
			aux = str[cont];
			if (str[cont + 1] && aux == str[cont + 1])
				cont++;
			while (str[cont++])
			{
				if (str[cont] == '>' || str[cont] == '<' || str[cont] == '\0')
					return (1);
				if (str[cont] != ' ')
					break ;
			}
		}
	}
	return (0);
}

int	ft_check_have_red(char *str)
{
	int	cont;

	cont = -1;
	while (str[++cont])
	{
		if (str[cont] == '"' || str[cont] == '\'')
			cont = ft_jump(str, cont);
		if (!str[cont])
			break ;
		if (str[cont] == '>' || str[cont] == '<')
			return (0);
	}
	return (1);
}

char	*ft_check_red(char *str)
{
	int	check;

	check = 0;
	if (!str || !(*str))
		return (str);
	if (ft_check_have_red(str) == 1)
		return (str);
	if (ft_check_any_after(str) == 1)
		return (ft_error_red(str));
	return (str);
}
