/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parse2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:16:34 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 17:36:54 by sneyt            ###   ########.fr       */
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
		ft_lstadd_back(&minishell->pipeline, ft_lstnew(word));
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

int	word_subparse(char *line, t_shell *minishell, t_token token)
{
	int		i;
	int		offset;
	int		operator;
	char	*new_element;
	char	*op_element;

	new_element = NULL;
	op_element = NULL;l
	i = 0;
	offset = 0;
	if (token == DOUBLE)
		return (add_pipeline(minishell, line, token));
	while (line[i])
	{
		operator = determine_operator(line, i);
		if (operator)
			op_element = build_operator(operator);
		if (!operator)
		{
			i++;
			if (!line[i])
				add_element(minishell, build_word(i + 1, offset, line), op_element, token);
			continue ;
		}
		if (i - offset > 0)
				new_element = build_word(i, offset, line);
		add_element(minishell, new_element, op_element, token);
		if (return_operator(operator) == 1)
		{
			i++;
			offset++;
		}	
		else if (return_operator(operator) == 2)
			i += 2;
		offset = i;
	}
	return (0);
}

/*
int word_subparse(char *line, t_shell *minishell, e_token token)
{
    int i = 0;
    int offset = 0;
    int operator = 0;
    char *new_element = NULL;
    char *op_element = NULL;

    if (token == DOUBLE)
        return add_pipeline(minishell, line, token);

    while (line[i])
    {
        operator = determine_operator(line, i);
        if (operator)
            op_element = build_operator(operator);
        if (!operator)
        {
            i++;
            if (!line[i])
            {
                new_element = build_word(i + 1, offset, line);
                add_element(minishell, new_element, op_element, token);
            }
            continue;
        }
        if (i - offset > 0)
            new_element = build_word(i, offset, line);
        add_element(minishell, new_element, op_element, token);
        if (return_operator(operator) == 1)
        {
            i++;
            offset++;
        }
        else if (return_operator(operator) == 2)
            i += 2;
        offset = i;
    }
    return 0;
}
*/

/*
int word_subparse(char *line, t_shell *minishell, e_token token)
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
            break;
        }
        operator = determine_operator(line, i);
        op_element = build_operator(operator);
        if (operator == 0)
        {
            i++;
            if (!line[i])
            {
                new_element = build_word(i + 1, offset, line);
                add_element(minishell, new_element, op_element, token);
            }
            continue;
        }
        if (i - offset > 0)
            new_element = build_word(i, offset, line);
        add_element(minishell, new_element, op_element, token);
        if (operator == PIPE || operator == SIMPLE_REDIRECT_TO \
		|| operator == SIMPLE_REDIRECT_FROM)
        {
            i++;
            offset++;
            offset = i;
        }
        else
        {
            i += 2;
            offset = i;
        }
    }
    return (0);
}
*/
