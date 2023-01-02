/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:12 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/21 08:44:04 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envparams(t_shell *minishell, char **new_envparams, int x)
{
	int	i;

	i = 0;
	while (minishell->envparams[i])
	{
		free(minishell->envparams[i]);
		i++;
	}
	free(minishell->envparams);
	new_envparams[x] = 0;
	minishell->envparams = new_envparams;
	g_exit_code = 0;
}

void	unset_loop(t_shell *minishell)
{
	int	count;
	int	x;

	x = 0;
	count = 0;
	while (minishell->cmd.arg[count])
		count++;
	if (count == 1)
		ft_unset(minishell, 0, 0);
	else
	{	
		while (x < count)
		{
			ft_unset(minishell, 0, x);
			x++;
		}
	}
}

int	ft_unset(t_shell *minishell, int i, int y)
{
	char	**new_envp;
	int		loc;
	int		x;

	if (!minishell->cmd.arg[1])
	{
		g_exit_code = 1;
		return (printf("unset: not enough arguments\n"));
	}
	x = 0;
	loc = find_env(minishell->cmd.arg[y], minishell);
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
	free_envparams(minishell, new_envp, x);
	return (0);
}

int	ft_unset_questionmark(t_shell *minishell)
{
	char	**new_envp;
	int		loc;
	int		i;
	int		x;

	i = 0;
	x = 0;
	loc = find_env("?", minishell);
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
	free_envparams(minishell, new_envp, x);
	return (0);
}
