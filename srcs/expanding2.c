/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:14:09 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/20 13:42:40 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// this one will return the name of the VAR in our codeline without the $.
// So $PWD -> PWD
// $SEEIFTHISONEWORKS -> SEEIFTHISONEWORKS
char	*get_var(char *str, int i)
{
	char	*var;
	int		x;
	int		y;
	int		len;

	y = 0;
	x = i + 1;
	while (!is_whitespace(str[x]) && str[x] != '\0'
		&& str[x] != '$' && str[x] != 34 && str[x] != 39)
		x++;
	var = malloc(sizeof(char) * (x - i + 1));
	if (!var)
		return (NULL);
	i++;
	len = x - i;
	while (y < len)
		var[y++] = str[i++];
	var[y] = '\0';
	return (var);
}

//We look if env_var ( Ex: PWD ) is equal to the mini_env we give it.
int	compare_env(char *env_var, char *mini_env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(env_var);
	while (i < len)
	{
		if (env_var[i] != mini_env[i])
			return (0);
		i++;
	}
	return (1);
}

// we loop through the envparams of our minishell to see if there is match
// with env_var we substracted from the line. if we find a match
// we return the index of the match.
// else we return -1 to say there is no match and the env_var does not exist.
int	check_in_env(char *env_var, t_shell *minishell)
{
	int	i;

	i = 0;
	if (!env_var)
		ft_exit(minishell, FAILED_MALLOC);
	while (minishell->envparams[i])
	{
		if (compare_env(env_var, minishell->envparams[i]))
			return (i);
		i++;
	}
	return (-1);
}

//helper function to shorten inital one. this one returns
//env based on the tilde or dollar sign
char	*env_var_based(char c, char *str, int i)
{
	char	*ans;

	ans = NULL;
	if (c == '~')
		ans = env_dup("HOME");
	if (c == '$')
		ans = get_var(str, i);
	return (ans);
}
