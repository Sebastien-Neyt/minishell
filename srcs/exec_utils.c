#include "../includes/minishell.h"

int	is_builtin(char *name)
{
	if (name == NULL)
		return (0);
	if (!ft_strcmp("cd", name)
		return (1);
	if (!ft_strcmp("echo", name)
		return (1);
	if (!ft_strcmp("pwd", name)
		return (1);
	if (!ft_strcmp("export", name)
		return (1);
	if (!ft_strcmp("unsset", name)
		return (1);
	if (!ft_strcmp("env", name)
		return (1);
	if (!ft_strcmp("exit", name)
		return (1);
	return (0);
}
int	ft_build_cmd(t_shell *minishell)
{
	cmd->path = get_path();
	if (!cmd->path)
		terminate;
	cmd->argv = (char *)malloc((count_token() + 1) * sizeof(char *));
	if (!cmd->argv)
		ft_exit(minishell, FAILED_MALLOC);
	cmd->argv = minishell->env;// name matching to be done here
}

// should throw error if token after redirection is ARG 
int	ft_redirect(t_shell *minishell)
{
	t_list	*pipeline;

	pipeline = minishell->pipeline;
	while (pipeline->token != NEWLINE && pipeline->token != PIPE)// loop through the wordlist
	{ 
		//open or create than replace
		if(cmd.type == SIMPLE_REDIRECT_TO)
		{
			open(/*path*/ O_WONLY | O_TRUNC | O_APPEND);
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

		pipeline = pipeline->next;
	}
}
