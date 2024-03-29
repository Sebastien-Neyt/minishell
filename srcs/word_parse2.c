/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parse2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:16:34 by sneyt             #+#    #+#             */
/*   Updated: 2023/01/05 09:10:24 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//we loop through our current linked list nodes.
//We trim each node->word from whitespaces and tabs
//and then we call our word_subparse function
int	parse_list(t_shell *minishell)
{
	t_list	*tmp;
	char	*new;

	tmp = minishell->list;
	while (tmp)
	{
		if (tmp->word)
		{
			new = ft_strtrim(tmp->word, " \t");
			if (!new)
				ft_exit(minishell, FAILED_MALLOC);
			free(tmp->word);
			tmp->word = new;
			word_subparse(tmp->word, minishell, tmp->token, 0);
		}
		tmp = tmp->next;
	}
	return (1);
}

//adds them to the pipeline.
int	add_pipeline(t_shell *minishell, char *word, t_token token)
{
	t_list	*new_word;

	if (!minishell->pipeline->word)
	{
		minishell->pipeline->word = word;
		minishell->pipeline->token = token;
	}
	else
	{
		ft_lstadd_back(&minishell->pipeline, ft_lstnew(word, minishell));
		new_word = ft_lstlast(minishell->pipeline);
		new_word->token = token;
	}
	return (0);
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

static void	add_element(t_shell *mini, char *ne, char *oe, t_token t)
{
	if (ne)
	{
		add_pipeline(mini, ne, t);
		ne = NULL;
	}
	if (oe)
	{
		add_pipeline(mini, oe, WORD);
		oe = NULL;
	}
}

//here we parse each node->word again but now we do it for all operators.i
//based on the index and offset we build newe 
//words again and add them to our NEW pipeline.

void	word_subparse(char *line, t_shell *mini, t_token token, int offset)
{
	int		i;
	int		operator;
	char	*new_element;
	char	*op;

	new_element = NULL;
	i = 0;
	while (line[i] && part_subparse(token, mini, line))
	{
		operator = determine_operator(line, i);
		op = NULL;
		if (operator != 0)
		{
			op = build_operator(operator);
			if (i - offset > 0)
				new_element = build_word(i, offset, line);
			add_element(mini, new_element, op, token);
			i += return_operator(operator);
			offset = i;
		}
		else
			if (!line[++i])
				add_element(mini, build_word(i + 1, offset, line), op, token);
	}
}
