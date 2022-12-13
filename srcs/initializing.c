/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:03:29 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/12 17:04:47 by sneyt            ###   ########.fr       */
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

static void	init_env_empty(t_shell *minishell)
{
	
	minishell->envparams = malloc(sizeof(char *) * 3);
	minishell->envparams[0] = NULL;
	set_env("PWD", getcwd(NULL, 0), minishell);
	printf("env = %s\n", minishell->envparams[0]);
	set_env("SHLVL", "1", minishell);
	printf("env = %s\n", minishell->envparams[1]);
	set_env("_", "usr/bin/env", minishell);
	printf("env = %s\n", minishell->envparams[2]);
}

int	init_envs(t_shell *minishell, char **envp)	
{
	int	i;
	int	count;

	i = 0;
	/*
	if (!envp)
	{
		init_env_empty(minishell);
		return (0);
	}
	*/
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

t_shell init_shell(char **envp)
{
	t_shell minishell;
	//printf("%s\n", envp[0]);
	if (!envp[0])
		init_env_empty(&minishell);
	else
		init_envs(&minishell, envp);
	minishell.list = ft_lstnew(NULL);
	minishell.pipeline = ft_lstnew(NULL);
	minishell.pipeline_start = NULL;
	cmd_init(&minishell);
	
	minishell.pid = NULL;
	minishell.line = NULL;
	minishell.line_tmp = NULL;

	minishell.nbr_pipe = 0;
	return (minishell);
}
