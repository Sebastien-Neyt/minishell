NAME = minishell

$(NAME):
		@cd libft && make
		@gcc srcs/*.c libft/libft.a -lreadline -o minishell
		@cd bin/pwd && gcc pwd_cmd.c -o pwd
		@cd bin/echo && gcc echo_cmd.c ../../srcs/utils.c -o echo
all:
		@gcc srcs/*.c  libft/libft.a -lreadline -o minishell
		@cd bin/pwd && gcc pwd_cmd.c -o pwd
		@cd bin/echo && gcc echo_cmd.c ../../srcs/utils.c -o echo
re:
		@rm minishell && rm bin/pwd/pwd && rm bin/echo/echo && make
