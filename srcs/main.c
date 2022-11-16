/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:44:30 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/16 14:22:48 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_chars(char *word)
{
	int	i;
	
	i = 0;
	while (word && word[i])
	{
		if (word[i] == '$' || word[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

int	check_for_exp(t_shell *minishell)
{
	t_list *tmp;

	tmp = minishell->list;
	while (tmp)
	{
		while (check_chars(tmp->word))
		{
			if (tmp->token == SINGLE)
			{
				tmp = tmp->next;
				continue;
			}
			check_expansion(tmp->word, minishell, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}

void trim_pipeline(t_shell *minishell)
{
	t_list *tmp;
	tmp = minishell->pipeline;
	while (tmp)
	{
		printf("TOKEN: %d || WORD: %s\n", tmp->token, tmp->word);
		if (tmp->token == DOUBLE)
			tmp->word = ft_strtrim(tmp->word, "\"");
		else if (tmp->token == SINGLE)
			tmp->word = ft_strtrim(tmp->word, "'");
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell minishell;
	char *line = "<<Make>>file|  '$TEST'  cat| echo ~ \"$PWD $SHELL << 'hola'\" ~/src | 'tr' -d $SEEIFTHISONEWORKS / >out>file|";	

	minishell = init_shell(argv, envp);
	minishell.pipeline = ft_lstnew(NULL);	
	word_parse(line, &minishell);
	check_for_exp(&minishell);

	//print_list(&minishell);

	ft_env(&minishell);
	//ft_echo(&minishell);		
		
	ft_export(&minishell);
	printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Exporting USER to testing/hello/... @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
	ft_env(&minishell);
	ft_unset(&minishell);
	printf("\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Unsetting USER@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
	ft_env(&minishell);

/*
	parse_list(&minishell);
	trim_pipeline(&minishell);
	minishell.list = minishell.pipeline;
	print_list(&minishell);
	*/
	//ft_pwd(&minishell);
	return (0);
}

/*
 *
void	append_line(t_shell *minishell)
{
	minishell->line_tmp = minishell->line;
	minishell->line = readline(">");
	if (minishell->line == NULL)
		ft_exit(minishell, UNXPCTD_EOF);
	parse_line(minishell);
	tokenize_line(minishell);
	check_syntax(minishell);
	join_line(minishell); //TODO should join the 2 lines, replace the line
}
 *
 * launch an ifinite loop that will:
 *	readline
 *	parse_line
 *	tokenize_line
 *	check syntax of the tokenized line
 *	append_line while line not done (ex: pipe token at the end of line)
 *	add to history
 *	free line
 *	repeat
 *
void	read_exec_loop(t_shell *minishell)
{
	while (1)
	{
		minishell->line = readline("minishell");
		if (minishell.line == NULL)
			ft_exit(minishell, NULL, DEFAULT);
		parse_line(minishell);
		tokenize_line(minishell);
		check_syntax(minishell);
		while (!minishell->line_done)
			append_line(minishell);
		execute_line(minishell);
		rl_add_history(minishell->line);
		clear_line(minishell);
	}
}
*
*
* declare struct
* initialize struct
* check arg nbr
* initialize signals
* call the main read exec loop
* the program will call exit() from within the loop
* neither the terminate nor the return should ever be reached
*
int	main(int argc, char *argv[], char *envp[])
{
	t_shell minishell;

	init_shell_struct(&minishell);
	if (argc > 1)
		ft_exit(NULL, NULL, ERR_ARGNBR);
	sig_init();
	init_envs(&minishell, envp);
	read_exec_loop(&minishell);
	ft_exit(&minishell, NULL, "unexpected error");
	return (1);
}
*
*  "bash: syntax error: unexpected end of file"
*  shell-init: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
*/
