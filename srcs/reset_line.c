/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:25:23 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/20 08:39:35 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_init(t_shell *minishell)
{
	t_cmd	*cmd;

	cmd = &(minishell->cmd);
	cmd->arg = NULL;
	cmd->name = NULL;
	cmd->path = NULL;
	cmd->envp = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
}

void	reset_line(t_shell *minishell)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
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
	free_list(minishell->list);
	minishell->list = ft_lstnew(NULL);
	free_list(minishell->pipeline_start);
	minishell->pipeline = ft_lstnew(NULL);
	minishell->pipeline_start = minishell->pipeline;
}
