/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:53:55 by aespinos          #+#    #+#             */
/*   Updated: 2022/11/03 18:36:15 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**search_cmds(char *str)
{
	char	*straux;
	int		len;
	int		lenaux;
	char	**ret;

	len = 0;
	lenaux = 0;
	while (str[len] && str[len] != '<' && str[len] != '>')
	{
		len++;
	}
	straux = malloc(sizeof(char) * (len + 1));
	while (lenaux < len)
	{
		straux[lenaux] = str[lenaux];
		lenaux++;
	}
	straux[lenaux] = '\0';
	ret = ft_split_pipe(straux, ' ');
	free(straux);
	return (ret);
}

t_all	*ft_parse(char **matrix, int *cont)
{
	t_all	*head;

	head = ft_calloc(sizeof(t_all), 1);
	if (matrix[++(*cont)])
	{
		head->dir = search_redirection(matrix[*cont]);
		head->cmds = search_cmds(matrix[*cont]);
		head->files = search_files(matrix[*cont]);
		head->files = ft_clean_quotes(head->files);
		// printf("redireccion:%s\n", head->dir);
		// printf("Comandos:\n");
		// ft_print_matrix(head->cmds);
		// printf("Archivos:\n");
		// ft_print_matrix(head->files);
		// printf("-------------------\n");
	}
	return (head);
}

t_all	*ft_create_lst(char **matrix)
{
	t_all	*head;
	t_all	*temp;
	int		cont;

	cont = -1;
	head = ft_parse(matrix, &cont);
	temp = head;
	while (matrix[cont])
		ft_lstadd_back(&head, ft_parse(matrix, &cont));
	ft_free_matrix(matrix);
	return (head);
}
