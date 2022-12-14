/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:46:33 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/16 14:19:20 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	ft_echo(t_shell *minishell)
{
	char *args[4] = {"echo", "-n", "this is a test", NULL};
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	while (args[i] && !ft_strcmp(args[i], "-n"))
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
	}
	if (new_line)
		printf("\n");
		//write(1, "\n", 1);	
	return (1);	
}

