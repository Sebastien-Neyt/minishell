/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:08 by sneyt             #+#    #+#             */
/*   Updated: 2023/01/05 10:55:30 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_shell *minishell)
{
	int		loc;
	int		i;

	i = 4;
	loc = find_env("PWD", minishell);
	if (loc < 0)
	{
		g_exit_code = 1;
		return (1);
	}
	while (minishell->envparams[loc][i])
	{
		write(1, &minishell->envparams[loc][i], 1);
		i++;
	}
	write(1, "\n", 1);
	g_exit_code = 0;
	return (0);
}
