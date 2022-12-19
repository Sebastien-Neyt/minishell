/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:03:29 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 11:46:35 by sneyt            ###   ########.fr       */
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
	char	*temp;

	minishell->envparams = malloc(sizeof(char *) * 4);
	temp = ft_strjoin("PWD=", getcwd(NULL, 0));
	minishell->envparams[0] = env_dup(temp);
	minishell->envparams[1] = env_dup("SHLVL=1");
	minishell->envparams[2] = env_dup("_=usr/bin/env");
	minishell->envparams[3] = NULL;
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
t_shell	init_shell(char **envp)
{
	t_shell	minishell;

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
