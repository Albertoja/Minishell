/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollarutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:07:22 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/01 20:04:12 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_dollarutils01(char *str_aux, int co)
{
	co++;
	while (str_aux[co] != 39)
		co++;
	co++;
	return (co);
}

t_strings	ft_dollarutils02(t_strings st, int *status, char **env, int co)
{
	st.ret = ft_strjoin_n(st.ret, st.str_aux, co);
	while (*st.str_aux && *st.str_aux != '$')
		st.str_aux++;
	st.var = elim_dollar_putequal_str(st.str_aux++, env, *status);
	while (*st.str_aux && *st.str_aux != 32 && *st.str_aux != 34
		&& *st.str_aux != 39 && *st.str_aux != 36 && *st.str_aux != '?')
		st.str_aux++;
	if (*st.str_aux == '?')
		st.str_aux++;
	st.ret = ft_strjoin(st.ret, st.var);
	free(st.var);
	return (st);
}

t_strings	ft_dollarutils03(t_strings st, int co)
{
	int	aux;

	aux = 0;
	co = ft_dollarutils01(st.str_aux, co);
	st.ret = ft_strjoin_n(st.ret, st.str_aux, co);
	aux = 0;
	while (aux < co)
	{
		aux++;
		st.str_aux++;
	}
	return (st);
}

int	ft_swdollar(int sw, char a)
{
	if (a == 34)
	{
		if (sw == 1)
			sw = 0;
		else if (sw == 0)
			sw = 1;
	}
	return (sw);
}

int	ft_comp_dollar(char *str, int co)
{
	if (str[co] == '$'
		&& ((str[co + 1] > 47 && str[co + 1] < 58)
			|| (str[co + 1] > 64 && str[co + 1] < 91)
			|| (str[co + 1] > 96 && str[co + 1] < 123)
			|| (str[co + 1] == '?')))
		return (0);
	else
		return (1);
}
