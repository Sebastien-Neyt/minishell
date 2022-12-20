/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:44:30 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/20 10:59:35 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* declare struct
 * initialize struct
 * check arg nbr
 * initialize signals
 * call the main read exec loop
 * the program will call exit() from within the loop
 * neither the terminate nor the return should ever be reached
 */
int	main(int argc, char *argv[], char *envp[])
{
	t_shell	minishell;

	minishell = init_shell(envp);
	(void)argv;
	if (argc > 1)
		ft_exit(NULL, ERR_ARGNBR);
	//sig_init();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	read_exec_loop(&minishell, 1);
	ft_exit(&minishell, "minishell : unexpected error\n");
	return (1);
}
/*  "bash: syntax error: unexpected end of file"
 *  shell-init: error retrieving current directory:
 *  getcwd: cannot access parent directories: No such file or directory
 */
