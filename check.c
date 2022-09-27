#include "minishell.h"

int ft_check_pipe(char *str)
{
	int aux;

	aux = 0;
	while(str[aux])
	{
		if (str[aux] == '|')
		{
			aux++;
			while(str[aux])
			{
				if(str[aux] == ' ' || (str[aux] >= 9 && str[aux] <= 13))
					aux++;
				else
					return (1);
			}
			ft_error("pipe suelto");
		}
		aux++;
	}
	return (0);
}
void check_str(char *str)
{
	int aux;
	int aux2;

	aux = 0;
	aux2 = 0;
	while(str[aux])
	{
		if (str[aux] == 34)
		{
			aux++;
			while(str[aux] && str[aux] != 34)
				aux++;
			if(str[aux] != 34)
				ft_error("comillas no cerradas");
		}
		if (str[aux] == 39)
		{
			aux++;
			while(str[aux] && str[aux] != 39)
				aux++;
			if(str[aux] != 39)
				ft_error("comillas no cerradas");
		}
		aux++;
	}
	ft_check_pipe(str);
}
