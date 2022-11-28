/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:25:27 by aespinos          #+#    #+#             */
/*   Updated: 2022/11/28 19:43:35 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_str_matrix(char **env, char *str, int a)
{
	int		i;
	char	**new_matrix;

	i = -1;
	new_matrix = malloc(sizeof(char *) * (count_str(env) + 1));
	while (env[++i])
	{
		if (i == a && a != -1)
			new_matrix[i] = ft_strdup(str);
		else
			new_matrix[i] = ft_strdup(env[i]);
	}
	// if (a == -1)
	// 	new_matrix[i] = ft_strdup(str);
	new_matrix[i] = NULL;
	return (new_matrix);
}

char	*search_line_env(char *str, char **env)
{
	char	*ret;
	int	i;
	int	j;
	int	a;

	i = 0;
	j = 0;
	a = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
		{
			ret = malloc(sizeof(char) * (ft_strlen(env[i]) - ft_strlen(str)) + 1);
			while (env[i][j])
			{
				while (env[i][j] != '=')
					j++;
				j++;
				while (env[i][j])
				{
					ret[a] = env[i][j];
					a++;
					j++;
				}
			}
			ret[a] = '\0';
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*elim_dollar_putequal(char *str)
{
	char	*ret;
	int		a;
	
	a = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str)) + 1);
	str++;
	while (*str)
	{
		ret[a] = *str;
		a++;
		str++;
	}
	ret[a] = '=';
	a++;
	ret[a] = '\0';
	return (ret);
}

char	**ft_dollar_sust(char **env, char **mat, int pos)
{
	char	**ret;
	char	*straux;
	char	*sust;

	straux = elim_dollar_putequal(mat[pos]);
	sust = search_line_env(straux, env);
	ret = copy_str_matrix(mat, sust, pos);
	free(straux);
	free(sust);
	return (ret);
}

char	**ft_dollar(char **mat, char **env)
{
	int		i;

	i = 0;
	while (mat[i])
	{
		if (mat[i][0] == '$')
			mat = ft_dollar_sust(env, mat, i);
		if (mat[i][0] == '"')
			mat[i] = ft_dollar_sust_str(mat[i], env);
		i++;
	}
	//exit(0);
	return(mat);
}
