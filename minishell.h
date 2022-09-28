#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
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

typedef struct s_list
{
	int				content;
	struct s_list	*next;
}	t_list;

typedef struct s_all {
	char	**matrix_input;
	t_list	*commands;
}	t_all;


void	ft_wait_for_input();
void	check_str(char *str);
void	ft_error(char *str);
char	**ft_split_pipe(char const *s, char c);
void	ft_print_matrix(t_all *all);
void	ft_create_lst(t_all all);
#endif
