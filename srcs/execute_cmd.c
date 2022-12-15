#include "../includes/minishell.h"

void	internal_execute(t_shell *minishell)
{
	int	std_in;
	int	std_out;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	//print_cmd(minishell);//DEBUG
	ft_build_cmd(minishell);
	if (ft_redirect(minishell))
		exec_builtin(minishell);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	reset_cmd(minishell);
}

/* count the number of pipe in
 * the pipeline to determine the number of cmd blocks
 * malloc an array to store the pid's of each forks
 * call the function directly if only one block 
 * and if cmd is a builtin
 * else call dedicated function to execute the pipeline
 */
void	execute_line(t_shell *minishell)
{
	int	i;

	i = 0;
	if (minishell->pipeline->word == NULL)
		return ;
	minishell->nbr_pipe = count_pipe(minishell);
	minishell->pipeline_start = minishell->pipeline;
	minishell->pid = malloc((minishell->nbr_pipe) * sizeof(pid_t));
	if (minishell->pid == NULL)
		ft_exit(minishell, FAILED_MALLOC);
	if (minishell->nbr_pipe == 0 && is_builtin(minishell))
		internal_execute(minishell);
	else
		exec_pipeline(minishell);
	while (i <= minishell->nbr_pipe)
	{
		waitpid((minishell->pid)[i], &g_exit_code, 0);
		//printf(YELLOW"[PID][%d]\t"WHITE, minishell->pid[i]);//DEBUG
		//printf(YELLOW"[RET][%d]\n"WHITE, g_exit_code);//DEBUG
		i++;
	}
}
