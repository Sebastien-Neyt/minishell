/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:04 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 13:13:15 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_pipeline(t_shell *minishell)
{
	while (minishell->pipeline_start)
	{
		minishell->pipeline = minishell->pipeline_start;
		minishell->pipeline_start = minishell->pipeline_start->next;
		free(minishell->pipeline);
	}
	minishell->pipeline = NULL;
	minishell->pipeline_start = NULL;
}

void	ft_exit(t_shell *minishell, char *msg)
{
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
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
	minishell->list = NULL;
	free_pipeline(minishell);
	free_env(minishell);
	clear_history();
	exit(g_exit_code);
}
