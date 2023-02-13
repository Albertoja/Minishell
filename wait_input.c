/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:59 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/13 19:17:31 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_for_input(char **env, int status, char *homepath)
{
	t_all	*head;
	int		std[2];
	char	**matrix;
	char	*input;

	status = 0;
	while (1)
	{
		g_interactive = 1;
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
		input = readline(RED"M"BLUE"i"GREEN"n"GRAY"i"PURPLE"s"CYAN"h"WHITE"e"YELLOW"ll"RESET" $>");
		g_interactive = 0;
		if (!input)
		{
			status = 1;
			if (g_interactive != 3)
			{
				ft_putstr_fd("exit\n", 1);
				exit(1);
			}
			if (g_interactive == 3)
				input = ft_strdup("");
			g_interactive = 1;
		}
		printf("g = %i\n", g_interactive);
		ft_create_history(input,homepath);
		input = check_str(input);
		if (!input)
			status = 1;
		if (input && input[0])
		{
			input = ft_dollar_sust_str(input, env, status);
			matrix = ft_split_pipe(input, '|');
			if (!matrix)
				exit(0);
			head = ft_create_lst(matrix);
			exe(head, env, status);
			dup2(STDIN_FILENO, std[0]);
			dup2(STDOUT_FILENO, std[1]);
			status = 0;
			ft_lstclear_minishell(&head);
		}
		free(input);
	}
}
