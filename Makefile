NAME = minishell

$(NAME):
		@gcc srcs/*.c -lreadline -o minishell
all:
		@gcc srcs/*.c -lreadline -o minishell

re:
		@rm minishell && make
