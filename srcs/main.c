/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:44:30 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/20 09:44:44 by sneyt            ###   ########.fr       */
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

int	change_term(bool echo_ctl_chr)
{
	struct termios	term;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &term);
	if (status == -1)
		return (1);
	if (echo_ctl_chr)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	if (status == -1)
		return (1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	minishell;

	minishell = init_shell(envp);
	(void)argv;
	if (argc > 1)
		ft_exit(NULL, ERR_ARGNBR);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	change_term(false);
	read_exec_loop(&minishell, 1);
	ft_exit(&minishell, "minishell : unexpected error\n");
	return (1);
}
/*  "bash: syntax error: unexpected end of file"
 *  shell-init: error retrieving current directory:
 *  getcwd: cannot access parent directories: No such file or directory
 */
