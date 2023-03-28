/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:13:14 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/28 16:42:36 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*back_one_dir(char *path)
{
	int		len;
	char	*new_dir;

	if (ft_strncmp(path, "/", 5) == 0)
		return (path);
	len = ft_strlen(path);
	while (path[len] != '/')
		len--;
	new_dir = ft_substr(path, 0, len);
	free(path);
	return (new_dir);
}

char	**ft_change_pwd(char **env, char *new_dir, int i)
{
	char	*pwd;
	char	*aux;

	aux = env[i];
	if (access(new_dir, F_OK) != 0)
	{
		env[i] = ft_strjoinm("PWD=", new_dir);
	}
	else
	{
		pwd = get_pwd();
		env[i] = ft_strjoinm("PWD=", pwd);
		free(pwd);
	}
	free(aux);
	return (env);
}

char	*back_three_dir(char *new_dir)
{
	while (access(new_dir, F_OK) != 0)
		new_dir = back_one_dir(new_dir);
	return (new_dir);
}

char	*ft_change_dir(char *new_dir)
{
	char	*aux;

	aux = ft_substr(new_dir, 0, ft_strlen(new_dir) - 1);
	free(new_dir);
	new_dir = ft_strdup(aux);
	free(aux);
	return (new_dir);
}

char	*ft_access_dir(char *new_dir)
{
	char	*simp;
	DIR		*open;

	open = opendir(new_dir);
	if (open)
	{
		closedir(open);
		return (new_dir);
	}
	else
	{
		simp = ft_search_dir_simp(new_dir);
		printf("minishell: cd: %s: Not a directory\n", simp);
		free(simp);
	}
	return (new_dir);
}
