/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:34:39 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/01 18:34:16 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_search_content(char *str, int len)
// {
// 	char	*ret;
// 	int		cont;
// 	int		len2;

// 	len++;
// 	len2 = len;
// 	while (str[len2])
// 		len2++;
// 	len2 = len2 - len;
// 	cont = 0;
// 	ret = malloc(len2 + 1);
// 	while (cont < len2)
// 	{
// 		ret[cont] = str[len];
// 		cont++;
// 		len++;
// 	}
// 	ret[cont] = '\0';
// 	return (ret);
// }

// char	*ft_search_var(char *str, int len)
// {
// 	char	*ret;
// 	int		cont;

// 	cont = 0;
// 	len++;
// 	ret = malloc (len + 1);
// 	while (cont < len)
// 	{
// 		ret[cont] = str[cont];
// 		cont++;
// 	}
// 	ret[cont] = '\0';
// 	return (ret);
// }

// char	*ft_putquotes_export(char *str)
// {
// 	char	*content;
// 	char	*var;
// 	int		len;

// 	len = 0;
// 	while (str[len] != '=' && str[len])
// 		len++;
// 	if (str[len] == '\0' || !str)
// 		return (ft_strdup(str));
// 	else
// 	{
// 		var = ft_search_var(str, len);
// 		content = ft_search_content(str, len);
// 		var = ft_strjoin(var, "\"");
// 		var = ft_strjoin(var, content);
// 		var = ft_strjoin(var, "\"");
// 		free(content);
// 		return (var);
// 	}
// 	return (ft_strdup(str));
// }
