/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:46 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/08 19:15:27 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str, char *straux)
{
	printf("minishell: %s: %s\n", straux, str);
}

char	*ft_errorred(char *str, int error)
{
	free(str);
	if (error == 1)
		printf("bash: syntax error near unexpected token `newline'\n");
	if (error == 2)
		printf("bash: error redirection\n");
	return (NULL);
}
