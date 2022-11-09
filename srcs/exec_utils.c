#include "minishell.h"

int	ft_build_cmd(t_shell minishell)
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
