/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:08:56 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 09:10:43 by sneyt            ###   ########.fr       */
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
