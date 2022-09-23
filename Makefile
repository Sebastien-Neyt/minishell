NAME = minishell

$(NAME):
		@gcc srcs/*.c -lreadline -o minishell
		@cd bin/pwd && gcc pwd_cmd.c -o pwd
all:
		@gcc srcs/*.c -lreadline -o minishell
		@cd bin/pwd && gcc pwd_cmd.c -o pwd

re:
		@rm minishell && rm bin/pwd/pwd rm && make
