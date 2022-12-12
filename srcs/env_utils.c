/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:01:40 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/12 09:17:25 by sneyt            ###   ########.fr       */
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

//this one looks for a env in minishell->envparams.
//if there is a match it returns the index, otherwise it returns -1
int	find_env(char *env, t_shell *minishell)
{
	int	i;
	int	x;

	x = 0;
	i = ft_strlen(env);
	while (minishell->envparams[x])
	{
		if (env_compare(env, i, minishell->envparams[x]))
			return (x);
		x++;
	}
	return (-1);
}

//this one creates the env string. it basically appends the env with 
//a '=' and the value.
char	*build_env(char *env, char *value)
{
	int		i;
	int		x;
	int		len;
	char	*new_env;

	len = ft_strlen(value) + ft_strlen(env) + 2;
	i = 0;
	x = 0;
	new_env = malloc(sizeof(char) * len);
	if (!new_env)
		return (NULL);
	while (env[x])
			new_env[i++] = env[x++];
	new_env[i] = '=';
	i++;
	x = 0;
	while (value[x])
		new_env[i++] = value[x++];
	new_env[i] = '\0';
	return (new_env);
}

//this one replaces the env in our envparam with the new value.
int	change_env(t_shell *minishell, int index, char *value, char *env)
{
	char	*new_env;

	new_env = build_env(env, value);
	if (!new_env)
		return (0);
	free(minishell->envparams[index]);
	minishell->envparams[index] = new_env;
	return (1);
}

//here we create a copy of our current minishell->envparams
void	copy_envp(t_shell *minishell, char **old_env, char *new_env)
{
	int	i;
	int	size;

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

//if its a new env that does not yet exist. we add it to 
//the minishell->envparams array.
int	add_env(char *env, char *value, t_shell *minishell)
{
	char	*new_env;
	char	**old_env;
	int		size;

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

//this is the global env function that will check if the env already exists
//or not and then decide if we change if we have to change or add the env
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
