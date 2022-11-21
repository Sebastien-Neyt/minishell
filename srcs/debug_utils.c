/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:28:16 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/16 11:40:11 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

