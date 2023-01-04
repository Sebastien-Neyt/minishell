/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:51:00 by sneyt             #+#    #+#             */
/*   Updated: 2023/01/04 09:36:45 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_shell *minishell, int x)
{
	int	i;

	i = 0;
	while (minishell->envparams[i])
	{
		if (x == 1)
			printf("declare -x ");
		printf("%s\n", minishell->envparams[i]);
		i++;
	}
	g_exit_code = 0;
	return (0);
}
