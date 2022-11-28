/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:50 by aespinos          #+#    #+#             */
/*   Updated: 2022/11/28 20:13:22 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    leaks(void)
{
    system("leaks minishell");
}

int	count_str(char **matrix)
{
	int	ret;

	ret = 0;
	while (matrix[ret])
		ret++;
	return (ret);
}

char	**copy_matrix(char **matrix)
{
	char	**env;
	char	**ret;

	if (!matrix)
		return (NULL);
	env = malloc(sizeof(char *) * (count_str(matrix) + 1));
	if (!env)
		return (NULL);
	ret = env;
	while (*matrix)
		*env++ = ft_strdup(*matrix++);
	*env = NULL;
	return (ret);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**env;

	atexit(leaks);
	if (argc != 1 || argv[1] || !envp)
		return (0);
	env = copy_matrix(envp);
	ft_read_history();
	ft_wait_for_input(env);
	ft_free_matrix(env);
}
