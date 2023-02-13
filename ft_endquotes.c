/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endquotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:52:36 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/13 17:10:15 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*search_first_cmd(char *input)
{
	int		a;
	char	*cmd;

	a = 0;
	while (input[a] != ' ')
		a++;
	cmd = malloc(sizeof(char) * (a + 1));
	a = 0;
	while (input[a] != ' ')
	{
		cmd[a] = input[a];
		a++;
	}
	return (cmd);
}

char	*sust_a(char *input, char a)
{
	char	*aux;
	int		i;
	int		j;

	aux = malloc(sizeof(char) * (ft_strlen(input) + 1));
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == a)
			i++;
		else
		{
			aux[j] = input[i];
			i++;
			j++;
		}
	}
	aux[j] = a;
	j++;
	aux[j] = '\0';
	free(input);
	return (aux);
}

char	*search_a(char	*input, char a)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == a)
		{
			input = sust_a(input, a);
			return (input);
		}
		i++;
	}
	return (input);
}

char	*ft_endquotes(char *oldinput, char a)
{
	char	*input;
	int		i;

	i = 0;
	g_interactive = 2;
	while (1)
	{
		input = readline(YELLOW">"RESET);
		if(!input)
		{
			if (g_interactive == 2)
			{
				printf("> minishell: unexpected EOF while looking for matching `\"'\n");
				printf("minishell: syntax error: unexpected end of file\n");
				return (ft_strdup(""));
			}
			if (g_interactive == 3)
				return (ft_strdup(""));
		}
		if (input && *input)
		{
			input = search_a(input, a);
			oldinput = ft_strjoin(oldinput, " \n");
			oldinput = ft_strjoin(oldinput, input);
			while (input[i])
				i++;
			if (input[i - 1] == a)
				break ;
			else
				i = 0;
		}
		else
			oldinput = ft_strjoin(oldinput, "\n");
	}
	free(input);
	return (oldinput);
}
