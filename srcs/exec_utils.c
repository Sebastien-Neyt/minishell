#include "../includes/minishell.h"

/* return 1 if name is a builtin 0 if not
 */

int	is_builtin_internal(char *name)
{
 	if (name == NULL)
 		return (1);
	if (!ft_strcmp("cd", name))
		return (1);
	if (!ft_strcmp("echo", name))
		return (1);
	if (!ft_strcmp("pwd", name))
		return (1);
	if (!ft_strcmp("export", name))
		return (1);
	if (!ft_strcmp("unset", name))
		return (1);
	if (!ft_strcmp("env", name))
		return (1);
	if (!ft_strcmp("exit", name))
		return (1);
	return (0);
}

int	is_builtin(t_shell *minishell)
{
	t_list *pipeline;
 	char *name;

 	pipeline = minishell->pipeline;
	name = NULL;
 	while (pipeline && pipeline->token != PIPE)
 	{
 		if (pipeline->token == CMD)
 			name = pipeline->word;
 		pipeline = pipeline->next;
 	}
	return (is_builtin_internal(name));
}

int	count_pipe(t_shell *minishell)
{
	int i;
	t_list *pipeline;

	pipeline = minishell->pipeline;
	i = 0;
	while(pipeline)
	{
		if (pipeline->token == PIPE)
			i++;
		pipeline = pipeline->next;
	}
	return (i);
}

/* return 1 if token is a redirect 0 if not
 */
int	is_redirect(e_token token)
{
	if (token == SIMPLE_REDIRECT_TO)
		return (1);
	if (token == SIMPLE_REDIRECT_FROM)
		return (1);
	if (token == DOUBLE_REDIRECT_TO)
		return (1);
	if (token == HEREDOC)
		return (1);
	return (0);
}

