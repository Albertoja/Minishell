#include "minishell.h"

void	no_ctrlprint(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	handler_ctrlc(int sig)
{
	sig = 0;
	sig++;
	if (g_interactive == 1)
	{
		//g_interactive = 0;
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_redisplay();
	}
	else if (g_interactive == 2)
	{
		close(0);
		ft_putstr_fd("\n", 1);
		g_interactive = 3;
	}
}

void	handler_ctrlslash(int sig)
{
	sig = 0;
	sig++;
	write(1, "barra\n", 6);
	if (g_interactive)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	ft_putstr_fd("^\\Quit: 3\n", 1);
}

void	signals_handlers(void)
{
	struct sigaction	ctrlc;
	struct sigaction	ctrlslash;

	ctrlc.sa_handler = &handler_ctrlc;
	ctrlslash.sa_handler = &handler_ctrlslash;
	sigaction(SIGINT, &ctrlc, NULL);
	sigaction(SIGQUIT, &ctrlslash, NULL);
}
