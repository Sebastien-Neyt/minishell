/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:59:08 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/20 12:56:20 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		g_exit_code = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
