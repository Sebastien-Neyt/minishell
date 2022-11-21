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

# define TILDE 1
# define DOLLAR 0

# define PIPE 10
# define RED_INPUT 11
# define RED_OUTPUT 12
# define RED_APPEND 101
# define RED_HEREDOC 102

typedef struct s_cmd {
	int	fd_out;
	int	fd_in;
	char	*name;
	char 	*path;
	char	**arg;
	char	**envp;
}	t_cmd;

typedef enum token {
	DEFAULT,
	SINGLE,
	DOUBLE,
}	e_token;

typedef struct s_list {
	char *word;
	struct s_list *next;
	e_token token;
}	t_list;

typedef struct s_shell {
	char	**envparams;
	char 	*line;
	char 	*line_tmp;
	t_list	*list;
	t_list	*pipeline;

}	t_shell;

// main.c
int	check_for_exp(t_shell *minishell);
int	check_chars(char *word);

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
int	ft_strcmp(char *s1, char *s2);
char *ft_strdup(char *s1);
char *ft_strtrim(char *s1, char *set);
char	*ft_strjoin(char const *s1, char const *s2);

// initializing.c
t_shell	init_shell(char **argv, char **envp);
int	env_counter(char **envp);
int	init_envs(t_shell *minishell, char **envp);

// unset.c
int	ft_unset(t_shell *minishell);

// export.c
int	ft_export(t_shell *minishell);

// env.c
int	ft_env(t_shell *minishell);

// echo.c
int	ft_echo(t_shell *minishell);

// pwd.c
int	ft_pwd(t_shell *minishell);

// debug_utils.c
void	print_envs(t_shell *minishell);
void	print_list(t_shell *minishell);
void	test_expansions(t_shell *minishell);

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
int		is_whitespace(char c);
char 	*build_word(int i, int offset, char *line);
void	add_word(t_shell *minishell, char *word, int flag);
int		check_quote(int type, char *line, int i);


// expanding.c
char *get_var(char *str, int i);
int check_expansion(char *str, t_shell *minishell, t_list *node);
int	check_in_env(char *env_var, t_shell *minishell);
int	compare_env(char *env_var, char *mini_env);
int expand_varv2(int index, t_shell *minishell, char *env_var, t_list *node, int macro);

// word_parse2.c
int	word_subparse(char *line, t_shell *minishell, e_token token);
int	parse_list(t_shell *minishell);

#endif
