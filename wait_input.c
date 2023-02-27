/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:59 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/27 18:23:00 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_input_signal(void)
{
	ft_putstr_fd("exita\n", 1);
	exit(1);
}

char	**start_mini(char *input, int *status, char **env)
{
	char	**matrix;
	t_all	*head;

	input = ft_dollar_sust_str(input, env, status);
	matrix = ft_split_pipe(input, '|');
	if (!matrix)
		exit(0);
	head = ft_create_lst(matrix);
	env = exe(head, env, status);
	//printf("ESTATUS FINAL = %d\n", *status);
	free(input);
	ft_lstclear_minishell(&head);
	return (env);
}

void	ft_wait_for_input(char **env, char *homepath)
{
	int			std[2];
	char		*input;
	int			status[1];

	*status = 0;
	while (1)
	{
		g_interactive = 1;
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
		input = readline(RED"M"BLUE"i"GREEN"n"GRAY"i"PURPLE"s"
				CYAN"h"WHITE"e"YELLOW"ll"RESET" $>");
		g_interactive = 0;
		printf("input = %s\n", input);
		printf("status = %i\n", *status);
		if (!input)
			no_input_signal();
		ft_create_history(input, homepath);
		input = check_str(input);
		if (!input)
			*status = 1;
		if (input && input[0])
			env = start_mini(input, status, env);
		dup2(STDIN_FILENO, std[0]);
		dup2(STDOUT_FILENO, std[1]);
	}
}
