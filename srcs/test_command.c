#include "minishell.h"

int	test_path(char *prefix, char *cmd)
{
	char	*path;
	int		ret;

	ret = -1;
	path = ft_strjoin(prefix, cmd);
	if (path == NULL)
		return (ret);
	if (access(path, X_OK) == 0)
		ret = 0;
	free(path);
	return (ret);
}

int	is_in_path(char *envp, char *cmd)
{
	char	**prefix;
	char	**save_p;
	int		ret;

	ret = -1;
	prefix = ft_split(envp, ':');
	save_p = prefix;
	if (prefix == NULL)
		return (ret);
	while (*prefix)
	{
		if (ret != 1 && test_path(*prefix, cmd) == 0)
			ret = 1;
		free(*prefix);
		prefix++;
	}
	free(save_p);
	return (ret);
}

// arguments :	argv	= name of the command
// 		envp	= PATH env variable
// return :	-1 	= no executable binary found when using path
// 		0	= found an executable binary
int	test_command(char *argv, char *envp)
{
	int		ret;
	char	*cmd;
	char	*tmp;

	ret = -1;
	cmd = ft_strdup(argv);
	if (cmd == NULL)
		return (ret);
	if (access(cmd, X_OK) == 0)
	{
		free(cmd);
		return (0);
	}
	tmp = cmd;
	cmd = ft_strjoin("/", cmd);
	free(tmp);
	if (cmd == NULL)
	{
		free(cmd);
		return (ret);
	}
	if (is_in_path(envp + 5, cmd) == 1)
		ret = 0;
	free(cmd);
	return (ret);
}

//TODO ? check for cases when executable is in current directory
