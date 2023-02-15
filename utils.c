/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:53:17 by aespinos          #+#    #+#             */
/*   Updated: 2023/01/27 11:16:52 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_homepath(char *env[])
{
	int		j;
	char	*homepath;

	j = 0;
	while (env[++j] && ft_strncmp(env[j], "OLDPWD=", 7))
		homepath = ft_strdup(env[j]);
	homepath = ft_strtrim(homepath, "PWD=");
	homepath = ft_strjoinm(homepath, "/history");
	return (homepath);
}
