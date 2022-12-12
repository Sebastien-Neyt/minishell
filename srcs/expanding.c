/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:14:49 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/12 15:32:16 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// this one will return the name of the VAR in our codeline without the $.
// So $PWD -> PWD
// $SEEIFTHISONEWORKS -> SEEIFTHISONEWORKS
char	*get_var(char *str, int i)
{
	char	*var;
	int		x;
	int		y;
	int		len;

	y = 0;
	x = i + 1;
	while (!is_whitespace(str[x]) && str[x] != '\0'
		&& str[x] != '$' && str[x] != 34 && str[x] != 39)
		x++;
	var = malloc(sizeof(char) * (x - i + 1));
	if (!var)
		return (NULL);
	i++;
	len = x - i;
	while (y < len)
		var[y++] = str[i++];
	var[y] = '\0';
	return (var);
}

//We look if env_var ( Ex: PWD ) is equal to the mini_env we give it.
int	compare_env(char *env_var, char *mini_env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(env_var);
	while (i < len)
	{
		if (env_var[i] != mini_env[i])
			return (0);
		i++;
	}
	return (1);
}

// we loop through the envparams of our minishell to see if there is match 
// with env_var we substracted from the line. if we find a match 
// we return the index of the match.
// else we return -1 to say there is no match and the env_var does not exist.
int	check_in_env(char *env_var, t_shell *minishell)
{
	int	i;

	i = 0;
	while (minishell->envparams[i])
	{
		if (compare_env(env_var, minishell->envparams[i]))
			return (i);
		i++;
	}
	return (-1);
}

//helper function to shorten inital one. this one returns
//env based on the tilde or dollar sign
char	*env_var_based(char c, char *str, int i)
{
	char	*ans;

	ans = NULL;
	if (c == '~')
		ans = env_dup("HOME");
	if (c == '$')
		ans = get_var(str, i);
	return (ans);
}

//we look for ~ and $. We get the index of the env_var. we then call 
//expand_varv2 that will decide what to do based on the index.
int	check_expansion(char *str, t_shell *minishell, t_list *node)
{
	int		i;
	char	*env_var;

	i = 0;
	if (!node->word)
		return (0);
	while (str[i])
	{
		env_var = env_var_based(str[i], str, i);
		if (str[i] == '~')
		{
			expand_varv2(minishell, env_var, node, TILDE);
			break ;
		}
		if (str[i] == '$')
		{
			i += ft_strlen(env_var) - 1;
			expand_varv2(minishell, env_var, node, DOLLAR);
			break ;
		}
		i++;
	}
	if (env_var)
		free(env_var);
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
		- ft_strlen(env))));
	else if (index >= 0 && macro == TILDE)
		expanded_word = malloc(sizeof(char) * ((ft_strlen(node->word) - 2) \
		+ (ft_strlen(minishell->envparams[index]) - ft_strlen(env))));
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
		//	part_expandv2(expanded_word, x, i, node);
			return (part_expandv2(expanded_word, x, i, node));
		}
		expanded_word[x++] = node->word[i++];
	}
}
