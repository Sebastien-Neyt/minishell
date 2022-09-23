#include "pipex.h"

// redirect io streams
// close fd's
// call exec

void	proc1(char **argv, int fd[2], char **envp)
{
	int	fildes;
	int	control;

	fildes = open(argv[1], O_RDONLY);
	if (fildes == -1)
	{
		perror(RED"could not open the file");
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
	control = dup2(fd[1], STDOUT_FILENO);
	if (control == -1)
		terminate(fd, fildes);
	control = dup2(fildes, STDIN_FILENO);
	if (control == -1)
		terminate(fd, fildes);
	close(fildes);
	close(fd[0]);
	close(fd[1]);
	execve(get_path(argv[2], get_env(envp)), ft_split(argv[2], ' '), envp);
	perror(RED "error");
	exit(EXIT_FAILURE);
}
