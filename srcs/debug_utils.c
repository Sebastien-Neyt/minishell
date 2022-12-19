/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:28:16 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/12 16:58:56 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cmd(t_shell *minishell)
{
	t_cmd *cmd;
	int i;

	i = 0;
	cmd = &(minishell->cmd);
	printf(BLUE"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"WHITE);
	printf(BLUE"||\t"GREEN"[NAME]\t[%s]\n"WHITE, cmd->name);
	printf(BLUE"||\t"GREEN"[PATH]\t[%s]\n"WHITE, cmd->path);
	printf(BLUE"||\t"GREEN"[ FD ]\t[(%d)(%d)]\n"WHITE, cmd->fd_in, cmd->fd_out);
	while (cmd->arg && cmd->arg[i])
	{
		printf(BLUE"||\t"GREEN"[ ARG]\t[%s]\n"WHITE, cmd->arg[i]);
		i++;
	}
	printf(BLUE"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"WHITE"\n");
}

void	print_envs(t_shell *minishell)
{
	int	i;

	i = 0;
	while (minishell->envparams[i])
	{
		printf("%s\n", minishell->envparams[i]);
		i++;
	}
}

void	print_list(t_shell *minishell)
{
	while (minishell->list->next)
	{
		printf("%s\n", minishell->list->word);
		minishell->list = minishell->list->next;
	}
	printf("%s\n", minishell->list->word);

}

void	print_pipeline(t_shell *minishell)
{
	t_list *pipeline;

	pipeline = minishell->pipeline;
	while (pipeline->next)
	{
		printf(YELLOW"WORD=[%s] ||||| "CYAN"TOKEN=[%u]\n"WHITE, pipeline->word, pipeline->token);
		pipeline = pipeline->next;
	}

		printf(YELLOW"WORD=[%s] ||||| "CYAN"TOKEN=[%u]\n"WHITE, pipeline->word, pipeline->token);

}
/*
void	test_expansions(t_shell *minishell)
{
	while (minishell->list->next)
	{
		check_expansion(minishell->list->word, minishell);
		minishell->list = minishell->list->next;
	}
}
*/

/*
void	test_expansions(t_shell *minishell)
{
	while (minishell->list->next)
	{
		check_expansion(minishell->list->word, minishell);
		minishell->list = minishell->list->next;
	}
}
*/

