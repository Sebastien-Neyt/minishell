/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:52:59 by sneyt             #+#    #+#             */
/*   Updated: 2023/01/05 09:27:01 by sneyt            ###   ########.fr       */
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
	if (i < 0)
		return (NULL);
	len = ft_strlen(minishell->envparams[i]) - ft_strlen(env) + 1;
	ans = ft_substr(minishell->envparams[i], (ft_strlen(env) + 1), len);
	return (ans);
}

char	*ft_check_arg(t_shell *minishell)
{
	if (minishell->cmd.arg[1])
		return (ft_strdup(minishell->cmd.arg[1]));
	else
		return (get_env("HOME", minishell));
}

static int	small_checker(char *path, char *oldpwd)
{
	if (!path || !oldpwd)
	{
		if (path)
			free(path);
		if (oldpwd)
			free(oldpwd);
		return (1);
	}
	return (0);
}

void	ft_cd(t_shell *minishell, char *path, char *oldpwd)
{
	if (chdir(path) == -1)
	{	
		g_exit_code = 1;
		if (path)
			free(path);
		if (oldpwd)
			free(oldpwd);
		error_msg("minishell : No such file or directory.\n", 0);
		return ;
	}
	else
	{
		if (path)
			free(path);
		path = getcwd(NULL, 0);
		if (small_checker(path, oldpwd))
			return ;
		set_env(ft_strdup("OLDPWD"), oldpwd, minishell);
		set_env(ft_strdup("PWD"), path, minishell);
	}
	g_exit_code = 0;
}
