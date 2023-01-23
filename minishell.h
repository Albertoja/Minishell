/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:27:12 by aespinos          #+#    #+#             */
/*   Updated: 2023/01/23 18:14:15 by aespinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <dirent.h>
# include <sys/stat.h>
# include "libft/libft.h"
# define RESET				"\x1b[0m"
# define WHITE				"\x1b[1m"
# define GRAY				"\x1b[2m"
# define BLACK				"\x1b[30m"
# define RED				"\x1b[31m"
# define GREEN				"\x1b[32m"
# define YELLOW				"\x1b[33m"
# define BLUE				"\x1b[34m"
# define PURPLE				"\x1b[35m"
# define CYAN				"\x1b[36m"
# define BUFFER_SIZE 3

typedef struct s_strings
{
	char	*ret;
	char	*var;
	char	*str_aux;
}	t_strings;

void	ft_wait_for_input(char **env, int status);
char	*check_str(char *str);
void	ft_error(char *str, char *straux);
char	**ft_split_pipe(char const *s, char c);
int		ft_print_matrix(char **matrix);
t_all	*ft_create_lst(char **matrix);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	ft_create_history(char	*input);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_read_history(void);
char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	**search_files(char *str);
char	*search_redirection(char *straux);
void	hello_norminette(char **str, char const *s, int **i, int *a);
char	**ft_clean_quotes(char **files);
char	**ft_builtins(t_all *head, char **env);
void	ft_echo(char **str);
char	**ft_cd(char **cmds, char **env);
char	*get_pwd(void);
void	ft_ls(char **cmds);
char	**ft_export(char **cmds, char **env);
int		count_str(char **matrix);
int		ft_comp_var(char *cmds, char **env);
char	**ft_unset(char **cmds, char **env);
char	**search_cmds(char *str);
int		ft_comp_var(char *cmds, char **env);
char	*ft_dollar(char *input, char **env);
char	*ft_dollar_sust_str(char *str, char **env);
char	*search_line_env(char *str, char **env);
char	*elim_dollar_putequal(char *str);
char	*ft_endquotes(char *input, char a);
char	*copy_no_quotes(char *str);
char	**copy_str_matrix(char **env, char *str, int a);
int		search_files42(char *str);
char	*ft_str_copy_num(char *str, int n);
char	*ft_strjoin_n(char *str1, char *str2, int n);
#endif
