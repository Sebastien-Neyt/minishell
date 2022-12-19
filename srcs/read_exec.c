/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:26:24 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 09:26:49 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* parse the line into a pipeline and tokenize
*/
void	parse_line(t_shell *minishell)
{	
	if (minishell->list->word != NULL)
		minishell->list = ft_lstnew(NULL);
	word_parse(minishell->line, minishell, 0, 0);
	check_for_exp(minishell);
	parse_list(minishell);
	trim_pipeline(minishell);
	tokenize_line(minishell);
	//print_pipeline(minishell);//debug
}

/* read another line
 * tokenize line
 * append it to previous line
 */
void	append_line(t_shell *minishell)
{
	minishell->line_tmp = minishell->line;
	minishell->line = readline(">");
	if (minishell->line == NULL)
		ft_exit(minishell, UNXPCTD_EOF);
	parse_line(minishell);
	if (append_str(&(minishell->line_tmp), minishell->line) == 0)
		ft_exit(minishell, FAILED_MALLOC);
	free(minishell->line);
	minishell->line = minishell->line_tmp;
	minishell->line_tmp = NULL;
}

/* 
*/
void	get_heredoc2(t_shell *minishell, t_list *pipeline, char *input, int ctl)
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
	if (ctl == 0)
		ft_exit(minishell, FAILED_MALLOC);
}

void	get_heredoc(t_shell *minishell, t_list *pipeline, char *input, int ctl)
{
	pipeline = minishell->pipeline;
	minishell->line_tmp = minishell->line;
	while (pipeline && pipeline->token != HEREDOC_DEL)
		pipeline = pipeline->next;
	while (ctl)
	{
		minishell->line = readline(">");
		if (minishell->line == NULL)
			break ;
		if (append_str(&(minishell->line_tmp), minishell->line) == 0)
			ctl = 0;
		if (ft_strcmp(minishell->line, pipeline->word) == 0)
			break ;
		if (append_str(&(input), minishell->line) == 0)
			ctl = 0;
	}
	get_heredoc2(minishell, pipeline, input, ctl);
}

/* launch an ifinite loop that will:
 * 	reset everything that needs to be reset
 *	readline
 *	parse_line
 *	append_line while line not done (ex: pipe token at the end of line)
 *	if syntax error (not_done == -1) skip to next iteration of the routine
 *	add to history
 *	repeat
 */
void	read_exec_loop(t_shell *minishell, int not_done)
{
	while (1)
	{
		reset_line(minishell);
		minishell->line = readline("minishell"RED"<3 "WHITE"");
		if (minishell->line == NULL)
			ft_exit(minishell, DEFAULT_MSG);
		parse_line(minishell);
		//print_pipeline(minishell);
		not_done = line_not_done(minishell);
		while (not_done != 0 && not_done != -1)
		{
			if (not_done == HEREDOC_DEL)
				get_heredoc(minishell, NULL, NULL, 1);
			else if (not_done == PIPE)
				append_line(minishell);
			not_done = line_not_done(minishell);
		}
		if (minishell->line && *(minishell->line))
			add_history(minishell->line);
		if (not_done != -1)
			execute_line(minishell);
	}
}
