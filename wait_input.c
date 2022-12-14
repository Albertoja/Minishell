/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:59 by aespinos          #+#    #+#             */
/*   Updated: 2022/11/28 20:08:14 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_for_input(char **env)
{
	t_all	*head;
	char	**matrix;
	char	*input;

	while (1)
	{
		input = readline(YELLOW"Minishell $>"RESET);
		if (input && *input)
		{
			check_str(input);
			ft_create_history(input);
			matrix = ft_split_pipe(input, '|');
			if (!matrix)
				exit(0);
			free(input);
			head = ft_create_lst(matrix, env);
			env = ft_builtins(head, env);
			ft_lstclear_minishell(&head);
		}
	}
}
