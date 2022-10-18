#include "minishell.h"

void	ft_print_matrix(t_all *all)
{
	int i;
	int	j;
	i = 0;
	j = 0;
	while(all->matrix_input[i])
	{
		j = 0;
		while(all->matrix_input[i][j])
		{
			write(1, &all->matrix_input[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	} 
}

//PITO
