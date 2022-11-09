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
 *
void	append_line(t_shell *minishell)
{
	minishell->line_tmp = minishell->line;
	minishell->line = readline(">");
	if (minishell->line == NULL)
		ft_exit(minishell, UNXPCTD_EOF);
	parse_line(minishell);
	tokenize_line(minishell);
	check_syntax(minishell);
	join_line(minishell); //TODO should join the 2 lines, replace the line
}
 *
 * launch an ifinite loop that will:
 *	readline
 *	parse_line
 *	tokenize_line
 *	check syntax of the tokenized line
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
			ft_exit(minishell, NULL, DEFAULT);
		parse_line(minishell);
		tokenize_line(minishell);
		check_syntax(minishell);
		while (!minishell->line_done)
			append_line(minishell);
		execute_line(minishell);
		rl_add_history(minishell->line);
		clear_line(minishell);
	}
}
*
*
* declare struct
* initialize struct
* check arg nbr
* initialize signals
* call the main read exec loop
* the program will call exit() from within the loop
* neither the terminate nor the return should ever be reached
*
int	main(int argc, char *argv[], char *envp[])
{
	t_shell minishell;

	init_shell_struct(&minishell);
	if (argc > 1)
		ft_exit(NULL, NULL, ERR_ARGNBR);
	sig_init();
	init_envs(&minishell, envp);
	read_exec_loop(&minishell);
	ft_exit(&minishell, NULL, "unexpected error");
	return (1);
}
*
*  "bash: syntax error: unexpected end of file"
*  shell-init: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
*/
