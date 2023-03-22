/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:04:21 by aespinos          #+#    #+#             */
/*   Updated: 2023/01/17 20:02:31 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_str_copy_num(char *str, int n)
{
	// char	*ret;
	// int		cont;
	
	// cont = 0;
	// ret = malloc(sizeof(char) * (n + 1));
	// while (cont < n)
	// 	ret[cont++] = *str++;
	str[n] = '\0';
	return (str);
}
