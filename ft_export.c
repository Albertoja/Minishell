/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:38:12 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/28 16:55:29 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**input_var(char **env, char *str)
{
	int		i;
	char	**new_env;

	i = -1;
	new_env = malloc(sizeof(char *) * (count_str(env) + 2));
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = ft_strdup(str);
	new_env[++i] = NULL;
	ft_free_matrix(env);
	return (new_env);
}

static int	check_var(char *str, int *status)
{
	int		ret;
	char	*aux;

	aux = str;
	ret = 1;
	if (ft_isalpha(*str) == 0 && *str != '_')
		ret = 0;
	while (*str != '=' && *str)
	{
		if (*str != '_' && ft_isalnum(*str) == 0)
			ret = 0;
		str++;
	}
	if (ret == 0)
	{
		*status = 1;
		printf("minishell: export: `%s': not a valid identifier\n", aux);
	}
	return (ret);
}

static char	*replace_line(char *replace, char *with)
{
	free(replace);
	return (ft_strdup(with));
}

static char	**print_matrix_export(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix || !*matrix)
		return (NULL);
	while (matrix[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(matrix[i++], 1);
		ft_putchar_fd('\n', 1);
	}
	return (matrix);
}

char	**ft_export(char **args, char **env, int *status)
{
	int		i;
	int		flag;
	size_t	len;
	int		j;

	i = 0;
	if (!args[1] || !env || !*env)
		return (print_matrix_export(env));
	while (args[++i])
	{
		flag = check_var(args[i], status);
		if (flag)
		{
			j = 0;
			len = ft_lenchar(args[i], '=');
			while (env[j] && ft_strncmp(args[i], env[j], len) != 0)
				j++;
			if (env[j] == NULL)
				env = input_var(env, args[i]);
			else
				env[j] = replace_line(env[j], args[i]);
		}
	}
	return (env);
}
