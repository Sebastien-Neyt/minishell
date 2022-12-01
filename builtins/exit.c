/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:53:04 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/15 14:53:05 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_exit(t_shell *minishell, char *msg)
{
	if (msg)
		write(STDERR_FILENO, msg ,ft_strlen(msg));
	(void)minishell;
	exit(g_exit_code);
}
