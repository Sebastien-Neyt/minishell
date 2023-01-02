/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:04 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/20 16:01:04 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->word)
			free(tmp->word);
		tmp->word = NULL;
		free(tmp);
	}
}

int	exit_internal(t_shell *minishell)
{
	if (minishell->cmd.arg[1] && is_num(minishell->cmd.arg[1]) \
		&& minishell->cmd.arg[2])
	{
		write(STDERR_FILENO, EXIT_ERR_ARGC, ft_strlen(EXIT_ERR_ARGC));	
		g_exit_code = 2;
		return (1);
	}
	else if (minishell->cmd.arg[1] && is_num(minishell->cmd.arg[1]))
		g_exit_code = ft_atoi(minishell->cmd.arg[1]);
	else if (minishell->cmd.arg[1] && !is_num(minishell->cmd.arg[1]))
	{
		write(STDERR_FILENO, EXIT_ERR_NUM, ft_strlen(EXIT_ERR_NUM));
		g_exit_code = 1;
	}
	return (0);
}

void	ft_exit(t_shell *minishell, char *msg)
{
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	if (minishell->cmd.arg && exit_internal(minishell))
		return ;
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
	minishell->list = NULL;
	free_list(minishell->pipeline_start);
	minishell->pipeline = NULL;
	minishell->pipeline_start = NULL;
	free_env(minishell);
	clear_history();
	exit(g_exit_code);
}
