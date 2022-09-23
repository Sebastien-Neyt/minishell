# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccollard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 11:47:57 by ccollard          #+#    #+#              #
#    Updated: 2019/11/18 11:48:06 by ccollard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= gcc

CCFLAGS	= -Wall -Wextra -Werror

NAME	= pipex

BLACK	= \033[0;30m
RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
CYAN	= \033[0;36m
WHITE 	= \033[0;37m

#SRCDIR	= src/

SRC	=	main.c \
		proc1.c \
		proc2.c \
		ft_strlen.c \
		ft_strjoin.c \
		ft_strndup.c \
		ft_strlcpy.c \
		ft_split.c \
		test_command.c \
		get_path.c

OBJ 	= $(SRC:%.c=%.o)

BOBJS	= $(BONUS:%.c=%.o)

#end of variable definitions

all: $(NAME)

$(NAME): $(OBJ) pipex.h
	 @$(CC) $(CCFLAGS) $(OBJ) -o $@
	 @printf "\n[COMPILED]" 

%.o: %.c
	@printf "$(GREEN)."
	@$(CC) $(CCFLAGS) -c $< -o $@ 

clean: 
	@rm -f $(OBJ)
	@printf "$(RED)[CLEAN]\n"

fclean: clean
	@rm -f $(NAME)
	@printf "[FCLEAN]\n"

re: fclean all

test:
	echo "test $(RED)test"

.PHONY: test clean fclean all re
