/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:20:37 by sneyt             #+#    #+#             */
/*   Updated: 2022/10/03 11:07:47 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_var(char *str)
{
	int	i = 0;

	if (str[i] == '$')
	{
		i++;
		if (str[i] == '$')
			printf("%d", getpid());
		else
		{
			
		}
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int	n_status;
	int	i;

	i = 1;
	n_status = 0;
	// Make it catch env's -> $HOME
	
	while (argv[i] && !check_for_var(argv[i]))
	{
		if (ft_strcmpv2(argv[i], "-n") == 0)
		{
			n_status = 1;
			i++;
		}
		printf("%s", argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (!n_status)
		printf("\n");
	return (0);
}
