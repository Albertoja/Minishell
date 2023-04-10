/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:46 by aespinos          #+#    #+#             */
/*   Updated: 2023/04/04 20:38:03 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *str, char *straux)
{
	printf("minishell: %s: %s\n", straux, str);
}

char	*ft_errorred(char *str, int error)
{
	if (str)
		free(str);
	if (error == 1)
		printf("minishell: syntax error near unexpected token `newline'\n");
	if (error == 2)
		printf("minishell: error redirection\n");
	return (ft_strdup(" "));
}

int	ft_errorcd2(void)
{
	printf("cd: error retrieving current directory: getcwd: cannot");
	printf(" access parent directories: No such file or directory\n");
	return (1);
}

char	*ft_search_dir_simp(char *new_dir)
{
	int		len;
	int		len_aux;
	char	*ret;

	if (!new_dir || !(*new_dir))
		return (ft_strdup(" "));
	len = ft_strlen(new_dir);
	while (len)
	{
		if (new_dir[len] == '/')
			break ;
		len--;
	}
	if (new_dir[len] != '/')
		return (ft_strdup(" "));
	len_aux = len + 1;
	len = ft_strlen(new_dir);
	ret = malloc(sizeof(char) * (len - len_aux + 1));
	len = 0;
	while (new_dir[len_aux])
		ret[len++] = new_dir[len_aux++];
	ret[len] = '\0';
	return (ret);
}

char	*ft_status_comp(int *status)
{
	if (*status >= 256)
		*status = *status / 256;
	return (ft_itoa(*status));
}
