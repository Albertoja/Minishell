/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:44:07 by magonzal          #+#    #+#             */
/*   Updated: 2023/03/07 19:41:34 by aespinos         ###   ########.fr       */
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

void	freeall(char *cmd, char	**paths)
{
	free(cmd);
	ft_free_matrix(paths);
}

char	*get_path(char *cmd, char *envp[])
{
	char	**paths;
	char	*goodpath;
	int		i_j[2];

	i_j[0] = 0;
	i_j[1] = 0;
	if (access(cmd, 0) == 0)
		return (cmd);
	while (envp[i_j[0]] && ft_strncmp(envp[i_j[0]], "PATH=", 5))
		i_j[0]++;
	paths = ft_split(envp[i_j[0]] + 5, ':');
	cmd = ft_strjoinm("/", cmd);
	while (paths[i_j[1]])
	{
		goodpath = ft_strjoinm(paths[i_j[1]], cmd);
		if (access(goodpath, 0) == 0)
		{
			freeall(cmd, paths);
			return (goodpath);
		}
		free(goodpath);
		i_j[1]++;
	}
	freeall(cmd, paths);
	return (NULL);
}
