/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endpipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:21:46 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/06 14:57:12 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*error_endpipe(void)
{
	printf("minishell: syntax error: unexpected end of file\n");
	return (ft_strdup(""));
}

char	*ft_endpipe(char *oldinput)
{
	char	*input;
	int		i;

	i = 0;
	g_interactive = 2;
	while (1)
	{
		input = readline(YELLOW">"RESET);
		if (!input)
		{
			free(oldinput);
			if (g_interactive == 2)
				return (error_endpipe());
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
	printf("old = %s\n", oldinput);
	return (oldinput);
}
