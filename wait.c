#include "minishell.h"

void ft_wait_for_input()
{
	char *input;

	input = readline(YELLOW"Minishell $>"RESET);
	check_str(input);
}
