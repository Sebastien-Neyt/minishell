/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:12 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/25 11:24:09 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(t_shell *minishell)
{
	char **new_envparams;
	int size;
	int loc;
	int i;
	int x;

	//unsetting multiple envs in 1 go?
	if (!minishell->cmd.arg[1])
	{
		printf("unset: not enough arguments\n");
		return (0);
	}
	i = 0;
	x = 0;
	size = env_counter(minishell->envparams);
	loc = find_env(minishell->cmd.arg[1], minishell);
	if (loc < 0)
		return (0);
	// check if the env exists -> loc will be - 1 if it doesn't
	//printf("SIZE: %d || LOC: %d\n", size, loc);
	new_envparams = malloc(sizeof(char *) * (size));
	if (!new_envparams)
		return (-1);
	while (i < size - 1)
	{
		if (i == loc)
			i++;
		new_envparams[x] = env_dup(minishell->envparams[i]);
		i++;
		x++;
	}
	new_envparams[x] = 0;

	//free envparams and link new array
	i = 0;
	while (minishell->envparams[i])
	{
		free(minishell->envparams[i]);
		i++;
	}
	free(minishell->envparams);
	minishell->envparams = new_envparams;
	return (0);
}
