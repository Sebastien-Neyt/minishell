/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:14:49 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/25 11:11:50 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// this one will return the name of the VAR in our codeline without the $.
// So $PWD -> PWD
// $SEEIFTHISONEWORKS -> SEEIFTHISONEWORKS
char *get_var(char *str, int i)
{
	char *var;
	int	x;
	int y;
	int	len;

	y = 0;
	x = i + 1;
	while (!is_whitespace(str[x]) && str[x] != '\0' && str[x] != '$' && str[x] != 34 && str[x] != 39)
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
// we loop through the envparams of our minishell to see if there is match with env_var we substracted from the line. if we find a match we return the index of the match.
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
//we look for ~ and $. We get the index of the env_var. we then call expand_varv2 that will decide what to do based on the index.
int	check_expansion(char *str, t_shell *minishell, t_list *node)
{
	int	i;
	int	index;
	char *env_var;

	env_var = NULL;
	i = 0;
	if (!node->word)
		return (0);
	while (str[i])
	{
		if (str[i] == '~')
		{
			env_var = env_dup("HOME");
			index = check_in_env(env_var, minishell);
			//printf("%s == %d\n", env_var, index);
			expand_varv2(index, minishell, env_var, node, TILDE);
			break ;
		}
		if (str[i] == '$') //check if next one is a $ aswell?
		{
			env_var = get_var(str, i);
			i += ft_strlen(env_var) - 1;
			index = check_in_env(env_var, minishell);
			expand_varv2(index, minishell, env_var, node, DOLLAR);
			break ;
		}
			//return 1 if there is a match, return len of the $VAR and increment i;
		i++;
	}
	if (env_var)
		free(env_var);
	return (0);
}

//this one will malloc the right amount of space for the expansion. depending on the fact that the variable is indeed expandable and in our minishell envparams. 
//if will then copy everyhting of our current node_word up till the expansion. and then either expand the variable or just skip. After that it will just copy the rest.
int	expand_varv2(int index, t_shell *minishell, char *env_var, t_list *node, int macro)
{
	int	i;
	int x;
	int y;
	//char *copy;
	char *expanded_word;
	//copy = env_dup(node->word);
	//if (node->word == NULL)
	//	return (0);
	if (index >= 0 && macro == DOLLAR)
	{
		expanded_word = malloc(sizeof(char) * ((ft_strlen(node->word) - ft_strlen(env_var) - 1) + (ft_strlen(minishell->envparams[index]) - ft_strlen(env_var))));
		//printf("len node-word : %d || len env_var : %d || len envparam : %d \n", ft_strlen(node->word), ft_strlen(env_var), ft_strlen(minishell->envparams[index]));
	}
	else if (index >= 0 && macro == TILDE)
	{
		expanded_word = malloc(sizeof(char) * ((ft_strlen(node->word) - 1 - 1) + (ft_strlen(minishell->envparams[index]) - ft_strlen(env_var))));
	}
	if (index < 0)
	{
		expanded_word = malloc(sizeof(char) * ((ft_strlen(node->word) - ft_strlen(env_var))));
		//printf("len node-word : %d || len env_var : %d \n", ft_strlen(node->word), ft_strlen(env_var));
	}
	//if (!expanded_word)
		//Malloc error
	//printf("INDEX: %d || env_var : %s || node_word: %s\n", index, env_var, node->word);
	i = 0;
	x = 0;
	while (node->word[i] != '\0')
	{
		//printf("%c\n", node->word[i]);
		if ((node->word[i] == '$' || node->word[i] == '~') && index >= 0)
		{
			y = ft_strlen(env_var) + 1;
			//printf("value of y : %d\n", y);
			while (minishell->envparams[index][y] != '\0')
			{
			//	printf("%c\n", minishell->envparams[index][y]);
				expanded_word[x] = minishell->envparams[index][y];
				x++;
				y++;
			}
			if (node->word[i] == '$')
				i += ft_strlen(env_var) + 1;
			else if (node->word[i] == '~')
				i += 1;
			while (node->word[i] != '\0')
			{
				expanded_word[x] = node->word[i];
				i++;
				x++;
			}
			expanded_word[x] = '\0';
			free(node->word);
			//printf("EXPANDED WORD: %s\n", expanded_word);
			node->word = expanded_word;
			//printf("TEST: %s\n", node->word);
			return (1);
		}
		else if (node->word[i] == '$' && index < 0 && i == 0)
		{
			//printf("expanded word is NULL\n");
			expanded_word = NULL;
			free(node->word);
			node->word = expanded_word;
			return (0);
		}
		else if (node->word[i] == '$' && index < 0)
		{
			i += (ft_strlen(env_var) + 1);
			while (node->word[i] != '\0')
			{
				expanded_word[x] = node->word[i];
				x++;
				i++;
			}
			expanded_word[x] = '\0';
			free(node->word);
			node->word = expanded_word;
			return (1);
		}
		expanded_word[x] = node->word[i];
		x++;
		i++;
	}
	return (0);
}
