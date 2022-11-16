/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:01:40 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/16 14:24:04 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_compare(char *env, int len, char *envparam)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (env[i] != envparam[i])
			return (0);
		i++;
	}
	return (1);
}

int	find_env(char *env, t_shell *minishell)
{
	int	i;
   	int	x;

	x = 0;
	i =	ft_strlen(env);
	while (minishell->envparams[x])
	{
		if (env_compare(env, i, minishell->envparams[x]))
			return (x);
		x++;
	}
	return (-1);
}

char *build_env(char *env, char *value)
{
	int	i;
	int x;
	int	len;
	char *new_env;

	len = ft_strlen(value) + ft_strlen(env) + 2;
	i = 0;
	x = 0;
	new_env = malloc(sizeof(char) * len);
	if (!new_env)
		return (NULL);
	while (i < len)
	{
		while (x < ft_strlen(env))
		{
				new_env[i] = env[x];
				i++;
				x++;
		}
		new_env[i] = '=';
		i++;
		x = 0;
		while (x < ft_strlen(value))
		{
			new_env[i] = value[x];
			x++;
			i++;
		}
		i++;
	}
	new_env[i] = '\0';
	return (new_env);
}

int	change_env(t_shell *minishell, int index, char *value, char *env)
{
	char *new_env;
	new_env = build_env(env, value);
	if (!new_env)
		return (0);
	free(minishell->envparams[index]);
	minishell->envparams[index] = new_env;
	return (1);
}

void copy_envp(t_shell *minishell, char **old_env, char *new_env)
{
	int	i;
	int size;

	size = env_counter(minishell->envparams);
	i = 0;
	while (i < size)
	{
		old_env[i] = env_dup(minishell->envparams[i]);
		i++;
	}
	old_env[i] = new_env;
	i++;
	old_env[i] = 0;
}

int	add_env(char *env, char *value, t_shell *minishell)
{
	char *new_env;
	char **old_env;
	int size;

	new_env = build_env(env, value);
	if (!new_env)
		return (0);	
	size = env_counter(minishell->envparams);
	old_env = malloc(sizeof(char *) * size + 2);
	copy_envp(minishell, old_env, new_env);	
	free_env(minishell);
	minishell->envparams = old_env;
	return (1);
}

int	set_env(char *env, char *value, t_shell *minishell)
{
	int	index;

	index = find_env(env, minishell);
	if (index < 0)
		add_env(env, value, minishell);
	else
		if (!change_env(minishell, index, value, env))
			return (error_msg("failed changing env", 0));
	return (1);
}

