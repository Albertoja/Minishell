/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:31:05 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/28 20:27:18 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char	*ret;
	char	buff[PATH_MAX + 1];
	int		len;

	len = 1;
	ret = NULL;
	getcwd(buff, PATH_MAX + 1);
	ret = strdup(buff);
	return (ret);
}

int	count_strs(char **arr)
{
	int	length;

	length = 0;
	if (!arr)
		return (length);
	while (arr[length])
		length++;
	return (length);
}
