#include "minishell.h"

void ft_wait_for_input()
{
	char *input;
	t_all all;

	while(1)
	{
		input = readline(YELLOW"Minishell $>"RESET);
		if (!input)
			exit(1);
		check_str(input);
		all.matrix_input = ft_split_pipe(input, '|');
		ft_print_matrix(&all);
		//ft_create_lst(&all);
	}
}
