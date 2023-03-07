/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magonzal <magonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:00:29 by magonzal          #+#    #+#             */
/*   Updated: 2023/03/07 18:02:34 by magonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipex_aux(int *pip, pid_t pid, int *in_out_all_act)
{
	close(pip[1]);
	waitpid(pid, &in_out_all_act[4], 0);
	close(in_out_all_act[0]);
	in_out_all_act[0] = pip[0];
}
