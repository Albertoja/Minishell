#include "minishell.h"

void	ft_error(char *str)
{
	printf("Error: %s\n", str);
	ft_wait_for_input();
}
