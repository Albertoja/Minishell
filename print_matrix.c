/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:21:53 by aespinos          #+#    #+#             */
/*   Updated: 2022/11/03 18:10:30 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (1);
	while (matrix[i])
	{
		ft_putstr_fd(matrix[i++], 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
