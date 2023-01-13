/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:14:49 by sneyt             #+#    #+#             */
/*   Updated: 2023/01/13 11:18:01 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//we look for ~ and $. We get the index of the env_var. we then call 
//expand_varv2 that will decide what to do based on the index.
int	check_expansion(t_shell *minishell, t_list *node, int i, char *env_var)
{
	if (!node->word)
		return (0);
	while (node->word[i])
	{
		env_var = env_var_based(node->word[i], node->word, i);
		if (node->word[i] == '~')
			if (node->word[i + 1] == '/' || node->word[i + 1] == '\0')
				expand_varv2(minishell, env_var, node, TILDE);
		if (node->word[i] == '$' && node->word[i + 1] != 0)
		{
			if (node->word[i + 1] && node->word[i + 1] == '?'
				&& is_one_of(node->word[i + 2]))
				set_signalenv(minishell);
			expand_varv2(minishell, env_var, node, DOLLAR);
			i += ft_strlen(env_var) + 1;
			ft_unset_questionmark(minishell);
		}
		if (env_var)
			free(env_var);
		if (node->word[i] == '~' || node->word[i] == '$')
			break ;
		i++;
	}
	return (0);
}

//helper function that mallocs the required size for the expantion.
char	*malloc_expand(t_list *node, char *env, t_shell *minishell, int macro)
{
	int		index;
	char	*expanded_word;

	expanded_word = NULL;
	index = check_in_env(env, minishell);
	if (index >= 0 && macro == DOLLAR)
		expanded_word = malloc(sizeof(char) * ((ft_strlen(node->word) \
		- ft_strlen(env) - 1) + (ft_strlen(minishell->envparams[index]) \
		- ft_strlen(env) - 1) + 1));
	else if (index >= 0 && macro == TILDE)
		expanded_word = malloc(sizeof(char) * ((ft_strlen(node->word)) \
		+ (ft_strlen(minishell->envparams[index]) - ft_strlen(env) - 1)));
	else if (index < 0 && macro == TILDE)
		expanded_word = malloc(sizeof(char) * ((ft_strlen(node->word) - 1)));
	else if (index < 0)
		expanded_word = malloc(sizeof(char) * ((ft_strlen(node->word) \
		- ft_strlen(env))));
	if (!expanded_word)
		ft_exit(minishell, FAILED_MALLOC);
	return (expanded_word);
}

int	index_jump(char *env_var, char c, int index)
{
	int	ans;

	ans = 0;
	if (index >= 0)
	{
		if (c == '$')
			ans = ft_strlen(env_var) + 1;
		else
			ans = 1;
	}
	else
	{
		if (c == '$')
			ans = ft_strlen(env_var) + 1;
		else if (c == '~')
			ans = 1;
		else
			ans = 0;
	}
	return (ans);
}

static void	part_expandv2(char *expanded_word, int x, int i, t_list *node)
{
	while (node->word[i] != '\0')
		expanded_word[x++] = node->word[i++];
	expanded_word[x] = '\0';
	free(node->word);
	node->word = NULL;
	node->word = expanded_word;
}

//this one will malloc the right amount of space for the expansion. 
//depending on the fact that the variable is indeed expandable and in 
//our minishell envparams. 
//if will then copy everyhting of our current node_word up till the expansion. 
//and then either expand the variable or just skip. After that 
//it will just copy the rest.
void	expand_varv2(t_shell *minishell, char *env_var, t_list *node, int macro)
{
	int		i;
	int		x;
	int		y;
	int		index;
	char	*expanded_word;

	index = check_in_env(env_var, minishell);
	expanded_word = malloc_expand(node, env_var, minishell, macro);
	i = 0;
	x = 0;
	while (node->word[i] != '\0')
	{
		if (node->word[i] == '$' || node->word[i] == '~')
		{
			if (index >= 0)
			{
				y = ft_strlen(env_var) + 1;
				while (minishell->envparams[index][y] != '\0')
					expanded_word[x++] = minishell->envparams[index][y++];
			}
			i += index_jump(env_var, node->word[i], index);
			return (part_expandv2(expanded_word, x, i, node));
		}
		expanded_word[x++] = node->word[i++];
	}
}
