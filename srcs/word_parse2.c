/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parse2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:16:34 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/16 14:18:03 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
char *build_subword(int i, int offset, char *word)
{
	char *word;

	word = malloc(sizeof(char) * (
}
*/


int	parse_list(t_shell *minishell)
{
	t_list *tmp;

	tmp = minishell->list;
	while (tmp)
	{
		//if tmp->word is empty we remove it?
	//	printf("TOKEN: %d WORD: %s\n", tmp->token, tmp->word);
		if (tmp->word)
		{
			tmp->word = ft_strtrim(tmp->word, " \t");
			word_subparse(tmp->word, minishell, tmp->token);
		}
		//printf("\n\n@@@END OF WORD@@@\n\n");
		tmp = tmp->next;
	}
	return (1);
}

int	determine_operator(char *line, int i)
{
	if (line[i] == '|')
		return (PIPE);
	else if (line[i] == 60 || line[i] == 62)
	{	// < OR > OUTPUT or INPUT
		if (line[i] == 60 && line[i + 1] == 60)
			return (RED_HEREDOC);
			// << HEREDOC
		if (line[i] == 62 && line[i + 1] == 62)
			return (RED_APPEND);
			// >> APPEND OUTPUT
		if (line[i] == 60)
			return (RED_INPUT);
		if (line[i] == 62)
			return (RED_OUTPUT);
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

void	add_pipeline(t_shell *minishell, char *word, e_token token)
{
	t_list *new_word;
	if (!minishell->pipeline->word)
	{
		minishell->pipeline->word = word;
		minishell->pipeline->token = token;
	}
	else
	{
		//new_word = ft_lstlast(minishell->pipeline);
		//minishell->pipeline->token = token;
	//	printf("%s NEW_WORD\n", word);
		ft_lstadd_back(&minishell->pipeline, ft_lstnew(word));
		new_word = ft_lstlast(minishell->pipeline);
		new_word->token = token;
	}
}

char *build_operator(int operator)
{
	char *ans;

	if (operator == PIPE)
		ans = ft_strdup("|");
	if (operator == RED_HEREDOC)
		ans = ft_strdup("<<");
	if (operator == RED_APPEND)
		ans = ft_strdup(">>");
	if (operator == RED_INPUT)
		ans = ft_strdup("<");
	if (operator == RED_OUTPUT)
		ans = ft_strdup(">");
	return (ans);
}


int word_subparse(char *line, t_shell *minishell, e_token token)
{
	int	i;
	int	offset;
	int operator;
	char *new_element;
	char *op_element;
	

	new_element = NULL;
	op_element = NULL;
	i = 0;
	offset = 0;
	//printf("LINE: %s\n", line);
	
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
		//printf("OPERATOR: %d || INDEX : %d || OFFSET : %d || OP_ELEMENT %s\n", operator, i, offset, op_element);	
		if (operator == 0)
		{
			i++;
			if (!line[i])
			{
				new_element = build_word(i + 1, offset, line);
				if (new_element)
				{
					add_pipeline(minishell, new_element, token);
					new_element = NULL;
				}
				if (op_element)
				{
					add_pipeline(minishell, op_element, DEFAULT);
					op_element = NULL;
				}
				//printf("ORIGINAL: %s\n", new_element);
			}
			continue;
		}
		else if (operator >= 10 && operator <= 12)
		{
			//printf("OPERATOR: %d || INDEX : %d || OFFSET : %d || OP_ELEMENT %s\n", operator, i, offset, op_element);	
			if (i - offset > 0)
				new_element = build_word(i, offset, line);
			if (new_element)
			{
				add_pipeline(minishell, new_element, token);
				new_element = NULL;
			}
			if (op_element)
			{
				add_pipeline(minishell, op_element, DEFAULT);
				op_element = NULL;
			}
			i++;
			offset++;
			offset = i;
			if (new_element)
			//	printf("NEW_ELEMENT: %s\n", new_element);
			continue;
		}	
		else if (operator > 100)
		{
			if (i - offset > 0)
				new_element = build_word(i, offset, line);
			if (new_element)
			{
				add_pipeline(minishell, new_element, token);
				new_element = NULL;
			}
			if (op_element)
			{
				add_pipeline(minishell, op_element, DEFAULT);
				op_element = NULL;
			}
			i += 2;
			offset = i;
			if (new_element)
				//printf("NEW_ELEMENT: %s\n", new_element);
			continue;
		}
	}
	return (0);
}
