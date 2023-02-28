/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:31:05 by aespinos          #+#    #+#             */
/*   Updated: 2022/11/03 18:34:51 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char	*ret;
	int		len;

	len = 1;
	ret = NULL;
	while (1)
	{
		ret = malloc(sizeof(char) * len);
		if (getcwd(ret, len) == NULL)
			free(ret);
		else
			break ;
		len++;
	}
	return (ret);
}
