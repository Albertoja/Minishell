/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:53:17 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/22 19:32:55 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_lenchar(char const *s, int c)
{
	size_t	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len] != c && s[len])
		len++;
	return (len);
}

char	*get_oldpwd(char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			return (ft_substr(env[i], 7, UINT_MAX));
		env++;
	}
	return (NULL);
}

int	ft_errorcd(char *new_dir)
{
	printf("minishell: cd: %s: No such file or directory\n", new_dir);
	return (1);
}

char	*ft_search_home(char **env)
{
	int	col;

	col = ft_comp_var("HOME", env);
	if (col < 0)
		return (NULL);
	return (env[col]);
}

char	*ft_search_pwd(char **env)
{
	int		col;
	char	*ret;

	ret = NULL;
	col = ft_comp_var("PWD", env);
	if (col < 0)
		return (NULL);
	else
	{
		if (ft_strncmp(env[col], "PWD=", 4) == 0)
		{
			ret = ft_substr(env[col], 4, UINT_MAX);
			return (ret);
		}
	}
	return (ret);
}
