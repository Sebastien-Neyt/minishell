#include "../includes/minishell.h"
/*
int	check_syntax_error
{
	t_list	*pipeline;
	e_token	prev_token;

	prev_token = LINE_START;
	pipeline = minishell->pipeline;
	while (pipeline)
	{
		if (prev_token == PIPE && pipeline->token == PIPE)
			return (1);
		prev_token = pipeline->token;
		pipeline = pipeline->next;
	}
	return (0);
}
*/
/* return 0 if line has a unexpended heredoc or if ended by a pipe
 * return 1 if not
 */
int	check_line_done(t_shell *minishell)
{
	t_list *pipeline;

	pipeline = minishell->pipeline;
	while(pipeline->next)
	{
		if (pipeline->token == HEREDOC_DEL)
			return (0);
		pipeline = pipeline->next;
	}
	if (pipeline->token == PIPE)
		return (0);
	return (1);
}
