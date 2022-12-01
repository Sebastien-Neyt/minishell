#include "../includes/minishell.h"

void	determine_token_meta(t_list *pipeline, int *cmd_flag)
{
	if (!ft_strcmp("|", pipeline->word))
	{
		pipeline->token = PIPE;
		*cmd_flag = 0;
	}
	else if (!ft_strcmp(">|", pipeline->word) || !ft_strcmp(">", pipeline->word))
		pipeline->token = SIMPLE_REDIRECT_TO;
	else if(!ft_strcmp("<", pipeline->word))
		pipeline->token = SIMPLE_REDIRECT_FROM;
	else if(!ft_strcmp(">>", pipeline->word))
		pipeline->token = DOUBLE_REDIRECT_TO;
	else if(!ft_strcmp("<<", pipeline->word))
	{
		pipeline->token = HEREDOC;
	}
}
	
void	determine_token_word(t_list *pipeline, e_token *prev_token, int *cmd_flag)
{
	if (*prev_token == HEREDOC)
		pipeline->token = HEREDOC_DEL;
	else if(*prev_token == DOUBLE_REDIRECT_TO || *prev_token == SIMPLE_REDIRECT_TO
	|| *prev_token == SIMPLE_REDIRECT_FROM)
		pipeline->token = FILE_NAME;
	else if(!*cmd_flag)
	{
		pipeline->token = CMD;
		*cmd_flag = 1;
	}
	else if(*cmd_flag)
		pipeline->token = ARG;
}

/*first word that is not a redirect is is always command all others are arguments
 * reset at each pipe
 * if pipe as first word 
 * or pipe following pipe
 * or incorect combination of pipe and redirect
 * 	bash: syntax error near unexpected token `|'
 * 	bash: syntax error near unexpected token `newline'
 * 	bash: syntax error near unexpected token `>'
 * 	bash: syntax error near unexpected token `<'
 *
 * 	error code = 2
 */
void	tokenize_line(t_shell *minishell)
{
	int 	cmd_flag;
	t_list	*pipeline;
	e_token prev_token;
	
	cmd_flag = 0;
	prev_token = 0;
	pipeline = minishell->pipeline;
	while(pipeline)
	{
		determine_token_meta(pipeline, &cmd_flag);
		if (pipeline->token == SINGLE || pipeline->token == DOUBLE)
			pipeline->token = WORD;
		if (pipeline->token == WORD)
			determine_token_word(pipeline, &prev_token, &cmd_flag);
		prev_token = pipeline->token;
		pipeline = pipeline->next;
	} 
}

// heredoc handling replace word by lines
// heredoc doesn't strip newline
// single eof terminate current here doc but doesnt call exit
// bash: warning: here-document at line 7 delimited by end-of-file (wanted `del')

