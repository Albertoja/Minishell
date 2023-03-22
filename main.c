/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:50 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/22 19:11:34 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	leaks(void)
// {
// 	system("leaks minishell");
// }

int	g_interactive = 0;

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

void	ft_shlvl(char **env)
{
	char	*shlvl;
	char	*sub;
	int		nbr;

	if (!env || !*env)
		return ;
	while (ft_strncmp(*env, "SHLVL=", 6))
		env++;
	sub = ft_substr(*env, 6, UINT_MAX);
	nbr = ft_atoi(sub) + 1;
	free(sub);
	sub = ft_itoa(nbr);
	shlvl = ft_strjoinm("SHLVL=", sub);
	free(sub);
	free(*env);
	*env = shlvl;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**env;

	//atexit(leaks);
	if (argc != 1 || argv[1] || !envp)
		return (0);
	env = copy_matrix(envp);
	ft_shlvl(env);
	ft_read_history(env);
	no_ctrlprint();
	signals_handlers();
	ft_wait_for_input(env);
	ft_free_matrix(env);
}
