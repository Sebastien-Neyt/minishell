/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:44:30 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/12 16:49:13 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_line(t_shell *minishell)
{	
	//printf("TEST//////////////////////%s\n", minishell->line);
	word_parse(minishell->line, minishell, 0, 0);
	check_for_exp(minishell);
	parse_list(minishell);
	trim_pipeline(minishell);
	tokenize_line(minishell);
//	print_pipeline(minishell);//TEST	
}

void	append_line(t_shell *minishell)
{
	char *tmp;

	minishell->line_tmp = minishell->line;
	minishell->line = readline(">");
	if (minishell->line == NULL)
		ft_exit(minishell, UNXPCTD_EOF);
	parse_line(minishell);
	//check_syntax_error(minishell);
	tmp = minishell->line;
	minishell->line = ft_strjoin(minishell->line_tmp, minishell->line);
	free(tmp);
}

int	line_not_done(t_shell *minishell)
{
	t_list *pipeline;

	pipeline = minishell->pipeline;
	while (pipeline && pipeline->next)
	{
		if (pipeline->token == HEREDOC_DEL)
			return (1);
		pipeline = pipeline->next;
	}
	if (pipeline->token == PIPE)
		return (1);
	return (0);
}

/* launch an ifinite loop that will:
 *	readline
 *	parse_line
 *	tokenize_line
 *	check syntax of the tokenized line
 *	append_line while line not done (ex: pipe token at the end of line)
 *	add to history
 *	free line
 *	repeat
 */
void	read_exec_loop(t_shell *minishell)
{
	while (1)
	{
		minishell->line = readline("minishell"RED"<3 "WHITE"");
		if (minishell->line == NULL)
			ft_exit(minishell, DEFAULT_MSG);
		parse_line(minishell);
		//check_syntax_error();
		while (line_not_done(minishell))
			append_line(minishell);
		execute_line(minishell);
		//rl_add_history(minishell->line);
		reset_line(minishell);
	}
}

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
	t_shell minishell;
	
	minishell = init_shell(envp);

	(void)argv;
	if (argc > 1)
		ft_exit(NULL, ERR_ARGNBR);
	//sig_init();
	read_exec_loop(&minishell);
	ft_exit(&minishell, "minishell : unexpected error\n");
	return (1);
}

/*  "bash: syntax error: unexpected end of file"
 *  shell-init: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
 */
