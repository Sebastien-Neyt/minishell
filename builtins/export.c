/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:17 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/21 09:38:25 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_for_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i + 1] == '=')
				return (0);
			return (i);
		}
		i++;
	}
	return (0);
}

static char	*cut_env_name(char *str, int index)
{
	char	*ans;
	int		x;

	x = 0;
	ans = malloc(sizeof(char) * index);
	if (!ans)
		return (NULL);
	while (x < index)
	{
		ans[x] = str[x];
		x++;
	}
	ans[x] = '\0';
	return (ans);
}

static char	*cut_env_value(char *str, int index)
{
	char	*ans;
	int		x;

	x = 0;
	ans = malloc(sizeof(char) * (ft_strlen(str) - index));
	if (!ans)
		return (NULL);
	index++;
	while (str[index])
	{
		ans[x] = str[index];
		x++;
		index++;
	}
	ans[x] = '\0';
	return (ans);
}

void	export_loop(t_shell *minishell)
{
	int	count;
	int	i;

	i = 1;
	count = 0;
	while (minishell->cmd.arg[count])
		count++;
	if (count == 1)
		ft_export(minishell, 0);
	else
	{
		while (i < count)
		{
			ft_export(minishell, i);
			i++;
		}
	}
}

int	ft_export(t_shell *minishell, int i)
{
	int	index;	

	if (!minishell->cmd.arg[1])
		ft_env(minishell);
	else
	{
		index = check_for_equal(minishell->cmd.arg[i]);
		if (!index)
		{
			g_exit_code = 256;
			return (error_msg("export : not a valid identiefier\n", 1));
		}
		set_env(cut_env_name(minishell->cmd.arg[i], index), \
		cut_env_value(minishell->cmd.arg[i], index), minishell);
	}
	g_exit_code = 0;
	return (0);
}
