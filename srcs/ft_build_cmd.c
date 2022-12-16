#include "../includes/minishell.h"

int	count_arg(t_shell *minishell)
{
	t_list	*pipeline;
	int		i;

	i = 0;
	pipeline = minishell->pipeline;
	while (pipeline && pipeline->token != PIPE)
	{
		if (pipeline->token == ARG)
			i++;
		pipeline = pipeline->next;
	}
	return (i);
}

char	**get_arg(t_shell *minishell)
{
	t_list	*pipeline;
	char	**arg;
	int		i;

	i = 0;
	pipeline = minishell->pipeline;
	arg = malloc(sizeof(char *) * (count_arg(minishell) + 2));
	if (arg == NULL)
		ft_exit(minishell, FAILED_MALLOC);
	arg[i] = minishell->cmd.name;
	i++;
	while (pipeline && pipeline->token != PIPE)
	{
		if (pipeline->token == ARG)
		{
			arg[i] = pipeline->word;
			i++;
		}
		pipeline = pipeline->next;
	}
	arg[i] = NULL;
	return (arg);
}

char	*get_name(t_shell *minishell)
{
	t_list	*pipeline;

	pipeline = minishell->pipeline;
	while (pipeline && pipeline->token != PIPE)
	{
		if (pipeline->token == CMD)
			return (pipeline->word);
		pipeline = pipeline->next;
	}
	return (NULL);
}

void	ft_build_cmd(t_shell *minishell)
{
	t_cmd	*cmd;

	cmd_init(minishell);
	cmd = &(minishell->cmd);
	cmd->name = get_name(minishell);
	if (is_builtin_internal(cmd->name))
		cmd->path = ft_strdup(cmd->name);
	else if (cmd->name)
		cmd->path = get_path(minishell);
	else
		return ;
	cmd->arg = get_arg(minishell);
	cmd->envp = minishell->envparams;
}

void	reset_cmd(t_shell *minishell)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = &(minishell->cmd);
	if (cmd->path)
		free(cmd->path);
	if (cmd->arg)
	{
		free(cmd->arg);
	}
	cmd_init(minishell);
}
