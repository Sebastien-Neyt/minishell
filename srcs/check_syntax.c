/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:05:08 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 16:35:15 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_syntax_pipe(int prev_token)
{
	if (prev_token == LINE_START
		|| prev_token == PIPE
		|| prev_token == SIMPLE_REDIRECT_TO
		|| prev_token == SIMPLE_REDIRECT_FROM
		|| prev_token == DOUBLE_REDIRECT_TO
		|| prev_token == HEREDOC)
		return (1);
	return (0);
}

int	check_syntax_last(int token)
{
	if (token == SIMPLE_REDIRECT_TO
		|| token == SIMPLE_REDIRECT_FROM
		|| token == DOUBLE_REDIRECT_TO
		|| token == HEREDOC)
		return (1);
	return (0);
}

int	check_syntax_error(t_shell *minishell)
{
	t_list	*pipeline;
	t_token	prev_token;

	pipeline = minishell->pipeline_start;
	prev_token = LINE_START;
	while (pipeline)
	{
		if (pipeline->token == PIPE)
			if (check_syntax_pipe(prev_token))
				return (1);
		if (pipeline->next == NULL)
			if (check_syntax_last(pipeline->token))
				return (1);
		prev_token = pipeline->token;
		pipeline = pipeline->next;
	}
	return (0);
}

/* return 0 if line has a unexpended heredoc or if ended by a pipe
 * return 1 if not
 */
int	line_not_done(t_shell *minishell)
{
	t_list	*pipeline;

	pipeline = minishell->pipeline;
	if (check_syntax_error(minishell))
	{
		write(\
2, "minishell : syntax error\n", ft_strlen("minishell : syntax error\n"));
		return (-1);
	}
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

void	move_pipeline(t_shell *minishell)
{
	while (minishell->pipeline && minishell->pipeline->token != PIPE)
		minishell->pipeline = minishell->pipeline->next;
	if (minishell->pipeline && minishell->pipeline->token == PIPE)
		minishell->pipeline = minishell->pipeline->next;
}
