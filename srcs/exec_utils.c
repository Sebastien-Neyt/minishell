#include "../includes/minishell.h"

/* return 1 if name is a builtin 0 if not
 */
int	is_builtin(char *name)
{
	if (name == NULL)
		return (0);
	if (!ft_strcmp("cd", name)
		return (1);
	if (!ft_strcmp("echo", name)
		return (1);
	if (!ft_strcmp("pwd", name)
		return (1);
	if (!ft_strcmp("export", name)
		return (1);
	if (!ft_strcmp("unsset", name)
		return (1);
	if (!ft_strcmp("env", name)
		return (1);
	if (!ft_strcmp("exit", name)
		return (1);
	return (0);
}

/* return 1 if token is a redirect 0 if not
 */
int	is_redirect(e_token token)
{
	if (token == SIMPLE_REDIRECT_TO)
		return (1);
	if (token == SIMPLE_REDIRECT_FROM)
		return (1);
	if (token == DOUBNLE_REDIRECT_TO)
		return (1);
	if (token == HERE_DOC)
		return (1);
	return (0);
}

