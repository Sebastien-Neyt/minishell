/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:18:53 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 09:19:15 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 *
 */
int	test_path(char *prefix, char *cmd)
{
	char	*path;
	int		ret;

	ret = -1;
	path = ft_strjoin(prefix, cmd);
	if (path == NULL)
		return (ret);
	if (access(path, X_OK) == 0)
		ret = 0;
	free(path);
	return (ret);
}

/*
 *
 */
char	*make_path(t_shell *minishell)
{
	char	**prefix;
	char	**save_p;
	char	*path;
	char	*tmp;

	path = NULL;
	if (find_env("PATH", minishell) == -1)
		return (NULL);
	prefix = ft_split(\
minishell->envparams[find_env("PATH", minishell)] + 5, ':');
	save_p = prefix;
	if (prefix == NULL)
		ft_exit(minishell, FAILED_MALLOC);
	while (*prefix)
	{
		tmp = *prefix;
		*prefix = ft_strjoin(*prefix, "/");
		free(tmp);
		if (path == NULL && test_path(*prefix, (minishell->cmd).name) == 0)
			path = ft_strjoin(*prefix, (minishell->cmd).name);
		free(*prefix);
		prefix++;
	}
	free(save_p);
	return (path);
}

/* check if name of command exist
 * check if executable exist in local directory
 * call make_path
 * dipslay error message if no command found and return null
 * return command path if command found
 */
char	*get_path(t_shell *minishell)
{
	char	*cmd;

	if ((minishell->cmd).name == NULL)
		return (NULL);
	cmd = ft_strdup(minishell->cmd.name);
	if (cmd == NULL)
		ft_exit(minishell, FAILED_MALLOC);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	cmd = make_path(minishell);
	if (cmd == NULL)
		write(STDERR_FILENO, CMD_NFOUND, ft_strlen(CMD_NFOUND));
	return (cmd);
}
