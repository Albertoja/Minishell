/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:28:29 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/22 17:35:52 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_dir2(char *new_dir, char **args, int *status)
{
	static int	sw;

	if (access(new_dir, F_OK) == 0)
		return(ft_access_dir(new_dir));
	else
	{
		if (sw == 1)
		{
			sw = 0;
			return (back_three_dir(new_dir));
		}
		if (ft_strncmp(args[1], "..", 2) == 0)
		{
			sw = 1;
			*status = ft_errorcd2();
			return (new_dir);
		}
		*status = ft_errorcd(args[1]);
		free(new_dir);
	}
	sw = 0;
	return (NULL);
}

char	*check_dir(char **args, char *path, int *status)
{
	char		*new_dir;

	if (args[1] && args[1][0] == '/')
		return (args[1]);
	path = ft_strjoinm(path, "/");
	new_dir = ft_strjoinm(path, args[1]);
	if (new_dir[ft_strlen(new_dir) - 1] == '/')
		new_dir = ft_change_dir(new_dir);
	free(path);
	return (check_dir2(new_dir, args, status));
}

void	replace_pwd_oldpwd(char *new_dir, char *path, char **env, char **args)
{
	int		i;
	char	*aux;

	i = -1;
	if (chdir(new_dir) != 0 && (ft_strncmp(args[1], "..", 2) != 0))
		return ;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			env = ft_change_pwd(env, new_dir, i);
	}
	chdir(new_dir);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 4) == 0)
		{
			aux = env[i];
			env[i] = ft_strjoinm("OLDPWD=", path);
			free(aux);
		}
	}
}

char	*get_home(char **env, int *status)
{
	char	*new_dir;

	while (*env)
	{
		if (ft_strncmp(*env, "HOME=", 5) == 0)
		{
			new_dir = ft_substr(*env, 5, UINT_MAX);
			return (new_dir);
		}
		env++;
	}
	ft_putstr_fd("minishell: cd : HOME not set\n", 1);
	*status = 1;
	return (NULL);

}

char	**ft_cd(char **args, char **env, int *status)
{
	char	*path;
	char	*new_dir;

	if (!env)
		return (NULL);
	path = get_pwd();
	if (!args[1] || ft_strncmp(args[1], "~", 5) == 0)
		new_dir = get_home(env, status);
	else if (ft_strncmp(args[1], "-", 5) == 0)
		new_dir = get_oldpwd(env);
	else
		new_dir = check_dir(args, path, status);
	if (new_dir)
		replace_pwd_oldpwd(new_dir, path, env, args);
	free(path);
	free(new_dir);
	return (env);
}
