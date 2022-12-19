/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parse3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:30:24 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 09:56:51 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//we check for whitespaces
int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

// this one returns based on the operator
// we found. looks for pipes / redirects
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

int	return_operator(int operator)
{
	if (operator == PIPE || operator == SIMPLE_REDIRECT_TO \
		|| operator == SIMPLE_REDIRECT_FROM)
		return (1);
	else if (operator == DOUBLE_REDIRECT_TO || operator == HEREDOC)
		return (2);
	return (0);
}
