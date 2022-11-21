#include "../includes/minishell.h"

void	ft_build_cmd(t_shell *minishell)
{
	cmd->name = get_name(minishell);
	cmd->path = get_path(minishell);
	if (!cmd->path)
		ft_exit(minishell, FAILED_MALLOC);
	cmd->argv = get_arg(minishell);
	if (!cmd->argv)
		ft_exit(minishell, FAILED_MALLOC);
	cmd->envp = minishell->envparams;// name matching to be done here
}

void	reset_cmd(t_shell *minishell)
{
	t_cmd	*cmd;
	int	i;

	i = 0;
	cmd = &(minishell->cmd);
	if (cmd->name)
		free(cmd->name);
	if (cmd->path)
		free(cmd->path);
	if (cmd->arg)
	{
		while (cmd->arg[i])
		{
			free(cmd->arg[i]);
			i++;
		}
		free(cmd->arg);
	}
	cmd->arg = NULL;
	cmd->name = NULL;
	cmd->path = NULL;
	cmd->envp = NULL;
	cmd->fd_in = STD_IN;
	cmd->fd_out = STD_OUT;
}
