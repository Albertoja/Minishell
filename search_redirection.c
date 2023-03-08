/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:32:39 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/08 19:13:34 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_redirection02(char *straux, char *ret, int cont)
{
	if (!ft_rederror(straux, cont))
		ft_error("bad redirection", NULL);
	else
	{
		cont++;
		if (straux[cont] == '<')
			ft_error("bad redirection", NULL);
		if (straux[cont] == '>')
		{
			if (!straux[cont + 1])
				ft_error("bad redirection", NULL);
			else
				return ("4");
		}
		else
			return ("2");
	}
	return (ret);
}

char	*search_redirection01(char *straux, char *ret, int cont)
{
	if (!ft_rederror(straux, cont))
		ft_error("bad redirection", NULL);
	else
	{
		cont++;
		if (straux[cont] == '>')
			ft_error("bad redirection", NULL);
		if (straux[cont] == '<')
		{
			if (!straux[cont + 1])
				ft_error("bad redirection", NULL);
			else
				return ("3");
		}
		else
			return ("1");
	}
	return (ret);
}

char	*search_redirection(char *straux)
{
	int		cont;
	char	*ret;

	cont = -1;
	ret = NULL;
	while (straux[++cont])
	{
		if (straux[cont] == '<')
		{
			if (!ret)
				ret = ft_strdup(search_redirection01(straux, ret, cont));
			else
				ret = ft_strjoin(ret, search_redirection01(straux, ret, cont));
		}
		else if (straux[cont] == '>')
		{
			if (!ret)
				ret = ft_strdup(search_redirection02(straux, ret, cont));
			else
				ret = ft_strjoin(ret, search_redirection02(straux, ret, cont));
		}
		if ((straux[cont] == '<' || straux[cont] == '>') && straux[cont + 1])
			cont++;
	}
	return (ret);
}
