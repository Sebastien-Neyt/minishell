/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:17 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/16 15:03:15 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_export(t_shell *minishell)
{
	char *line[2] = {"export", "TEST=testing/hello/"};
	
	//if (argc == 1)
		//ft_env(minishell);
	set_env("CYCOLLAR", "testing/hello/...", minishell);
	//should be added in ascii order?
	return (1);
}
