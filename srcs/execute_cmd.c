#include "minishell.h"

/* fork the process 
 * return the pid on the parent side
 * on the child side*/
pid_t	exec_cmd(t_shell *minishell)
{
	int proc_pid;
	t_cmd	cmd;

	proc_pid = fork();
	if (proc_pid == 0)
		return (proc_pid);
	else if (proc_pid < 0)
		ft_exit(minishell, FORK_FAILED);
	cmd = minishell->cmd;
	ft_redirect(minishell);// should set exit values to 0 if succes 1 if not
	if (cmd == NULL)
		ft_exit(minishell, NULL)
	execute_builtin(minishell);
	execve(cmd.path, cmd.arg, cmd.envp);
	ft_exit(minishell, FAILED_EXEC);
}

// using the pointer to path as cmd.name maybe to be able to restart from there 
void	exec_pipeline(t_shell *minishell)
{
	int	i;

	i = 0;
	while (i <= minishell->nbr_pipe)
	{
		ft_build_cmd(minishell);
		(minishell->pid)[i] = exec_cmd(minishell);
		ft_reset_cmd(minishell);
		i++;
	}
	i = 0;
	while (i <= minishell->nbr_pipe)
	{
		waitpid((minishell->pid)[i], &g_exit_code, 0);
		i++;
	}
}

void	exec_builtin(t_shell *minishell)
{
	ft_redirect(minishell);
	if (!ft_strcmp("cd", (minishell->cmd).name)
		ft_cd(minishell);
	if (!ft_strcmp("echo", (minishell->cmd).name)
		ft_echo(minishell);
	if (!ft_strcmp("pwd", (minishell->cmd).name)
		ft_pwd(minishell);
	if (!ft_strcmp("export", (minishell->cmd).name)
		ft_export(minishell);
	if (!ft_strcmp("unsset", (minishell->cmd).name)
		ft_unset(minishell);
	if (!ft_strcmp("env", (minishell->cmd).name)
		ft_env(minishell);
	if (!ft_strcmp("exit", (minishell->cmd).name)
		ft_exit(minishell, MSG_DEFAULT);
}

void	execute_line(t_shell *minishell)
{
	minishell->nbr_pipe = count_pipe(minishell);
	minishell->pid = malloc((nbr_pipe + 1) * sizeof(pid_t));
	if (minishell->pid == NULL)
		ft_exit(minishell, NULL, FAILED_MALLOC);
	set_pipes(minishell);//TODO
	if (nbr_pipe == 0 && is_builtin(minishell))
	{
		ft_build_cmd(minishell);
		exec_builtin(minishell);
	}
	else
		exec_pipeline(minishell);
}
