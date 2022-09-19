#include "pipex.h"

// redirect io streams
// open or create file if doesn't exist
// close fd's
// call exec
void	terminate2(int fd[2])
{
	perror(RED"could not open the file");
	close(fd[0]);
	close(fd[1]);
	exit(1);
}

void	proc2(char **argv, int fd[2], char **envp)
{
	int	control;
	int	fildes;

	fildes = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fildes == -1)
		terminate2(fd);
	if (test_command(argv[3], get_env(envp)) != 0)
	{
		write(2, RED"command not found ", ft_strlen(RED"command not found "));
		terminate(fd, fildes);
	}
	control = dup2(fd[0], STDIN_FILENO);
	if (control == -1)
		terminate(fd, fildes);
	control = dup2(fildes, STDOUT_FILENO);
	if (control == -1)
		terminate(fd, fildes);
	close(fildes);
	close(fd[0]);
	close(fd[1]);
	execve(get_path(argv[3], get_env(envp)), ft_split(argv[3], ' '), envp);
	perror(RED"error");
	exit(EXIT_FAILURE);
}
