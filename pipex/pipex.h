#ifndef PIPEX_H
# define PIPEX_H

# define BLACK   "\033[0;30m"
# define RED     "\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE    "\033[0;34m"
# define PURPLE  "\033[0;35m"
# define CYAN    "\033[0;36m"
# define WHITE 	"\033[0;37m"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> //to be removed
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_cmd
{
	char	*path;
	char	**args;
	char	**env;
}	t_cmd;

int		test_command(char *argv_ptr, char *envp);
void	proc1(char **argv, int fd[2], char **envp);
void	proc2(char **argv, int fd[2], char **envp);
void	terminate(int fd[2], int fildes);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strndup(const char *src, size_t n);
char	*get_path(char *argv, char *envp);
char	*get_env(char **envp);

#endif
