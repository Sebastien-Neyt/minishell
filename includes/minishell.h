/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:04:20 by sneyt             #+#    #+#             */
/*   Updated: 2022/10/03 11:00:18 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../libft/libft.h"

# define RESET	"\033[0m"
# define BLACK	"\033[0;30m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define BLUE	"\033[0;34m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define WHITE	"\033[0;37m"
# define BOLDGREEN "\033[1m\033[32m"
/*
enum	token_type {
	BUILTIN
}
*/
/*
typedef struct s_token {
	char	*content;
	enum	token_type;
}	t_token;

typedef struct s_job {
	t_job *next;
	t_token content;
}	t_job;
*/	
typedef struct s_shell {
	char	**envparams;
} 	t_shell;
/*
typedef struct s_cmd {
	char	*name;
	char	**args;
	char	**envp;
} 	t_cmd;
*/
// test_command.c
int	test_command(char *argv, char *envp);

int	ft_strcmpv2(char const *s1, char const *s2);
char	*ft_strdupv2(char *s1);
/////////////////////////////////////////////////

#endif
