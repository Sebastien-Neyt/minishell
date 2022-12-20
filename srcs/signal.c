/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 08:21:39 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/20 09:44:25 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
static void	process_signal(int signal)
{
	printf("test %d\n", signal);	
}
*/

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		printf("SIGINT >> New prompt on the next line \n");
		g_exit_code = 1;
	//	rl_replace_line("", 0);
		rl_on_new_line();
		//reset line
	}
	else if (signal == SIGQUIT)
	{
		//rl_replace_line("", 0);
		//printf("SIGQUIT does nothing \n");
		//rl_on_new_line();
	}
}
