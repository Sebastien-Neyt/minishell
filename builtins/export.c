/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:17 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/13 12:32:03 by sneyt            ###   ########.fr       */
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
			return (i);
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
	// Proctection malloc
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
	// Protection malloc
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

int	ft_export(t_shell *minishell)
{
	int	index;	

	if (!minishell->cmd.arg[1])
		ft_env(minishell);
	else
	{
		index = check_for_equal(minishell->cmd.arg[1]);
		if (!index)
			return (printf("returning 0\n"));
		set_env(cut_env_name(minishell->cmd.arg[1], index), \
		cut_env_value(minishell->cmd.arg[1], index), minishell);
	}
	return (1);
}
