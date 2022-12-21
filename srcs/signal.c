/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:59:08 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/20 13:08:20 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	event(void)
{
	return (0);
}

void	sig_in_append(int signal)
{
	if (signal == SIGINT)
	{
		rl_readline_state = RL_STATE_DONE;
		rl_done = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = -1;
	}
}

void	sig_nothing(int signal)
{
	(void)signal;
}

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		g_exit_code = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
