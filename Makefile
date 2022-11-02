NAME = minishell

$(NAME):
		@gcc srcs/* -lreadline -o minishell
re:
		@rm minishell && make
