/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:03:28 by sneyt             #+#    #+#             */
/*   Updated: 2022/10/03 15:34:35 by sneyt            ###   ########.fr       */
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
		minishell->envparams[i] = ft_strdupv2(envp[i]);
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
	int	i;
	char *user;
	
	minishell = malloc(sizeof(t_shell *));
	if (init_envs(minishell, envp))
	{
		printf("Error while initializing env\n");
		exit(1);
	}
	while(1)
	{
		i = 0;
		user = ft_strjoin(getenv("USER"), "@minishell >$ ");
		line = readline(user);
		if (line == 0)
			exit(1);
		if (line[0] == 0)
			continue ;
		cmd_list = ft_split(line, ' ');
		if (ft_strcmpv2(cmd_list[0], "exit") == 0)
			break ;
		if (ft_strcmpv2(cmd_list[0], "pwd") == 0)
		{	
			pid = fork();
			if (pid == 0)
				execve("bin/pwd/pwd", NULL, NULL);
			wait(NULL);
		}
	/*
		if (ft_strcmpv2(cmd_list[0], "cd") == 0)
		{
			//printf("%s\n", cmd_list[1]);
			chdir("/Users/sneyt");
			init_envs(minishell, envp);
		}
	*/
		if (ft_strcmpv2(cmd_list[0], "su") == 0)
		{
			pid = fork();
			if (pid == 0)
				execve("/usr/bin/su", cmd_list, NULL);
			wait(NULL);
		}
		if (ft_strcmpv2(cmd_list[0], "env") == 0)
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
		if (ft_strcmpv2(cmd_list[0], "echo") == 0)
		{
			pid = fork();
			if (pid == 0)
				execve("bin/echo/echo", cmd_list, NULL);
			wait(NULL);
		}
		add_history(line);
		if (line)
			free(line);
	}
}
