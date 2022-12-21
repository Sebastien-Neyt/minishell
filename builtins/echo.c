/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:46:33 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/21 09:59:45 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_newline_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_shell *minishell)
{
	int	i;
	int	new_line;

	if (!minishell->cmd.arg[1])
		return (1);
	new_line = 1;
	i = 1;
	if (check_newline_flag(minishell->cmd.arg[i]))
	{
		new_line = 0;
		i++;
	}
	while (minishell->cmd.arg[i])
	{
		if (!minishell->cmd.arg[i + 1])
			printf("%s", minishell->cmd.arg[i]);
		else
			printf("%s ", minishell->cmd.arg[i]);
		i++;
	}
	if (new_line)
		printf("\n");
	g_exit_code = 0;
	return (1);
}
