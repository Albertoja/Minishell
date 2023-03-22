/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_files2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:43:33 by aespinos          #+#    #+#             */
/*   Updated: 2023/01/09 16:45:31 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	search_filescont01(char *str, int *cont)
// {
// 	while (str[cont[0]] == '<' || str[cont[0]] == '>')
// 		cont[0]++;
// 	while (str[cont[0]] == ' ')
// 		cont[0]++;
// 	if (str[cont[0]] == '"')
// 	{
// 		cont[1]++;
// 		cont[0]++;
// 		while (str[cont[0]] && str[cont[0]] != '"')
// 		{
// 			cont[1]++;
// 			cont[0]++;
// 		}
// 		cont[1]++;
// 		cont[0]++;
// 	}
// 	else
// 	{
// 		while (str[cont[0]] && str[cont[0]] != ' ')
// 		{
// 			cont[1]++;
// 			cont[0]++;
// 		}
// 		cont[1]++;
// 	}
// }

// int	search_files01(char *str)
// {
// 	int	cont[2];
// 	int	ret;

// 	cont[0] = 0;
// 	cont[1] = 0;
// 	while (str[cont[0]])
// 	{
// 		if (str[cont[0]] == '<' || str[cont[0]] == '>')
// 			search_filescont01(str, cont);
// 		else
// 			cont[0]++;
// 	}
// 	ret = cont[1];
// 	return (ret);
// }
