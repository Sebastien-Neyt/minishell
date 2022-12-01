#include "../includes/minishell.h"

// note should maybe close fd's in case too many simultanous cdmd's are executed

// should throw error if token after redirection is ARG 
int	ft_redirect(t_shell *minishell)//TODO
{
	/*t_list	*pipeline;
	int	oflag;

	pipeline = minishell->pipeline;
	oflag = 0;
	while (pipeline && pipeline->token != PIPE)// loop through the wordlist
	{
		//open or create than replace
		if(pipeline->token == SIMPLE_REDIRECT_TO)
			oflag = (O_WRONLY | O_TRUNC | O_APPEND);
		//open and read
		if (pipeline->token == SIMPLE_REDIRECT_FROM)
			oflag = (O_RDONLY);
		//open or create than append
		if (pipeline->token == DOUBLE_REDIRECT_TO)
			oflag = (O_WRONLY | O_CREAT | O_APPEND);
		if (oflag)
			pipeline = pipeline->next;
		if (open(pipeline->word, oflag) == -1)
			return (0);
		oflag = 0;
		pipeline = pipeline->next;
	}*/
	dup2(minishell->cmd.fd_in, STDIN_FILENO);
	dup2(minishell->cmd.fd_out, STDOUT_FILENO);
	return (1);
}

/* if cmd is a builtin call the corresponding function
 */
int	exec_builtin_2(t_shell *minishell)
{
	if (!ft_strcmp("export", (minishell->cmd).name))
	{
		ft_export(minishell);
		return (1);
	}
	if (!ft_strcmp("unset", (minishell->cmd).name))
	{
		ft_unset(minishell);
		return (1);
	}
	if (!ft_strcmp("env", (minishell->cmd).name))
	{
		ft_env(minishell);
		return (1);
	}
	return (0);
}

int	exec_builtin(t_shell *minishell)
{
	if (!ft_strcmp("exit", (minishell->cmd).name))
		ft_exit(minishell, DEFAULT_MSG);
	if (!ft_strcmp("cd", (minishell->cmd).name))
	{
		ft_cd(minishell);
		return (1);
	}
	if (!ft_strcmp("echo", (minishell->cmd).name))
	{
		ft_echo(minishell);
		return (1);
	}
	if (!ft_strcmp("pwd", (minishell->cmd).name))
	{
		ft_pwd(minishell);
		return (1);
	}
	return (exec_builtin_2(minishell));
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
		ft_exit(minishell, FAILED_FORK);
	cmd = &minishell->cmd;
	if (ft_redirect(minishell) == 0)
		ft_exit(minishell, NULL);
	if (cmd->name == NULL)
		ft_exit(minishell, NULL);
	if (exec_builtin(minishell))
		ft_exit(minishell, NULL);
	else
		execve(cmd->path, cmd->arg, cmd->envp);
	ft_exit(minishell, FAILED_EXEC);
	return (-1);
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
			(minishell->cmd).fd_in = fd[0];
		if (i < minishell->nbr_pipe)
		{
			if (pipe((fd)) == -1)
				ft_exit(minishell, FAILED_PIPE);
			(minishell->cmd).fd_out = fd[1];
		}
		//print_cmd(minishell);//TEST
		(minishell->pid)[i] = exec_cmd(minishell);
		if (i < minishell->nbr_pipe)
			close(fd[1]);
		if (i > 0)
			close((minishell->cmd).fd_in);
		reset_cmd(minishell);
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
	minishell->pipeline_start = minishell->pipeline;
	minishell->pid = malloc((minishell->nbr_pipe) * sizeof(pid_t));
	if (minishell->pid == NULL)
		ft_exit(minishell, FAILED_MALLOC);
	if (minishell->nbr_pipe == 0 && is_builtin(minishell))
	{
		ft_build_cmd(minishell);
		ft_redirect(minishell);
		exec_builtin(minishell);
		reset_cmd(minishell);
	}
	else
		exec_pipeline(minishell);
	while (i <= minishell->nbr_pipe)
	{
		waitpid((minishell->pid)[i], &g_exit_code, 0);
		printf(YELLOW"[PID][%d]\t"WHITE, minishell->pid[i]);
		printf(YELLOW"[RET][%d]\n"WHITE, g_exit_code);
		i++;
	}
}
