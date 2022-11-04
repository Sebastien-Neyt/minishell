
/*
void

int	main(int argc, char *argv[], char *envp[])
{
	t_shell minishell;

	init_shell_struct(&minishell);
	if (argc > 1)
		//some error
	sig_init();
	init_envs(&minishell, envp);
	read_exec_loop(&minishell);
	while ()
	{
		minishell.line = readline("minishell");
		if (minishell.line == NULL)
			//TODO
		parse_line(&minishell);
		tokenize_line(&minishell);
		execute_line(&minishell);
		rl_add_history(line);
	}
	terminate();
	return (1);
}
*/
