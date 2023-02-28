/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:53:17 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/28 09:19:42 by magonzal         ###   ########.fr       */
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
