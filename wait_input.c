/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:59 by aespinos          #+#    #+#             */
/*   Updated: 2022/10/25 17:26:14 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_for_input(void)
{
	t_all	*head;
	char	**matrix;
	char	*input;

	while (1)
	{
		input = readline(YELLOW"Minishell $>"RESET);
		if (!input)
			exit(0);
		ft_create_history(input);
		check_str(input);
		matrix = ft_split_pipe(input, '|');
		if (!matrix)
			exit(0);
		free(input);
		head = ft_create_lst(matrix);
		ft_lstclear_minishell(&head);
	}
}
