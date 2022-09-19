/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:03:28 by sneyt             #+#    #+#             */
/*   Updated: 2022/09/19 12:07:25 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char *line;
	char *user;

	user = getenv("USER");
	printf("%s\n", user);
	while(1)
	{
		line = readline(">$");
		if (ft_strcmp(line, "exit") == 0)
			break ;
		add_history(line);
	}
}
