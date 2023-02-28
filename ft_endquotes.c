/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endquotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:52:36 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/28 19:36:03 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

char	*error_endquotes(void)
{
	if (g_interactive == 2)
	{
		printf("> minishell: ");
		printf("unexpected EOF while looking for matching `\"'\n");
		printf("minishell: syntax error: unexpected end of file\n");
	}
	return (ft_strdup(""));
}

char	*ft_endquotes2(char *input, char *oldinput)
{
	oldinput = ft_strjoin(oldinput, " \n");
	oldinput = ft_strjoin(oldinput, input);
	return (oldinput);
}

char	*ft_endquotes(char *oldinput, char a)
{
	char		*input;
	static int	i;

	while (1)
	{
		g_interactive = 2;
		input = readline(YELLOW">"RESET);
		if (!input)
			return (error_endquotes());
		if (input && *input)
		{
			input = search_a(input, a);
			oldinput = ft_endquotes2(input, oldinput);
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
