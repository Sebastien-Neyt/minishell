# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccollard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 11:47:57 by ccollard          #+#    #+#              #
#    Updated: 2022/10/04 13:30:46 by sneyt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= gcc

CCFLAGS	= -Wall -Wextra -Werror

NAME	= libft.a

BLACK	= \033[0;30m
RED	= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
CYAN	= \033[0;36m
WHITE 	= \033[0;37m

#SRCDIR	= src/

#BDIR	= bonus/

#INCDIR	= includes/

SRC	= ft_atoi.c\
	  ft_bzero.c\
	  ft_calloc.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_isascii.c\
	  ft_isdigit.c\
	  ft_isprint.c\
	  ft_itoa.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_memcpy.c\
	  ft_memmove.c\
	  ft_memset.c\
	  ft_putchar_fd.c\
	  ft_putendl_fd.c\
	  ft_putnbr_fd.c\
	  ft_putstr_fd.c\
	  ft_split.c\
	  ft_strchr.c\
	  ft_strdup.c\
	  ft_striteri.c\
	  ft_strjoin.c\
	  ft_strlcat.c\
	  ft_strlcpy.c\
	  ft_strlen.c\
	  ft_strmapi.c\
	  ft_strncmp.c\
	  ft_strnstr.c\
	  ft_strrchr.c\
	  ft_strtrim.c\
	  ft_substr.c\
	  ft_tolower.c\
	  ft_toupper.c\
	  ft_lstadd_back.c\
	  ft_lstadd_front.c\
	  ft_lstclear.c\
	  ft_lstdelone.c\
	  ft_lstiter.c\
	  ft_lstlast.c\
	  ft_lstmap.c\
	  ft_lstnew.c\
	  ft_lstsize.c

OBJ 	= $(SRC:%.c=%.o)


#end of variable definitions

all: $(NAME)

$(NAME): $(OBJ) libft.h
	 @ar rcs $@ $(OBJ) libft.h 

%.o: %.c
	@printf "$(GREEN)."
	@$(CC) $(CCFLAGS) -c $< -o $@ 

clean: 
	@rm -f $(OBJ) $(BOBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all


test:
	echo "test $(RED)test"

.PHONY: test clean fclean all re reb
