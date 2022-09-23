#include "pipex.h"

int	make_path(char *prefix, char **ret)
{
	char	*test;

	test = ft_strjoin(prefix, *ret);
	if (test == NULL)
		return (-1);
	if (access(test, X_OK) == 0)
	{
		free(*ret);
		*ret = test;
		return (0);
	}
	free(test);
	return (-1);
}

void	free_tab(char **prefix)
{
	while (*prefix)
	{
		free(*prefix);
		prefix++;
	}
}

char	*return_path(char *cmd, char *envp)
{
	char	**prefix;
	char	**prefix_save;

	prefix = ft_split(envp, ':');
	prefix_save = prefix;
	if (prefix == NULL)
	{
		free(cmd);
		return (NULL);
	}
	while (*prefix)
	{
		if (make_path(*prefix, &cmd) == 0)
			break ;
		free(*prefix);
		prefix++;
	}
	free_tab(prefix);
	free(prefix_save);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	free(cmd);
	return (NULL);
}

char	*make_cmd(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != ' ')
		i++;
	return (ft_strndup(argv, i));
}

char	*get_path(char *argv, char *envp)
{
	char	*cmd;
	char	*tmp;

	cmd = make_cmd(argv);
	if (cmd == NULL)
		return (cmd);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	tmp = cmd;
	cmd = ft_strjoin("/", cmd);
	free(tmp);
	if (cmd == NULL)
		return (cmd);
	return (return_path(cmd, envp + 5));
}

/*
   int make_path(char *prefix, char **ret)
   {
   char *test;

   test = ft_strjoin(prefix, *ret);
   if (test == NULL)
   return (-1);
   if (access(test, X_OK) == 0)
   {
   free(*ret);
 *ret = test;
 return (0);        
 }
 free(test);
 return (-1);
 }

 char    *get_path(char *argv)
 {
 int i;
 char    *ret;

 i = 0;
 while (argv[i] && argv[i] != ' ')
 i++;
 ret = ft_strndup(argv, i);
 if (ret == NULL)
 return (ret);
 ret[i] = 0;
 if (access(ret, X_OK) == 0)
 return (ret);
 if (make_path("/bin/", &ret) == 0)
 return (ret);
 if (make_path("/sbin/", &ret) == 0)
 return (ret);
 if (make_path("/usr/bin/", &ret) == 0)
 return (ret);
 if (make_path("/usr/sbin/", &ret) == 0)
 return (ret);
 if (make_path("/usr/local/bin", &ret) == 0)
 return (ret);
 return (ret);
 }
 */
