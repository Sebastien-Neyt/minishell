/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:45:38 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/20 15:20:24 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include "macros.h"

# define TILDE 1
# define DOLLAR 0

// colours
# define BLACK   "\033[0;30m"
# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE    "\033[0;34m"
# define PURPLE  "\033[0;35m"
# define CYAN    "\033[0;36m"
# define WHITE   "\033[0;37m"

int	g_exit_code;

typedef struct s_cmd {
	int		fd_out;
	int		fd_in;
	char	*name;
	char	*path;
	char	**arg;
	char	**envp;
}	t_cmd;
/*
typedef enum token {
	WORD,			 0 
	PIPE,			 1 
	SINGLE,			 2 
	DOUBLE, 		 3 
	SIMPLE_REDIRECT_TO,	 4
	SIMPLE_REDIRECT_FROM,	 5
	DOUBLE_REDIRECT_TO,	 6
	HEREDOC,		 7
	HEREDOC_DEL,		 8
	HEREDOC_CONTENT,	 9
	CMD,			 10 
	ARG,			11 
	FILE_NAME,		12 
	LINE_START,		13 
}	e_token;
*/

typedef enum token {
	WORD,
	PIPE,
	SINGLE,
	DOUBLE,
	SIMPLE_REDIRECT_TO,
	SIMPLE_REDIRECT_FROM,
	DOUBLE_REDIRECT_TO,
	HEREDOC,
	HEREDOC_DEL,
	HEREDOC_CONTENT,
	CMD,
	ARG,
	FILE_NAME,
	LINE_START,
}	t_token;

typedef struct s_list {
	char			*word;
	t_token			token;
	struct s_list	*next;	
}	t_list;

typedef struct s_shell {
	char	**envparams;
	char	*line;
	char	*line_tmp;
	t_list	*list;
	t_list	*pipeline;
	t_list	*pipeline_start;
	pid_t	*pid;
	int		nbr_pipe;
	t_cmd	cmd;
}	t_shell;

void	rl_replace_line(const char *text, int clear_undo);

// main.c
int		check_for_exp(t_shell *minishell);
int		check_chars(char *word);

//read_exec.c
void	read_exec_loop(t_shell *minishell, int not_done);

//redirect.c
int		ft_redirect(t_shell *minishell);

// exec_utils.c
int		is_builtin(t_shell *minishell);
int		is_builtin_internal(char *name);
int		count_pipe(t_shell *minishell);
int		is_redirect(t_token token);

// reset_line.c
void	reset_line(t_shell *minishell);
void	cmd_init(t_shell *minishell);

//pipeline.c
void	exec_pipeline(t_shell *minishell);
pid_t	exec_cmd(t_shell *minishell);
int		exec_builtin(t_shell *minishell);
int		exec_builtin_2(t_shell *minishell);

// check_syntax.c
int		check_syntax_error(t_shell *minishell);
int		line_not_done(t_shell *minishell);
void	move_pipeline(t_shell *minishell);

// tokenize_line.c
void	tokenize_line(t_shell *minishell);

// get_path.c
char	*get_path(t_shell *minishell);

// ft_build_cmd.c
void	ft_build_cmd(t_shell *minishell);
void	reset_cmd(t_shell *minishell);

// execute_cmd.c
void	execute_line(t_shell *minishell);

// error.c
int		ft_strlen(char *str);
int		error_msg(char *err, int ret);
void	free_env(t_shell *minishell);

// utils1.c
char	*env_dup(char *s1);
int		ft_strlen(char *str);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
char	*ft_substr(char *s, int start, int len);

//utils2.c
int		check_chars(char *word);
int		check_for_exp(t_shell *minishell);
void	trim_pipeline(t_shell *minishell);

//utils3.c
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

//utils5.c
int		append_str(char **str1, char *str2);
int		add_nl(char **str1);

// initializing.c
t_shell	init_shell(char **envp);
int		env_counter(char **envp);
int		init_envs(t_shell *minishell, char **envp);

// exit.c
void	ft_exit(t_shell *minishell, char *msg);
void	free_list(t_list *list);

// unset.c
int		ft_unset(t_shell *minishell, int i);

// export.c
int		ft_export(t_shell *minishell);

// env.c
int		ft_env(t_shell *minishell);

// echo.c
int		ft_echo(t_shell *minishell);

// pwd.c
int		ft_pwd(t_shell *minishell);

// cd.c
void	ft_cd(t_shell *minishell);

// debug_utils.c
void	print_envs(t_shell *minishell);
void	print_cmd(t_shell *minishell);
void	print_list(t_shell *minishell);
void	print_pipeline(t_shell *minishell);
void	test_expansions(t_shell *minishell);

// env_utils.c
int		find_env(char *env, t_shell *minishell);
int		env_compare(char *env, int len, char *envparam);
char	*build_env(char *env, char *value);
int		change_env(t_shell *minishell, int index, char *value, char *env);
int		set_env(char *env, char *value, t_shell *minishell);
void	copy_envp(t_shell *minishell, char **old_env, char *new_env);
int		add_env(char *env, char *value, t_shell *minishell);

// word_parse.c
void	word_parse(char *line, t_shell *minishell, int i, int x);
int		is_whitespace(char c);
char	*build_word(int i, int offset, char *line);
void	add_word(t_shell *minishell, char *word, int flag);
int		check_quote(int type, char *line, int i);
int		determine_flag(char c);
int		determine_operator(char *line, int i);
int		return_operator(int operator);

// expanding.c
char	*get_var(char *str, int i);
int		check_expansion(char *str, t_shell *minishell, t_list *node);
int		check_in_env(char *env_var, t_shell *minishell);
int		compare_env(char *env_var, char *mini_env);
void	expand_varv2(t_shell *minishell, \
		char *env_var, t_list *node, int macro);
char	*malloc_expand(t_list *node, char *env_var, \
		t_shell *minishell, int macro);
int		index_jump(char *env_var, char c, int index);
char	*env_var_based(char c, char *str, int i);
int		ft_unset_questionmark(t_shell *minishell);
int		is_one_of(char c);
void	set_signalenv(t_shell *minishell);

// word_parse2.c
void	word_subparse(char *line, t_shell *mini, t_token token, int off);
int		parse_list(t_shell *minishell);
int		part_subparse(t_token token, t_shell *minishell, char *line);
int		add_pipeline(t_shell *minishell, char *word, t_token token);

// signal.c
void	sig_handler(int signal);
#endif
