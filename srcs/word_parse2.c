/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parse2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:16:34 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/12 16:24:08 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//we loop through our current linked list nodes.
//We trim each node->word from whitespaces and tabs
//and then we call our word_subparse function
int	parse_list(t_shell *minishell)
{
	t_list	*tmp;

	tmp = minishell->list;
	while (tmp)
	{
		if (tmp->word)
		{
			tmp->word = ft_strtrim(tmp->word, " \t");
			word_subparse(tmp->word, minishell, tmp->token);
		}
		tmp = tmp->next;
	}
	return (1);
}

// this one returns based on the operator we found. looks for pipes / redirects
int	determine_operator(char *line, int i)
{
	if (line[i] == '|')
		return (PIPE);
	else if (line[i] == 60 || line[i] == 62)
	{
		if (line[i] == 60 && line[i + 1] == 60)
			return (HEREDOC);
		if (line[i] == 62 && line[i + 1] == 62)
			return (DOUBLE_REDIRECT_TO);
		if (line[i] == 60)
			return (SIMPLE_REDIRECT_FROM);
		if (line[i] == 62)
			return (SIMPLE_REDIRECT_TO);
	}
	return (0);
}

/*
char *build_new_word(int i, int offset, char *line)
{
	char *word;
	int	y;
	int x;

	x = offset;
	y = 0;
	word = malloc(sizeof(char) * (i - offset + 1));
	//if (!word)
	//	error
	while (y < i - offset)
	{
		word[y]
	}
}
*/

//adds them to the pipeline.
void	add_pipeline(t_shell *minishell, char *word, e_token token)
{
	t_list	*new_word;

	if (!minishell->pipeline->word)
	{
		minishell->pipeline->word = word;
		minishell->pipeline->token = token;
	}
	else
	{
		ft_lstadd_back(&minishell->pipeline, ft_lstnew(word));
		new_word = ft_lstlast(minishell->pipeline);
		new_word->token = token;
	}
}

//builds operator buildingblocks
char	*build_operator(int operator)
{
	char	*ans;

	if (operator == PIPE)
		ans = ft_strdup("|");
	if (operator == HEREDOC)
		ans = ft_strdup("<<");
	if (operator == DOUBLE_REDIRECT_TO)
		ans = ft_strdup(">>");
	if (operator == SIMPLE_REDIRECT_FROM)
		ans = ft_strdup("<");
	if (operator == SIMPLE_REDIRECT_TO)
		ans = ft_strdup(">");
	return (ans);
}

static void add_element(t_shell *minishell, char *new_element, char *op_element, e_token token)
{
	if (new_element)
	{
		add_pipeline(minishell, new_element, token);
		new_element = NULL;
	}
	if (op_element)
	{
		add_pipeline(minishell, op_element, WORD);
		op_element = NULL;
	}
}

//here we parse each node->word again but now we do it for all operators. based on the index and offset we build newe words again and add them to our NEW pipeline.
int	word_subparse(char *line, t_shell *minishell, e_token token)
{
	int		i;
	int		offset;
	int		operator;
	char	*new_element;
	char	*op_element;

	new_element = NULL;
	op_element = NULL;
	i = 0;
	offset = 0;
	while (line[i])
	{
		if (token == DOUBLE)
		{
			add_pipeline(minishell, line, token);
			break ;
		}
		operator = determine_operator(line, i);
		if (operator)
			op_element = build_operator(operator);
		if (operator == 0)
		{
			i++;
			if (!line[i])
			{
				new_element = build_word(i + 1, offset, line);
				add_element(minishell, new_element, op_element, token);
			}
			continue ;
		}
		else if (operator == PIPE || operator == SIMPLE_REDIRECT_TO || operator == SIMPLE_REDIRECT_FROM)
		{
			if (i - offset > 0)
				new_element = build_word(i, offset, line);
			add_element(minishell, new_element, op_element, token);
			i++;
			offset++;
			offset = i;
		}	
		else if (operator == DOUBLE_REDIRECT_TO || operator == HEREDOC)
		{
			if (i - offset > 0)
				new_element = build_word(i, offset, line);
			add_element(minishell, new_element, op_element, token);
			i += 2;
			offset = i;
			continue ;
		}
	}
	return (0);
}
