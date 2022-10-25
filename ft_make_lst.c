/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:53:55 by aespinos          #+#    #+#             */
/*   Updated: 2022/10/25 17:51:42 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**search_files(char *str)
{
	char	**ret;
	char	*str_aux;
	int		cont;
	int		cont2;

	cont = 0;
	cont2 = 0;
	str_aux = NULL;
	while (str[cont])
	{
		if (str[cont] == '<' || str[cont] == '>')
		{
			while (str[cont])
			{
				cont2++;
				cont++;
			}
		}
		else
			cont++;
	}
	str_aux = malloc(sizeof(char) * (cont2 + 1));
	cont2 = 0;
	cont = 0;
	while (str[cont])
	{
		if (str[cont] == '<' || str[cont] == '>')
		{
			while (str[cont])
			{
				if (str[cont] == '<' || str[cont] == '>')
					str_aux[cont2] = ' ';
				else
					str_aux[cont2] = str[cont];
				cont++;
				cont2++;
			}
		}
		else
			cont++;
	}
	str_aux[cont2] = '\0';
	ret = ft_split_pipe(str_aux, ' ');
	free(str_aux);
	return (ret);
}

char	*search_redirection(char *straux)
{
	int		cont;
	char	*ret;

	cont = 0;
	ret = NULL;
	while (straux[cont])
	{
		if (straux[cont] == '<')
		{
			if (!straux[cont + 1])
				ft_error("bad redirection");
			else
			{
				cont++;
				if (straux[cont] == '>')
					ft_error("bad redirection");
				if (straux[cont] == '<')
				{
					if (!straux[cont + 1])
						ft_error("bad redirection");
					else
					{
						if (!ret)
							ret = ft_strdup("3");
						else
							ret = ft_strjoin(ret, "3");
					}
				}
				else
				{
					if (!ret)
						ret = ft_strdup("1");
					else
						ret = ft_strjoin(ret, "1");
				}
			}
		}
		else if (straux[cont] == '>')
		{
			if (!straux[cont + 1])
				ft_error("bad redirection");
			else
			{
				cont++;
				if (straux[cont] == '<')
					ft_error("bad redirection");
				if (straux[cont] == '>')
				{
					if (!straux[cont + 1])
						ft_error("bad redirection");
					else
					{
						if (!ret)
							ret = ft_strdup("4");
						else
							ret = ft_strjoin(ret, "4");
					}
				}
				else
				{
					if (!ret)
						ret = ft_strdup("2");
					else
						ret = ft_strjoin(ret, "2");
				}
			}
		}
		cont++;
	}
	return (ret);
}

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
		printf("redireccion:%s\n", head->dir);
		printf("Comandos:\n");
		ft_print_matrix(head->cmds);
		printf("Archivos:\n");
		ft_print_matrix(head->files);
		printf("-------------------\n");
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
