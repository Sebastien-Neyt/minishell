/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:44:30 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/02 14:49:47 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell minishell;
	
	minishell = init_shell(argv, envp);

	
	char *line = "<Makefile cat| echo \"$PWD 'hola'\" ~/src | 'tr' -d / >outfile";
	
	word_parse(line, &minishell);

	while (minishell.list->next)
	{
		printf("%s\n", minishell.list->word);
		minishell.list = minishell.list->next;
	}
	printf("%s\n", minishell.list->word);
	/*
	print_envs(&minishell);
	printf("\n\n");
	set_env("USERNAME", "S0cr@tes", &minishell);
	print_envs(&minishell);
	set_env("USERNAME", "Cycollar", &minishell);
	set_env("PWD", "THISISATEST", &minishell);
	print_envs(&minishell);
	*/
	
	return (0);
}
/*
 * launch an ifinite loop that will:
 *	readline
 *	parse_line
 *	tokenize_line
 *	append_line while line not done (ex: pipe token at the end of line)
 *	add to history
 *	free line
 *	repeat
 *
void	read_exec_loop(t_shell *minishell)
{
	while (1)
	{
		minishell->line = readline("minishell");
		if (minishell.line == NULL)
			ft_exit(NULL, minishell);
		parse_line(&minishell);
		tokenize_line(&minishell);
		while (!minishell->line_done)
			append_line(minishell);
		execute_line(&minishell);
		rl_add_history(minishell->line);
		free(minishell->line);
		minishell->line = NULL;
	}
}
*
*
* declare struct
* initialize struct
* check arg nbr
* initialize signals
* call the main read exec loop
* the program should never exit from the main
*
int	main(int argc, char *argv[], char *envp[])
{
	t_shell minishell;

	init_shell_struct(&minishell);
	if (argc > 1)
		terminate(NULL, ERR_ARGNBR);
	sig_init();
	init_envs(&minishell, envp);
	read_exec_loop(&minishell);
	terminate(&minishell, NULL);
	return (1);
}
*/
