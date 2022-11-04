#include "minishel.h"

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
 * */
int tokenize_line(t_lst *pipeline)
{
	int cmd_flag;
	e_token prev_token;
	
	cmd_flag = 0;
	prev_token = 0;
	while(pipeline->token != NEWLINE)
	{
		if
			determine_token_meta(pipeline, &prev_token, &cmd_flag);//TODO
		else
			determine_token_word(pipeline, &prev_token, &cmd_flag);//TODO
		if (check_syntax_error(pipeline, &prev_token, &cmd_flag))//TODO
			return (/**/);
		pipeline = pipeline->next;
	} 
	if (check_syntax_error(pipeline, &prev_token, &cmd_flag))//TODO
		//something
	if ()
	{
		// giving back prompt
	}
	return ();
}

// heredoc handling replace word by 

void	determine_token(t_/**/ *pipeline, e_token *prev_token, int *cmd_flag)
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
		pipeline->token = HEREDOC;
	else if (prev_token == HEREDOC)
		pipeline->token = HERE_DOC_DELIMITER;
	else if(prev_token == DOUBLE_REDIRECT_TO || prev_token == SIMPLE_REDIRECT_TO
	|| prev_token == SIMPLE_REDIRECT_FROM)
		pipeline->token = FILE_NAME;
	else if(!*cmd_flag)
	{
		pipeline->token = CMD;
		*cmd = 1;
	}
	else if(*cmd_flag)
		pipeline->token = ARG;
}

int	check_syntax_error
{
	if(ft_strcmp() && prev_token == 0);
		// print error and give back prompt
	if ()
		// print error and give back prompt
	if ()
		// print error and give back prompt
	return (0);
}

int execute_line()
{
	int nbr_pipes;

	nbr_pipes = count_pipe();
	if (nbr_pipe == 1)
	{
		execute_cmd();
		return ();
	}
	if ()
	while ()
	{
		 
	}
	
}


/* fork the process 
 * return the pid on the parent side
 * on the child side*/
int execute_cmd(t_shell *minishell)
{
	int proc_pid;
	t_cmd	cmd;

	proc_pid = fork();
	if (proc_pid < 1)
		return (proc_pid);
	if (ft_redirecti(/**/))
		terminate(/**/);
	if(ft_build_cmd(&cmd, minishell))
		terminate(/**/);
	execute_builtin(minishell);
	execve(cmd.path, cmd.arg, cmd.envp);
	free_cmd(/**/);
	perror(FAILED_EXEC_MSG);
	return (FAILED_EXEC);
}

int execute_builtin(t_shell *minishell)
{
	t_cmd	cmd;

	ft_redirect();
	ft_build_cmd(&cmd, minishell);
	if (ft_strcmp(/**/))
		exec_cd(cmd);
	if (ft_strcmp(/**/))
		exec_echo(cmd);
	if (ft_strcmp(/**/))
		exec_pwd(cdm);
	if (ft_strcmp(/**/))
		exec_export(cmd);
	if (ft_strcmp(/**/))
		exec_unset(cdm);
	if (ft_strcmp(/**/))
		exec_env(cmd);
	if (ft_strcmp(/**/))
		exec_exit(cmd);
	return ();
}
// 

int	ft_build_cmd(/*TODO*/)
{
	cmd->path = get_path();
	if (!cmd->path)
		terminate;
	cmd->argv = (char *)malloc((count_token() + 1) * sizeof(char *));
	if (!cmd->argv)
		terminate;
	cmd->arv = copy_env();
	if (!cmd->envp)
		terminate;
	
}
int	ft_redirect(/*TODO*/)
{
	while ()// loop through the wordlist
	{ 
		//open or create than replace
		if(cmd.type == SIMPLE_REDIRECT_TO)
		{
			open(/*path*/, O_WONLY | O_TRUNC | O_APPEND);
		}
		//open and read
		if (redirect == SIMPLE_REDIRECT_FORM)
		{
			open(/*path*/, O_RDONLY);
		}
		//open or create than append
		if (redirect == DOUBLE_REDIRECT_TO)
		{
			open(/*path*/, O_WONLY | O_CREAT | O_APPEND);
		}
		//increment
	}
}
