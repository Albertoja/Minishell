/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:44:59 by magonzal          #+#    #+#             */
/*   Updated: 2023/03/23 19:51:09 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (g_interactive)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	ft_putstr_fd("^\\Quit: 3\n", 1);
}

void	signals_handlers_default(void)
{
	struct sigaction	ctrlc;
	struct sigaction	ctrlslash;

	ctrlc.sa_handler = SIG_IGN;
	ctrlslash.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ctrlc, NULL);
	sigaction(SIGQUIT, &ctrlslash, NULL);
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
