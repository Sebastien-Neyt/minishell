/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:01:40 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/21 12:52:16 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
}

//if its a new env that does not yet exist. we add it to 
//the minishell->envparams array.
int	add_env(char *env, char *value, t_shell *minishell)
{
	char	*new_env;
	char	**new_envp;
	int		size;

	new_env = build_env(env, value);
	if (!new_env)
		ft_exit(minishell, FAILED_MALLOC);
	size = env_counter(minishell->envparams);
	new_envp = malloc(sizeof(char *) * (size + 2));
	if (!new_envp)
		ft_exit(minishell, FAILED_MALLOC);
	copy_envp(minishell, new_envp, new_env);
	new_envp[size + 1] = NULL;
	free_env(minishell);
	minishell->envparams = new_envp;
	free(env);
	free(value);
	return (1);
}

int	count_occurences(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			count++;
		i++;
	}
	return (count);
}

//this is the global env function that will check if the env already exists
//or not and then decide if we change if we have to change or add the env
int	set_env(char *env, char *value, t_shell *minishell)
{
	int	index;

	if (!env || !value)
		ft_exit(minishell, FAILED_MALLOC);
	env = trim_word(env, minishell, 0, 0);
	value = trim_word(value, minishell, 0, 0);
	index = find_env(env, minishell);
	if (index < 0)
		add_env(env, value, minishell);
	else
		if (!change_env(minishell, index, value, env))
			return (error_msg("failed changing env", 0));
	return (1);
}
