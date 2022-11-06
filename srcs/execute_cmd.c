#include "minishell.h"

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
