/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:21:47 by aespinos          #+#    #+#             */
/*   Updated: 2022/01/21 13:04:50 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	if (dstsize < ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	while (dst[a])
		a++;
	if (dstsize < a)
	{
		while (src[b])
			b++;
		return (dstsize + b);
	}
	while (dstsize > 0 && a < dstsize - 1 && src[b])
		dst[a++] = src[b++];
	dst[a] = '\0';
	while (src[b++])
		a++;
	return (a);
}

// int main()
// {
//     //****************************************            strlcpy main.
//     char src[21] = "0sdasfe";
//     char dest[13] = "rrrrrrrrrrrrr";
//     char src2[8] = "0sdasfe";
//     char dest2[21] = "rrrrrrrrrrrrr";
//     size_t mine;
//     size_t their;
//     //printf("before: %p\n", dest);
//     mine = ft_strlcat(dest, src, 5);
//     //printf("after: %p\n", r);
//     their = strlcat(dest2, src2, 5);
//     printf("mine = %lu\ntheir = %lu\n", mine, their);
//     printf("---------------------------\n");
//     for(int i = 0; i < 23; i++)
//     {
//             printf("%c\n", dest[i]);
// 			if (dest[i] == 0)
// 				printf("its null\n");
//     }
//     printf("--------------------------------------\n");
//     for(int j = 0; j < 23; j++)
//     {
//             printf("%c\n", dest2[j]);
// 			if (dest2[j] == 0)
// 				printf("its null\n");
//     }
// }