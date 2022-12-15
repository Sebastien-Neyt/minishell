#include "../includes/minishell.h"

int	heredoc_redirect(t_shell *minishell, t_list *pipeline)
{
	int	pid;
	int	status;
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit(minishell, FAILED_PIPE);
	pid = fork();
	if (pid == 0)
	{
		status = write(\
fd[1], pipeline->next->word, ft_strlen(pipeline->next->word));
		exit(status);
	}
	waitpid(pid, &status, 0);
	close(fd[1]);
	if (status == -1)
		ft_exit(minishell, "failed heredoc\n");
	return (fd[0]);
}

void	red_to(t_list *pipeline, int *fd_out)
{
	if (pipeline->token == SIMPLE_REDIRECT_TO)
	{
		if (*fd_out)
			close(*fd_out);
		*fd_out = open(\
pipeline->next->word, (O_WRONLY | O_CREAT | O_TRUNC), 0666);
	}
	if (pipeline->token == DOUBLE_REDIRECT_TO)
	{
		if (*fd_out)
			close(*fd_out);
		*fd_out = open(\
pipeline->next->word, (O_WRONLY | O_CREAT | O_APPEND), 0666);
	}
}

void	red_from(t_list *pipeline, int *fd_in, t_shell *minishell)
{
	if (pipeline->token == SIMPLE_REDIRECT_FROM)
	{
		if (*fd_in)
			close(*fd_in);
		*fd_in = open(pipeline->next->word, (O_RDONLY));
	}
	if (pipeline->token == HEREDOC)
	{
		if (*fd_in)
			close(*fd_in);
		*fd_in = heredoc_redirect(minishell, pipeline);
	}
}

// should heredoc be written to stdin
// should throw error if token after redirection is ARG
// need to be splitted 
// segfault protection on next ?
// should have have perror inside already
int	ft_redirect(t_shell *minishell)
{
	t_list	*pipeline;
	int		fd_in;
	int		fd_out;

	fd_in = 0;
	fd_out = 0;
	pipeline = minishell->pipeline;
	while (pipeline && pipeline->next && pipeline->token != PIPE)
	{
		red_to(pipeline, &fd_out);
		red_from(pipeline, &fd_in, minishell);
		if (fd_in == -1 || fd_out == -1)
			return (0);
		pipeline = pipeline->next;
	}
	if (fd_in)
		minishell->cmd.fd_in = fd_in;
	if (fd_out)
		minishell->cmd.fd_out = fd_out;
	dup2(minishell->cmd.fd_in, STDIN_FILENO);
	dup2(minishell->cmd.fd_out, STDOUT_FILENO);
	return (1);
}
