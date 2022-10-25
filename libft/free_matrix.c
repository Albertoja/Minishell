/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:22:29 by aespinos          #+#    #+#             */
/*   Updated: 2022/10/24 19:13:30 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
		return (0);
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	return (0);
}
