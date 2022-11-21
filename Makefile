NAME = minishell

$(NAME):
		@gcc srcs/*.c builtins/*.c -lreadline -o minishell
re:
		@rm minishell && make
