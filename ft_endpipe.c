/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endpipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:21:46 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/25 20:02:47 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_endpipe(char *oldinput)
{
	char	*input;

	g_interactive = 2;
	while (1)
	{
		input = readline(YELLOW">"RESET);
		if (!input)
		{
			if (g_interactive == 2)
			{
				printf("> minishell: unexpected EOF \n");
				printf("minishell: syntax error: unexpected end of file\n");
				return (ft_strdup(""));
			}
			if (g_interactive == 3)
				return (ft_strdup(""));
		}
		if (input && *input)
		{
			input = ft_strdup(input);
			oldinput = ft_strjoin(oldinput, input);
			free(input);
			return (oldinput);
		}
	}
	free(input);
	return (oldinput);
}
