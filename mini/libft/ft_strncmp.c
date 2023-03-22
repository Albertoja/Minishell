/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:24:38 by aespinos          #+#    #+#             */
/*   Updated: 2022/11/03 17:10:18 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *sr1, const char *sr2, size_t n)
{
	size_t			c;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)sr1;
	s2 = (unsigned char *)sr2;
	c = 0;
	if (n == 0)
		return (0);
	while ((s1[c] != '\0') && (s2[c] != '\0') \
			&& (s1[c] == s2[c]) && (c < (n - 1)))
		c++;
	return (s1[c] - s2[c]);
}
