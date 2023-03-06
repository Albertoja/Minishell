/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:53:17 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/06 14:35:57 by aespinos         ###   ########.fr       */
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

char	*ft_search_home(char **env, char *home)
{
	int	col;

	col = ft_comp_var("HOME", env);
	if (col < 0)
	{
		if (!home)
			return (NULL);
		return (home);
	}
	else
		return (env[col]);
}
