CC	= gcc

CCFLAGS	= -Wall -Wextra -Werror

INCLUDES= -I /usr/local/opt/readline/include

LIB	= -l readline -L /usr/local/opt/readline/lib

NAME	= minishell

RESET	= \033[0m
BLACK	= \033[0;30m
RED	= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
CYAN	= \033[0;36m
WHITE 	= \033[0;37m

BOLDBLACK	= \033[1m\033[30m
BOLDRED		= \033[1m\033[31m
BOLDGREEN	= \033[1m\033[32m
BOLDYELLOW	= \033[1m\033[33m
BOLDBLUE	= \033[1m\033[34m
BOLDMAGENTA	= \033[1m\033[35m
BOLDCYAN	= \033[1m\033[36m
BOLDWHITE	= \033[1m\033[37m

SRC_DIR		= srcs/
BUILTIN_DIR	= builtins/

SRC_LIST	= check_syntax.c\
		  debug_utils.c\
		  env_utils.c\
		  error.c\
		  exec_utils.c\
		  execute_cmd.c\
		  pipeline.c\
		  expanding.c\
		  ft_build_cmd.c\
		  get_path.c\
		  initializing.c\
		  main.c\
		  read_exec.c\
		  reset_line.c\
		  tokenize_line.c\
		  utils1.c\
		  utils2.c\
		  utils3.c\
		  utils4.c\
		  utils5.c\
		  word_parse.c\
		  word_parse2.c\
		  redirect.c

BUILTIN_LIST	=	cd.c\
			echo.c\
			env.c\
			exit.c\
			export.c\
			pwd.c\
			unset.c

SRC	=	$(addprefix $(SRC_DIR), $(SRC_LIST))\
		$(addprefix $(BUILTIN_DIR), $(BUILTIN_LIST))

OBJ 	= $(SRC:%.c=%.o)

BOBJS	= $(BONUS:%.c=%.o)

#end of variable definitions

all: $(NAME) 

$(NAME): $(OBJ)
	 @$(CC) $(CCFLAGS) $(LIB) $(OBJ) $(INCLUDES) -o $@
	 @printf "\n[COMPILED]\n" 

%.o: %.c
	@printf "$(GREEN).$(RESET)"
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@ 

clean: 
	@rm -f $(OBJ)
	@printf "$(RED)[CLEAN]\n$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@printf "[FCLEAN]\n"

re: fclean all

test:
	echo "test $(RED)test"

.PHONY: test clean fclean all re
