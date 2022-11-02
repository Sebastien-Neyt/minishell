/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:28:16 by sneyt             #+#    #+#             */
/*   Updated: 2022/10/26 11:32:44 by sneyt            ###   ########.fr       */
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
