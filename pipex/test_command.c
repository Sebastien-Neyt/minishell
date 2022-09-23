#include "pipex.h"
/*
   int test_path(char *prefix, char *argv)
   {
   char *path;
   int ret;

   ret = -1;
   path = ft_strjoin(prefix, argv);
   if (path == NULL)
   return (ret);
   if (access(path, X_OK) == 0)
   ret = 0;
   free(path);
   return (ret);
   }

   int test_command(char *argv_ptr)
   {
   int i;
   int ret;
   char    *argv;

   i = 0;
   ret = -1;
   argv = ft_strndup(argv_ptr, ft_strlen(argv_ptr));
   if (argv == NULL)
   return (ret);
   while (argv[i] && argv[i] != ' ')
   i++;
   argv[i] = 0;
   if (access(argv, X_OK) == 0)
   ret = 0;  
   if (test_path("/bin/", argv) == 0)
   ret = 0;    
   if (test_path("/sbin/", argv) == 0)
   ret = 0;    
   if (test_path("/usr/bin/", argv) == 0)
   ret = 0;    
   if (test_path("/usr/sbin/", argv) == 0)
   ret = 0;    
   if (test_path("/usr/local/bin", argv) == 0)
   ret = 0;
   free(argv);
   return (ret);
   }
   */

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
		if (test_path(*prefix, cmd) == 0)
			ret = 1;
		free(*prefix);
		prefix++;
	}
	free(save_p);
	return (ret);
}

static char	*make_cmd(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != ' ')
		i++;
	return (ft_strndup(argv, i));
}

int	test_command(char *argv, char *envp)
{
	int		ret;
	char	*cmd;
	char	*tmp;

	ret = -1;
	cmd = make_cmd(argv);
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

//TODO  add error messages
