/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:52:59 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/12 16:40:02 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Change the getenv to my custom env

void	ft_cd(t_shell *minishell)
{
	char *path;
	char *oldpwd;

	//checking for argument. if not than cd points to HOME
	oldpwd = getenv("PWD");
	if (minishell->cmd.arg[1])
		path = minishell->cmd.arg[1];
	else
		path = getenv("HOME");
	printf("PATH : %s\n", path);	
	if (chdir(path) == -1)
		return; 
		//error because the path does not exist
	else
	{
		set_env("OLDPWD", oldpwd, minishell);
		set_env("PWD", path, minishell);
		//free(oldpwd);
		//free(path);
	}
}

