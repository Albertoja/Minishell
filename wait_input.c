/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:59 by aespinos          #+#    #+#             */
/*   Updated: 2023/01/27 11:58:20 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_for_input(char **env, int status, char *homepath)
{
	t_all	*head;
	char	**matrix;
	char	*input;
	int		pip[2];

	status = 0;
	pip[0] = 0;
	pip[1] = 0;
	while (1)
	{
		input = readline(RED"M"BLUE"i"GREEN"n"GRAY"i"PURPLE"s"CYAN"h"WHITE"e"YELLOW"ll"RESET" $>");
		if (input && *input)
		{
			ft_create_history(input,homepath);
			input = check_str(input);
			input = ft_dollar_sust_str(input, env);
			//printf("input------%s\n", input);
			matrix = ft_split_pipe(input, '|');
			if (!matrix)
				exit(0);
			head = ft_create_lst(matrix);
			exe(head,env);
			ft_lstclear_minishell(&head);
		}
		free(input);
	}
}
