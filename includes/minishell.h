/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:04:20 by sneyt             #+#    #+#             */
/*   Updated: 2022/09/19 12:08:20 by sneyt            ###   ########.fr       */
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

# define RESET "\033[0m"
# define GREEN "\033[32m"
# define BOLDGREEN "\033[1m\033[32m"

typedef struct s_shell {
	char	**envparams;
} 	t_shell;

int	ft_strcmp(char const *s1, char const *s2);
//////////////////////////////////////////////////
size_t	ft_strlen(char const *str);
size_t	ft_strlcpy(char *dst, char const *src, size_t maxlen);
static size_t	ft_wordcounter(char *s, char c);
static void	ft_free_all(char **ans);
static int	ft_wordmalloc(char *s, char c, size_t amount, char **ans);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *s1);
/////////////////////////////////////////////////

#endif
