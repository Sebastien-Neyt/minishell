#include "pipex.h"

int	child1(char **argv, int fd[2], char **envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (access(argv[1], R_OK) != 0)
		{
			perror(RED"file not found");
			exit(1);
		}
		if (test_command(argv[2], get_env(envp)) != 0)
		{
			perror(RED"command not found");
			exit(1);
		}
		proc1(argv, fd, envp);
	}
	return (pid);
}

int	child2(char **argv, int fd[2], char **envp)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		proc2(argv, fd, envp);
	return (pid);
}

void	terminate(int fd[2], int fildes)
{
	close(fildes);
	close(fd[0]);
	close(fd[1]);
	perror(RED"error");
	exit(1);
}

char	*get_env(char **envp)
{
	while (*envp)
	{
		if ((*(*envp + 0) == 'P') && (*(*envp + 1) == 'A') \
		&& (*(*envp + 2) == 'T') && (*(*envp + 3) == 'H') \
		&& (*(*envp + 4) == '='))
			return (*envp);
		envp++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	status;

	if (argc != 5)
	{
		perror(RED"[wrong number of arguments]");
		return (1);
	}
	if (pipe(fd) == -1)
	{
		perror(RED"[pipe error]");
		return (1);
	}
	pid1 = child1(argv, fd, envp);
	pid2 = child2 (argv, fd, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (status);
}
