/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endpipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:21:46 by aespinos          #+#    #+#             */
/*   Updated: 2023/04/10 16:12:13 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*error_endpipe(void)
{
	printf("minishell: syntax error: unexpected end of file\n");
	return (NULL);
	return (ft_strdup(""));
}

char	*ft_endpipe2(char *oldinput, char *input)
{
	free(oldinput);
	free(input);
	if (g_interactive == 2)
		return (error_endpipe());
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
			return (ft_endpipe2(oldinput, input));
		if (input && *input)
		{
			oldinput = ft_strjoin(oldinput, input);
			oldinput = check_str(oldinput);
			free(input);
			return (oldinput);
		}
		free(input);
	}
	free(input);
	oldinput = check_str(oldinput);
	return (oldinput);
}
