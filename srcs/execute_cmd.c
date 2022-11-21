#include "../includes/minishell.h"

// note should maybe close fd's in case too many simultanous cdmd's are executed

// should throw error if token after redirection is ARG 
void	ft_redirect(t_shell *minishell)//TODO
{
	t_list	*pipeline;
	int	oflag;

	pipeline = minishell->pipeline;
	oflag = 0;
	while (pipeline && pipeline->token != PIPE)// loop through the wordlist
	{
		oflag = is_token(pipeline->token)
		if (oflag)
		{
			//open or create than replace
			if(cmd.type == SIMPLE_REDIRECT_TO)
				oflag = (O_WONLY | O_TRUNC | O_APPEND);
			//open and read
			if (redirect == SIMPLE_REDIRECT_FORM)
				oflag = (O_RDONLY);
			//open or create than append
			if (redirect == DOUBLE_REDIRECT_TO)
				oflag = (O_WONLY | O_CREAT | O_APPEND);
			if (open() == -1)
			{
				perror();//TODO
				break;
			}
		}
		pipeline = pipeline->next;
	}
}

/* if cmd is a builtin call the corresponding function
 */
void	exec_builtin(t_shell *minishell)
{
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

/* fork the process 
 * return the pid on the parent side
 * on the child side
 * call ft_redirect to handle redirection of io and openig/ creation of files
 * the fork terminate normaly after that if no cmd nor buitin
 * call buitin if element tokenized to COMMAND is a builtin
 * call execve if cmd exist and builtin wasn't called
 */
pid_t	exec_cmd(t_shell *minishell)
{
	int proc_pid;
	t_cmd	*cmd;

	proc_pid = fork();
	if (proc_pid > 0)
		return (proc_pid);
	else if (proc_pid < 0)
		ft_exit(minishell, FORK_FAILED);
	cmd = &minishell->cmd;
	if (ft_redirect(minishell) == NULL)
		ft_exit();
	if (cmd->name == NULL)
		ft_exit(minishell, NULL);
	if (is_builtin(cmd->name))
	{
		execute_builtin(minishell);
		ft_exit(minishell, NULL);
	}
	else
		execve(cmd->path, cmd->arg, cmd->envp);
	ft_exit(minishell, FAILED_EXEC);
}

/* set up the pipes and execute the command and perform the neccessary close()
 * each iteration of the loop will creat a pipe except the last
 * each iteration of the loop will set the fd_in to the read end of the pipe except the first
 * each iteration of the loop will set the fd_out to the write end of the pipe except the last
 */
void	exec_pipeline(t_shell *minishell)
{
	int	i;
	int	fd[2];

	i = 0;
	while (i <= minishell->nbr_pipe)
	{
		ft_build_cmd(minishell);
		if (i > 0)
		{
			(minishell->cmd).fd_in = fd[0];
			close(fd[1]);
		}
		if (i < minishell->nbr_pipe)
		{
			if (pipe((fd) == -1)
				ft_exit(minishell, FAILED_PIPE);
			(minishell->cmd).fd_out = fd[1];
		}
		(minishell->pid)[i] = exec_cmd(minishell);
		if (i < minishell->nbr_pipe)
			close(fd[0]);
		ft_reset_cmd(minishell);
		i++;
	}
}

/* count the number of pipe in the pipeline to determine the number of cmd blocks
 * malloc an array to store the pid's of each forks
 * call the function directly if only one block and if cmd is a builtin
 * else call dedicated function to execute the pipeline
 */
void	execute_line(t_shell *minishell)
{
	int	i;
	
	i = 0;
	minishell->nbr_pipe = count_pipe(minishell);
	minishell->pid = malloc((nbr_pipe + 1) * sizeof(pid_t));
	if (minishell->pid == NULL)
		ft_exit(minishell, FAILED_MALLOC);
	if (nbr_pipe == 0 && is_builtin(minishell))
	{
		ft_build_cmd(minishell);
		ft_redirect(minishell);
		exec_builtin(minishell);
		reset_cmd(minishell->cmd);
	}
	else
	{
		exec_pipeline(minishell);
		while (i <= minishell->nbr_pipe)
		{
			waitpid((minishell->pid)[i], &g_exit_code, 0);
			i++;
		}
	}
	reset_line(minishell);
}
