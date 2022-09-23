/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:03:28 by sneyt             #+#    #+#             */
/*   Updated: 2022/09/19 12:07:25 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_counter(char **envp)
{
	int i = 0;

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
	minishell->envparams = (char **)malloc(sizeof(char *) * (count + 1));
	if (!minishell->envparams)
		return (1);
	while (i < count)
	{
		minishell->envparams[i] = ft_strdup(envp[i]);
		if (!minishell->envparams[i])
			return (1);
		//printf("%d -->%s\n", i, minishell->envparams[i]);
		i++;
	}
	minishell->envparams[i] = NULL;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	char **cmd_list;
	int pid;
	t_shell *minishell;
	int	i = 0;
	
	minishell = malloc(sizeof(t_shell *));
	if (init_envs(minishell, envp))
	{
		printf("Error while initializing env\n");
		exit(1);
	}
	while(1)
	{
		line = readline(BOLDGREEN "root@minishell >$ " RESET);
		cmd_list = ft_split(line, ' ');
		if (ft_strcmp(cmd_list[0], "exit") == 0)
			break ;
		if (ft_strcmp(cmd_list[0], "pwd") == 0)
		{	
			pid = fork();
			if (pid == 0)
				execve("bin/pwd/pwd", NULL, NULL);
			wait(NULL);
		}
		if (ft_strcmp(cmd_list[0], "env") == 0)
		{
			while (minishell->envparams[i])
			{
				printf("%s\n", minishell->envparams[i]);
				i++;
			}
			/*
			pid = fork();
			if (pid == 0)
				execve("bin/env/env", NULL, NULL);
			wait(NULL);
			*/
		}
		add_history(line);
	}
}
