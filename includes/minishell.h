/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:45:38 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/02 14:00:17 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

//# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_block {
	int	infile;
	int	outfile;
	char **cmd;
	char *path;
}	t_block;


typedef struct s_list {
	char *word;
	struct s_list *next;
}	t_list;

typedef struct s_shell {
	char	**envparams;
	t_list	*list;
}	t_shell;

// error.c
int	ft_strlen(char *str);
int	error_msg(char *err, int ret);
void	free_env(t_shell *minishell);

// utils1.c
char	*env_dup(char *s1);
int	ft_strlen(char *str);
t_list *ft_lstnew(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);

// initializing.c
t_shell	init_shell(char **argv, char **envp);
int	env_counter(char **envp);
int	init_envs(t_shell *minishell, char **envp);

// debug_utils.c
void	print_envs(t_shell *minishell);

// env_utils.c
int	find_env(char *env, t_shell *minishell);
int	env_compare(char *env, int len, char *envparam);
char *build_env(char *env, char *value);
int	change_env(t_shell *minishell, int index, char *value, char *env);
int	set_env(char *env, char *value, t_shell *minishell);
void	copy_envp(t_shell *minishell, char **old_env, char *new_env);
int	add_env(char *env, char *value, t_shell *minishell);

// word_parse.c
void	word_parse(char *line, t_shell *minishell);


#endif
