/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:28:29 by aespinos          #+#    #+#             */
/*   Updated: 2022/11/07 15:50:27 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**change_env(char **env, char *newpath, char *path)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			env[i] = ft_strjoin("PWD=", newpath);
		else if (ft_strncmp(env[i], "OLDPWD=", 4) == 0)
			env[i] = ft_strjoin("OLDPWD=", path);
		i++;
	}
	chdir(newpath);
	return (env);
}

char	*cd_normal(char **cmds, char *path)
{
	char	*newpath;
	char	*aux;
	int		fd;

	if (cmds[1] && cmds[1][0] == '/')
		return (cmds[1]);
	path = ft_strjoin(path, "/");
	newpath = ft_strjoin(path, cmds[1]);
	if (newpath[ft_strlen(newpath) - 1] == '/')
	{
		aux = ft_substr(newpath, 0, ft_strlen(newpath) - 1);
		free(newpath);
		newpath = aux;
	}
	free(path);
	fd = open(newpath, O_DIRECTORY | O_RDONLY);
	if (fd <= 0)
		return (NULL);
	close(fd);
	return (newpath);
}
char	*cd_back(char *path)
{
	int		len;
	char	*ret;

	if (ft_strncmp(path, "/", 5) == 0)
		return (path);
	len = ft_strlen(path);
	while (path[len] != '/')
		len--;
	ret = ft_substr(path, 0, len);
	return (ret);
}

char	*cd_home(char **env)
{
	char	*ret;

	while(*env)
	{
		if (ft_strncmp(*env, "HOME=", 5) == 0)
		{
			ret = ft_substr(*env, 5, 4294967295);
			return (ret);
		}
		env++;
	}
	return (NULL);
}

char	**ft_cd(char **cmds, char **env)
{
	char	*path;
	char	*newpath;

	if (!env)
		return (NULL);
	//ft_print_matrix(env);
	path = get_pwd();
	if (!cmds[1])
		newpath = cd_home(env);
	else if (ft_strncmp(cmds[1], "..", 5) == 0)
		newpath = cd_back(path);
	else
		newpath = cd_normal(cmds, path);
	if (newpath)
		env = change_env(env, newpath, path);
	free(path);
	free(newpath);
	return (env);
}
