/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:46:33 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/13 11:16:00 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(t_shell *minishell)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	while (minishell->cmd.arg[i] && !ft_strcmp(minishell->cmd.arg[i], "-n"))
	{
		new_line = 0;
		i++;
	}
	while (minishell->cmd.arg[i])
	{
		printf("%s", minishell->cmd.arg[i]);
		i++;
	}
	if (new_line)
		printf("\n");
	return (1);
}
