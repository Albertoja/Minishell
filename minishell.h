/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aespinos <aespinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:27:12 by aespinos          #+#    #+#             */
/*   Updated: 2023/03/22 19:40:49 by aespinos         ###   ########.fr       */
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
# include <termios.h>
# include <signal.h>
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

typedef struct s_pxstrt
{
	t_all	*head;
	char	**env;
	int		*status;
	char	*home;
}	t_pxstrt;

typedef struct s_strings
{
	char	*ret;
	char	*var;
	char	*str_aux;
}	t_strings;

extern int	g_interactive;

char		**copy_str_matrix(char **env, char *str, int a);
char		**ft_cd(char **args, char **env, int *status);
char		**ft_clean_quotes(char **files);
char		**ft_split_pipe(char const *s, char c);
char		**search_cmds(char *str);
char		**search_files(char *str);
char		*check_str(char *str);
char		*copy_no_quotes(char *str);
int			ft_echo(char **str);
char		*elim_dollar_putequal(char *str);
char		**exe(t_all *first, char **envp, int *status);
char		*ft_endquotes(char *input, char a);
char		**ft_export(char **cmds, char **env, int *status);
char		*ft_homepath(char **env);
char		*ft_str_copy_num(char *str, int n);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(const char *s1, char const *s2);
char		*ft_strjoin_n(char *str1, char *str2, int n);
char		*ft_strjoingnl(const char *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*get_next_line(int fd);
char		*get_path(char *cmd, char *envp[]);
char		*get_pwd(void);
char		*search_line_env(char *str, char **env);
char		*search_redirection(char *straux);
int			count_str(char **matrix);
char		**ft_builtins(t_all *head, char **env, int *status);
int			ft_comp_var(char *cmds, char **env);
int			ft_comp_var(char *cmds, char **env);
int			ft_print_matrix(char **matrix);
void		heredoc(t_all *first, char **envp, int *status);
int			is_builtin(char *command);
int			outputappendredirection(t_all *first, char **envp);
void		outputredirection(t_all *first, char **envp, int *status);
int			search_files42(char *str);
size_t		ft_linelen(const char *line);
size_t		ft_strlen(const char *s);
t_all		*ft_create_lst(char **matrix);
char		**ft_unset(char **cmds, char **env);
void		*ft_calloc(size_t count, size_t size);
void		error(char *str);
void		execmd(t_all *first, char **envp, int *status);
void		ft_create_history(char *input, char **env);
void		ft_error(char *str, char *straux);
void		ft_ls(char **cmds);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_read_history(char **env);
void		ft_slave1(t_all *head, int pip[2], char *envp[]);
void		ft_slave2(t_all *head, int pip[2], char *envp[]);
void		ft_wait_for_input(char **env);
void		handler_ctrlc(int sig);
void		heredocaux(int *fd_len, t_all *f, char **envp, int *pip);
void		hello_norminette(char **str, char const *s, int **i, int *a);
void		inputredirection(t_all *f, char **envp, int *status);
void		outputredirection(t_all *f, char **envp, int *status);
void		outputredirectionaux(t_all *f, char **envp, char *path, int *i);
void		pipex(t_all *head, char **envp, int *status);
void		no_ctrlprint(void);
void		redirections(t_all *first, char **envp, int *status);
void		rl_replace_line(char *s, int a);
void		signals_handlers(void);
void		signals_handlers_default(void);
char		*ft_endpipe(char *oldinput);
size_t		ft_lenchar(char const *s, int c);
char		*get_oldpwd(char **env);
char		*ft_putquotes_export(char *str);
char		*ft_dollar_sust_str(char *str, char **env, int *status);
int			ft_dollarutils01(char *str_aux, int co);
t_strings	ft_dollarutils02(t_strings st, int *status, char **env, int co);
char		*elim_dollar_putequal_str(char *str, char **env, int *status);
t_strings	ft_dollarutils03(t_strings st, int co);
int			ft_swdollar(int sw, char a);
int			ft_comp_dollar(char *str, int co);
int			ft_errorcd(char *new_dir);
int			ft_comp_var(char *cmds, char **env);
char		*ft_search_home(char **env);
void		heredocpip(t_all *aux, int i, int out);
void		ft_pipex_aux(int *pip, pid_t pid, int *in_out_all_act);
int			ft_rederror(char *straux, int cont);
char		*ft_errorred(char *str, int error);
char		**ft_change_pwd(char **env, char *new_dir, int i);
char		*back_three_dir(char *new_dir);
char		*ft_change_dir(char *new_dir);
char		*ft_search_pwd(char **env);
int			ft_errorcd2(void);
char		*ft_access_dir(char *new_dir);
char		*ft_search_dir_simp(char *new_dir);
char		*ft_status_comp(int *status);
#endif
