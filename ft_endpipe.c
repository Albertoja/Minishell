/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endpipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:21:46 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/15 19:05:43 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


char	*ft_endpipe(char *oldinput)
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
			input = ft_strdup(input);
			oldinput = ft_strjoin(oldinput, input);
			free(input);
			return(oldinput);
		}
	}
	free(input);
	return (oldinput);
}
