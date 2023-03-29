/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:11:38 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/28 18:03:07 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset_var(char *cmds, int *status)
{
	int	cont;

	cont = 0;
	while (cmds[cont])
	{
		if ((cmds[cont] >= 'a' && cmds[cont] <= 'z')
			|| (cmds[cont] >= 'A' && cmds[cont] <= 'Z') || cmds[cont] == '_')
			cont++;
		else
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cmds);
			*status = 1;
			return (1);
		}
	}
	return (0);
}

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
	if (!env)
		return (-1);
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

char	**ft_unset(char **cmds, char **env, int *status)
{
	int		cont;
	int		col;
	char	**new_env;
	int		flag;

	flag = 0;
	*status = 0;
	cont = 1;
	while (cmds[cont])
	{
		if (ft_unset_var(cmds[cont], status) == 0)
		{
			col = ft_comp_var(cmds[cont], env);
			if (col >= 0)
			{
				new_env = ft_delete_str_matrix(env, col);
				flag++;
			}
		}
		cont++;
	}
	if (flag == 0)
		return (env);
	ft_free_matrix(env);
	return (new_env);
}
