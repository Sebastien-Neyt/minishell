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

# define RESET "\033[0m"
# define GREEN "\033[32m"
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


int	ft_strcmpv2(char const *s1, char const *s2);
/*
//////////////////////////////////////////////////
size_t	ft_strlen(char const *str);
size_t	ft_strlcpy(char *dst, char const *src, size_t maxlen);
static size_t	ft_wordcounter(char *s, char c);
static void	ft_free_all(char **ans);
static int	ft_wordmalloc(char *s, char c, size_t amount, char **ans);
char	**ft_split(char const *s, char c);
*/
char	*ft_strdupv2(char *s1);
/////////////////////////////////////////////////

#endif
