/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:51:39 by aespinos          #+#    #+#             */
/*   Updated: 2022/12/14 16:53:34 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_matrix_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (1);
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (0);
}

int	ft_pwd(void)
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
	printf("%s\n", ret);
	return (0);
}

void	ft_exit2(char **str)
{
	if (str[1][0] == '-' && ft_strncmp("-9223372036854775808", str[1], 21) < 0)
		printf("minishell: exit: %s: numeric argument required\n", str[1]);
	else if (str[1][0] != '-' &&
			ft_strncmp("9223372036854775807", str[1], 21) < 0)
		printf("minishell: exit: %s: numeric argument required\n", str[1]);
}

void	ft_exit(char **str, char **envc)
{
	int	env;
	int	cont;

	cont = 0;
	ft_free_matrix(envc);
	if (!str[1])
		exit(0);
	while (str[1][cont])
	{
		if (str[1][0] == '-' || str[1][cont] < '0' ||
			str[1][cont] > '9' || ft_strlen(str[1]) >= 19)
		{
			if (str[1][0] != '-' && str[1][cont] == '-')
			{
				printf("minishell: exit: %s: ", str[1]);
				printf("numeric argument required\n");
				exit(255);
			}
		}
		cont++;
	}
	ft_exit2(str);
	env = ft_atoi(str[1]);
	exit(env);
}

char	**ft_builtins(t_all *head, char **env)
{
	if (ft_strncmp(head->cmds[0], "exit", 10) == 0)
		ft_exit(head->cmds, env);
	else if (ft_strncmp(head->cmds[0], "pwd", 10) == 0)
		ft_pwd();
	else if (ft_strncmp(head->cmds[0], "echo", 10) == 0)
		ft_echo(head->cmds);
	else if (ft_strncmp(head->cmds[0], "cd", 10) == 0)
		ft_cd(head->cmds, env);
	else if (ft_strncmp(head->cmds[0], "env", 10) == 0)
		ft_print_matrix_env(env);
	else if (ft_strncmp(head->cmds[0], "export", 10) == 0)
		env = ft_export(head->cmds, env);
	else if (ft_strncmp(head->cmds[0], "unset", 10) == 0)
		env = ft_unset(head->cmds, env);
	else
		ft_error("command not found", head->cmds[0]);
	return (env);
}
