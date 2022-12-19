/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:12 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 13:12:24 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envparams(t_shell *minishell, char **new_envparams)
{
	int	i;

	i = 0;
	while (minishell->envparams[i])
	{
		free(minishell->envparams[i]);
		i++;
	}
	free(minishell->envparams);
	minishell->envparams = new_envparams;
	g_exit_code = 0;
}

int	ft_unset(t_shell *minishell)
{
	char	**new_envp;
	int		loc;
	int		i;
	int		x;

	if (!minishell->cmd.arg[1])
		return (printf("unset: not enough arguments\n"));
	i = 0;
	x = 0;
	loc = find_env(minishell->cmd.arg[1], minishell);
	if (loc < 0)
		return (0);
	new_envp = malloc(sizeof(char *) * (env_counter(minishell->envparams)));
	if (!new_envp)
		ft_exit(minishell, FAILED_MALLOC);
	while (i < env_counter(minishell->envparams) - 1)
	{
		if (i == loc)
			i++;
		new_envp[x++] = env_dup(minishell->envparams[i++]);
	}
	new_envp[x] = 0;
	free_envparams(minishell, new_envp);
	return (0);
}
