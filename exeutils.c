/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:44:07 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/28 16:30:13 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(char **path, int j)
{
	int	i;

	i = -1;
	if (!path)
		return ;
	while (path[++i] && j <= 0)
	{
		free(path[i]);
		j--;
	}
	free(path);
}

char	*get_path(char *cmd, char *envp[])
{
	char	**paths;
	char	*goodpath;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (cmd[0] == '/' && access(cmd, 0) == 0)
		return (cmd);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	cmd = ft_strjoinm("/", cmd);
	while (paths[j])
	{
		goodpath = ft_strjoinm(paths[j], cmd);
		if (access(goodpath, 0) == 0)
		{
			free(cmd);
			ft_free_matrix(paths);
			return (goodpath);
		}
		free(goodpath);
		j++;
	}
	free(cmd);
	ft_free_matrix(paths);
	return (NULL);
}
