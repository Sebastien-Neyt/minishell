/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:02:07 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/02 11:48:33 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_msg(char *err, int ret)
{
	write(1, err, ft_strlen(err));
	return (ret);
}

void	free_env(t_shell *minishell)
{
	int	i;
	int	size;

	//size = env_counter(minishell->envparams);
	while (minishell->envparams[i])
	{
		free(minishell->envparams[i]);
		i++;
	}
	free(minishell->envparams);
}

