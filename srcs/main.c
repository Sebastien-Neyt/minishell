/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:03:28 by sneyt             #+#    #+#             */
/*   Updated: 2022/10/04 16:20:51 by sneyt            ###   ########.fr       */
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

int	quote_error(char *string)
{
	int	type;
	int	flag_closed;
	int	i;

	i = 0;
	flag_closed = 1;
	while (string[i])
	{
		if (string[i] == 39)
		{
			if (flag_closed == 1)
			{
				type = 1;
				flag_closed = 0;
			}
			else if (type == 1)
				flag_closed = 1;
		}
		if (string[i] == 34)
		{
			if (flag_closed == 1)
			{
				type = 2;
				flag_closed = 0;
			}
			else if (type == 2)
				flag_closed = 1;
		}
		i++;	
	}
	if (!flag_closed)
	{
		if (type == 1)
			printf("squote> ");
		if (type == 2)
			printf("dquote >");
		return (1);
	}
	return (0);
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
		i++;
	}
	minishell->envparams[i] = NULL;
	return (0);
}

int	temp_builtin(t_shell *minishell)
{
	int	i;
	int pid;
	i = 0;
	if (ft_strcmpv2(minishell->cmd_list[0], "exit") == 0)
		return (1);
	if (ft_strcmpv2(minishell->cmd_list[0], "pwd") == 0)
	{	
		pid = fork();
		if (pid == 0)
			execve("bin/pwd/pwd", NULL, NULL);
		wait(NULL);
	}
	if (ft_strcmpv2(minishell->cmd_list[0], "su") == 0)
	{
		pid = fork();
		if (pid == 0)
			execve("/usr/bin/su", minishell->cmd_list, NULL);
		wait(NULL);
	}
	if (ft_strcmpv2(minishell->cmd_list[0], "env") == 0)
	{
		while (minishell->envparams[i])
		{
			printf("%s\n", minishell->envparams[i]);
			i++;
		}
	}
	if (ft_strcmpv2(minishell->cmd_list[0], "echo") == 0)
	{
		pid = fork();
		if (pid == 0)
			execve("bin/echo/echo", minishell->cmd_list, NULL);
		wait(NULL);
	}
	return (0);
}

int	ft_readline(t_shell *minishell, char **line)
{
	char *user;
	int line_error;

	user = ft_strjoin(getenv("USER"), "@minishell >$ ");
	*line = readline(user);
	if (*line == 0)
		return (2);
	if (*line[0] == 0)
		return (1);
	line_error = quote_error(*line);
	while (line_error == 1)
	{
		*line = ft_strjoin(*line, readline(""));	
		if (!quote_error(*line))
			line_error = 0;
	}
	return (0);
}



void	ft_build_blocks(t_shell *minishell, char *line)
{
	t_list *block;
	int	i;
	int	operator;
	char *temp;
	int y;

	y = ft_strlen(line);
	i = 0;
	while (i < y)
	{
		//operator = 0;
		if (line[i] == 124 || line[i] == 60 || line[i] == 62)
		{
			operator = 1;
			if ((line[i] == 60 && line[i + 1] == 60) || (line[i] == 62 && line[i + 1]))
			   	operator = 2;

			if (i == 0 && operator == 1)
				temp = ft_substr(line, 0, 1);	
			else
				temp = ft_substr(line, 0, i - 1);

			//printf("%s\n", temp);

			block = ft_lstnew(temp);
			//if (!minishell->blocks->content)
			if (minishell->blocks)
				ft_lstadd_back(&minishell->blocks, block);
			else
				minishell->blocks = block;

			if (operator == 1)
			{
				if (line[i] == 124)
					block = ft_lstnew("|");
				else if (line[i] == 60)
					block = ft_lstnew("<");
				else if (line[i] == 62)
					block = ft_lstnew(">");
			}
			else
			{
				if (line[i] == 60)
					block = ft_lstnew("<<");
				else if (line[i] == 63)
					block = ft_lstnew(">>");
				//block = ft_lstnew(ft_strjoin(line[i], line[i + 1]));
			}

			ft_lstadd_back(&minishell->blocks, block);
			if (operator == 1 && i == 0)
				line = ft_substr(line, i + 1, ft_strlen(line) - i);
			else
				line = ft_substr(line, i, ft_strlen(line) - 1);
			printf("%s\n", line);

			y -= i;
			i = 0;
		}
		else
			i++;
	}
	

	/*
	char *test = "lets' see if this works";
	block = ft_lstnew(test);
	minishell->blocks = block;
	block = ft_lstnew(test);
	ft_lstadd_back(&minishell->blocks, block);
	//printf("size of list: %d\n", ft_lstsize(minishell->blocks));
	printf("%s \n%s\n", minishell->blocks->content, minishell->blocks->next->content);
	//printf("%s \n", minishell->blocks->content);
	*/
	printf("%s \n%s\n%s\n", minishell->blocks->content, minishell->blocks->next->content, minishell->blocks->next->next->content);
}

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	t_shell *minishell;
	char *user;
	int	i;
	
	minishell = malloc(sizeof(t_shell *));
	//minishell->blocks = malloc(sizeof(t_list *));
	//minishell->blocks = ft_lstnew("hello");
	if (init_envs(minishell, envp))
	{
		printf("Error while initializing env\n");
		exit(1);
	}
	while(1)
	{
		//minishell->blocks = malloc(sizeof(t_list *));
		minishell->blocks = NULL;
		//minishell->blocks->content = 0;

		i = ft_readline(minishell, &line);
		ft_build_blocks(minishell, line);
		if (i == 1)
			continue;
		if (i == 2)
			exit(1);

		minishell->cmd_list = ft_split(line, ' ');

		if (temp_builtin(minishell))
			break ;
		add_history(line);
		if (line)
			free(line);
		free(minishell->blocks);
	}
}
