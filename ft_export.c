/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:38:12 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/27 16:50:12 by magonzal         ###   ########.fr       */
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

int	ft_check_export(char *str)
{
	while (*str)
	{
		if ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'Z')
			|| (*str >= 'a' && *str <= 'z') || (*str == '=')
			|| (*str == '_') || (*str == '\n'))
			str++;
		else
			return (0);
	}
	return (1);
}

char	**copy_str_matrix(char **env, char *str, int a)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = malloc(sizeof(char *) * (count_str(env) + 2));
	while (env[++i])
	{
		if (i == a && a != -1)
			new_env[i] = ft_strdup(str);
		else
			new_env[i] = ft_strdup(env[i]);
	}
	if (a == -1)
	{
		new_env[i] = ft_strdup(str);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**ft_export(char **cmds, char **env)
{
	int	cont;
	int	cop;

	cop = 0;
	cont = -1;
	if (!cmds[1] || !cmds || !*cmds)
	{
		while (env[++cont])
			printf("declare -x %s\n", env[cont]);
		return (env);
	}
	cont = 1;
	while (cmds[cont])
	{
		if (ft_check_export(cmds[cont]) == 0)
		{
			printf("export: `%s': not a valid identifier\n", cmds[cont]);
			exit(0);
		}
		cop = ft_comp_var(cmds[cont], env);
		env = copy_str_matrix(env, cmds[cont], cop);
		cont++;
	}
	return (env);
}