#include "../includes/minishell.h"

void	reset_line(t_shell *minishell)
{
	reset_cmd(minishell);
	if (minishell->pid)
		free(minishell->pid);
	minishell->pid = NULL;
	if (minishell->line)
		free(minishell->line);
	minishell->line = NULL;
	if (minishell->line_tmp)
		free(minishell->line_tmp);
	minishell->line_tmp = NULL;
	if (minishell->list)
		free(minishell->list);
	minishell->list = ft_lstnew(NULL);
	if (minishell->pipeline_start)
		free(minishell->pipeline_start);
	minishell->pipeline = ft_lstnew(NULL);	
}
