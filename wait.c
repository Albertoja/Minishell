#include "minishell.h"

char *readline(char const *prompt);

void ft_wait_for_input()
{
	char *inp;

	inp = readline("Minishell $>");
	printf("%s", inp);
}