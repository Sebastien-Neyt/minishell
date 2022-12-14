#include "../includes/minishell.h"

void	check_syntax_error(t_shell *minishell)
{
	t_list	*pipeline;
	e_token	prev_token;

	pipeline = minishell->pipeline_start;
	prev_token = LINE_START;
	while (pipeline)
	{
		if (prev_token == PIPE && pipeline->token == PIPE)
			ft_exit(minishell, "syntax error");
		prev_token = pipeline->token;
		pipeline = pipeline->next;
	}
}

/* return 0 if line has a unexpended heredoc or if ended by a pipe
 * return 1 if not
 */
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

void	move_pipeline(t_shell *minishell)
{
	while (minishell->pipeline && minishell->pipeline->token != PIPE)
		minishell->pipeline = minishell->pipeline->next;
	if (minishell->pipeline && minishell->pipeline->token == PIPE)
		minishell->pipeline = minishell->pipeline->next;
}

