/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:11:38 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/28 13:45:00 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_equal(char *str, char a)
{
	int	ret;

	ret = 0;
	while (*str != a && *str != '\0')
	{
		ret++;
		str++;
	}
	return (ret);
}

int	ft_comp_var(char *cmds, char **env)
{
	int	len;
	int	ret;

	ret = 0;
	while (env[ret])
	{
		len = ft_len_equal(env[ret], '=');
		if (ft_strncmp(cmds, env[ret], len) == 0)
			return (ret);
		ret++;
	}
	return (-1);
}

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

char	**ft_unset(char **cmds, char **env)
{
	int	cont;
	int	col;

	cont = 1;
	while (cmds[cont])
	{
		col = ft_comp_var(cmds[cont], env);
		if (col >= 0)
			env = ft_delete_str_matrix(env, col);
		cont++;
	}
	return (env);
}
