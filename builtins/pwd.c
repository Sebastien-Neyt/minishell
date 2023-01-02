/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:08 by sneyt             #+#    #+#             */
/*   Updated: 2023/01/02 16:57:19 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_shell *minishell)
{
	int		loc;
	char	*pwd;

	loc = find_env("PWD", minishell);
	pwd = get_var(minishell->envparams[loc], 3);
	printf("%s\n", pwd);
	if (pwd)
		free(pwd);
	return (0);
}
