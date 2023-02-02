/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:11:38 by aespinos          #+#    #+#             */
/*   Updated: 2023/01/27 12:01:04 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_delete_str_matrix(char **matrix, int col)
{
	char	**env;
	char	**ret;

	if (!matrix)
		return (NULL);
	env = malloc(sizeof(char *) * (count_str(matrix)));
	if (!env)
		return (NULL);
	ret = env;
	while (*matrix)
	{
		if (col == 0)
			matrix++;
		if (*matrix)
			*env++ = ft_strdup(*matrix++);
		col--;
	}
	*env = NULL;
	return (ret);
}

void	ft_unset(char **cmds, char **env)
{
	int	cont;
	int	col;

	cont = 1;
	while (cmds[cont])
	{
		col = ft_comp_var(cmds[cont], env);
		printf("aqui! %i", col);
		if (col >= 0)
			env = ft_delete_str_matrix(env, col);
		cont++;
		write(1, "a\n", 2);
	}
}
