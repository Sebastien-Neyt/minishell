
/*
void	read_exec_loop(t_shell *minishell)
{
	while (1)
	{
		minishell->line = readline("minishell");
		if (minishell.line == NULL)
			ft_exit(NULL, minishell);
		parse_line(&minishell);
		tokenize_line(&minishell);
		while (!minishell->line_done)
			append_line(minishell);
		execute_line(&minishell);
		rl_add_history(minishell->line);
		free(minishell->line);
		minishell->line = NULL;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell minishell;

	init_shell_struct(&minishell);
	if (argc > 1)
		terminate(NULL, ERR_ARGNBR);
	sig_init();
	init_envs(&minishell, envp);
	read_exec_loop(&minishell);
	terminate(&minishell, NULL);
	return (1);
}
*/
