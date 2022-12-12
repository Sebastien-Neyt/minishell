/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:44:30 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/12 17:21:04 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	append_str(char **str1, char *str2)
{
	char	*tmp;

	if (str2 == NULL)
		return 1;
	if (*str1 == NULL)
	{
		*str1 = str2;
		return 1;
	}
	tmp = ft_strjoin(*str1, str2);
	if (tmp == NULL)
		return 0;
	free(*str1);
	*str1 = tmp;
	return 1;
}

void	parse_line(t_shell *minishell)
{	
	if (minishell->list->word != NULL)
		minishell->list = ft_lstnew(NULL);
	word_parse(minishell->line, minishell, 0, 0);
	check_for_exp(minishell);
	parse_list(minishell);
	trim_pipeline(minishell);
	tokenize_line(minishell);
}

void	append_line(t_shell *minishell)
{

	minishell->line_tmp = minishell->line;
	minishell->line = readline(">");
	if (minishell->line == NULL)
		ft_exit(minishell, UNXPCTD_EOF);
	parse_line(minishell);
	//check_syntax_error(minishell);
	if (append_str(&(minishell->line_tmp), minishell->line) == 0)
		ft_exit(minishell, FAILED_MALLOC);
	free(minishell->line);
	minishell->line = minishell->line_tmp;
	minishell->line_tmp = NULL;
}

void	get_heredoc2(t_shell *minishell, t_list *pipeline, char *input, int control)
{
	free(pipeline->word);
	pipeline->word = input;
	pipeline->token = HEREDOC_CONTENT;
	if (minishell->line == NULL)
		perror("warning: here-document delimited by end-of-file\n");
	else
		free(minishell->line);
	minishell->line = minishell->line_tmp;
	minishell->line_tmp = NULL;
	if (control == 0)
		ft_exit(minishell, FAILED_MALLOC);
}

void	get_heredoc(t_shell *minishell, t_list *pipeline, char *input, int control)
{
	pipeline = minishell->pipeline;
	minishell->line_tmp = minishell->line;
	while (pipeline && pipeline->token != HEREDOC_DEL)
		pipeline = pipeline->next;
	while (control)
	{
		minishell->line = readline(">");
		if (minishell->line == NULL)
			break;
		if (append_str(&(minishell->line_tmp), minishell->line) == 0)
			control = 0;
		if (ft_strcmp(minishell->line, pipeline->word) == 0)
			break;
		if (append_str(&(input), minishell->line) == 0)
			control = 0;
	}
	get_heredoc2(minishell, pipeline, input, control);
}

int	line_not_done(t_shell *minishell)
{
	t_list *pipeline;

	pipeline = minishell->pipeline;
	while (pipeline && pipeline->next)
	{
		if (pipeline->token == HEREDOC_DEL)
			return (HEREDOC_DEL);
		pipeline = pipeline->next;
	}
	if (pipeline->token == PIPE || pipeline->token == HEREDOC_DEL)
		return (pipeline->token);
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
	int not_done;

	not_done = 0;
	while (1)
	{
		minishell->line = readline("minishell"RED"<3 "WHITE"");
		if (minishell->line == NULL)
			ft_exit(minishell, DEFAULT_MSG);
		parse_line(minishell);
		//check_syntax_error();
		not_done = line_not_done(minishell);
		while (not_done)
		{
			if (not_done == HEREDOC_DEL)
				get_heredoc(minishell, NULL, NULL, 1);
			else if (not_done == PIPE)
				append_line(minishell);
			not_done = line_not_done(minishell);
		}
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
