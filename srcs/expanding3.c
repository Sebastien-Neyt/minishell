/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:15:54 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 16:18:13 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_one_of(char c)
{
	if (c == 34 || is_whitespace(c) || c == '\0')
		return (1);
	return (0);
}

void	set_signalenv(t_shell *minishell)
{
	char str[4];
	int nbr;

	nbr = g_exit_code;
	str[0] = nbr / 100 + '0';
	str[1] = (nbr / 10) % 10 + '0';
	str[2] = nbr % 10 + '0';
	str[3] = '\0';
	if (str[0] == '0')
	{
		str[0] = str[1];
		if (str[1] == '0')
		{
			str[1] = '\0';
			str[0] = str[2];
		}
		else
			str[1] = str[2];
		str[2] = '\0';
	}
	set_env("?", str, minishell);
}
