/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:45:41 by aespinos          #+#    #+#             */
/*   Updated: 2023/02/28 19:26:00 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_strlen_var(char *str)
{
	int	ret;

	ret = 0;
	while (str[ret] && str[ret] != ' ' && str[ret] != '"' && str[ret] != '\'')
		ret++;
	return (ret);
}

char	*search_line_env2(char *ret, char **env, int i)
{
	int	j;
	int	a;

	j = 0;
	a = 0;
	while (env[i][j])
	{
		while (env[i][j] != '=')
			j++;
		j++;
		while (env[i][j])
		{
			ret[a] = env[i][j];
			a++;
			j++;
		}
	}
	ret[a] = '\0';
	return (ret);
}

char	*search_line_env(char *str, char **env)
{
	char	*ret;
	int		i;
	int		len;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
		{
			len = ft_strlen(env[i]) - ft_strlen(str);
			ret = malloc(sizeof(char) * (len + 1));
			ret = search_line_env2(ret, env, i);
			free(str);
			return (ret);
		}
		i++;
	}
	free(str);
	return (ft_strdup(" "));
}

char	*elim_dollar_putequal_str(char *str, char **env, int status)
{
	char	*ret;
	int		a;

	a = 0;
	while (*str && *str != '$')
		str++;
	ret = malloc(sizeof(char) * (ft_strlen_var(str) + 1));
	if (str && *str)
		str++;
	while (*str && *str && *str != ' '
		&& *str != '"' && *str != '\'' && *str != '$')
	{
		ret[a] = *str;
		a++;
		str++;
	}
	ret[a] = '=';
	if (ret[a] && ret)
		a++;
	ret[a] = '\0';
	if (ft_strncmp(ret, "?=", ft_strlen(ret)) == 0)
		return (ft_itoa(status));
	return (search_line_env(ret, env));
}

char	*ft_dollar_sust_str(char *str, char **env, int *status)
{
	t_strings	st;
	int			co;

	co = -1;
	st.str_aux = str;
	st.ret = NULL;
	while (st.str_aux[++co])
	{
		if (st.str_aux[co] == 39)
		{
			st = ft_dollarutils03(st, co);
			co = -1;
		}
		if (st.str_aux[co] == '$'
			&& ((st.str_aux[co + 1] > 47 && st.str_aux[co + 1] < 58)
				|| (st.str_aux[co + 1] > 64 && st.str_aux[co + 1] < 91)
				|| (st.str_aux[co + 1] > 96 && st.str_aux[co + 1] < 123)))
		{
			st = ft_dollarutils02(st, status, env, co);
			co = -1;
		}
	}
	st.ret = ft_strjoin_n(st.ret, st.str_aux, co);
	free (str);
	return (st.ret);
}
