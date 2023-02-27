/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:44:07 by magonzal          #+#    #+#             */
/*   Updated: 2023/02/25 17:19:04 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		goodpath = ft_strjoin(paths[j], cmd);
		if (access(goodpath, 0) == 0)
		{
			return (goodpath);
		}
		j++;
	}
	return (NULL);
}

void	error(char *str)
{
	printf("%s", str);
	exit (1);
}
