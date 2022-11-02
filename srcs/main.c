/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:44:30 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/02 14:49:47 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell minishell;
	
	minishell = init_shell(argv, envp);

	
	char *line = "<Makefile cat| echo \"$PWD 'hola'\" ~/src | 'tr' -d / >outfile";
	
	word_parse(line, &minishell);

	while (minishell.list->next)
	{
		printf("%s\n", minishell.list->word);
		minishell.list = minishell.list->next;
	}
	printf("%s\n", minishell.list->word);
	/*
	print_envs(&minishell);
	printf("\n\n");
	set_env("USERNAME", "S0cr@tes", &minishell);
	print_envs(&minishell);
	set_env("USERNAME", "Cycollar", &minishell);
	set_env("PWD", "THISISATEST", &minishell);
	print_envs(&minishell);
	*/
	
	return (0);
}
