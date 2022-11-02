/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:03:29 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/02 13:59:09 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_counter(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	init_envs(t_shell *minishell, char **envp)	
{
	int	i;
	int	count;

	i = 0;
	count = env_counter(envp);
	minishell->envparams = malloc(sizeof(char *) * (count + 1));
	if (!minishell->envparams)
		return (1);
	while (i < count)
	{
		minishell->envparams[i] = env_dup(envp[i]);
		if (!minishell->envparams[i])
			return (1);
		i++;
	}
	minishell->envparams[i] = NULL;
	return (0);
}

// change env SSHL - PATH - PWD

t_shell init_shell(char **argv, char **envp)
{
	t_shell minishell;
	
	init_envs(&minishell, envp);
	minishell.list = ft_lstnew(NULL);
	return (minishell);
}
