/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:52:59 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 13:12:52 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Change the getenv to my custom env

char	*get_env(char *env, t_shell *minishell)
{
	char	*ans;
	int		i;
	int		len;

	i = find_env(env, minishell);
	len = ft_strlen(minishell->envparams[i]) - ft_strlen(env) + 1;
	ans = ft_substr(minishell->envparams[i], (ft_strlen(env) + 1), len);
	return (ans);
}

void	ft_cd(t_shell *minishell)
{
	char	*path;
	char	*oldpwd;

	oldpwd = get_env("PWD", minishell);
	if (minishell->cmd.arg[1])
		path = minishell->cmd.arg[1];
	else
		path = get_env("HOME", minishell);
	if (chdir(path) == -1)
	{	
		g_exit_code = 1;
		error_msg("minishell : No such file or directory.\n", 0);
		return ;
	}
	else
	{
		path = getcwd(NULL, 0);
		set_env("OLDPWD", oldpwd, minishell);
		set_env("PWD", path, minishell);
		free(oldpwd);
		free(path);
	}
	g_exit_code = 0;
}
