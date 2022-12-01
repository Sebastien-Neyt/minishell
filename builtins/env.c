/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:51:00 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/25 10:38:05 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_shell *minishell)
{
	int	i;

	i = 0;
	while (minishell->envparams[i])
	{
		printf("%s\n", minishell->envparams[i]);
		i++;
	}
	return (0);
}
