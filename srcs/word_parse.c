/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:07:39 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/12 17:06:24 by sneyt            ###   ########.fr       */
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

// this one build the word based on the index and our offset.
// it will copy from offset till index.
char	*build_word(int i, int offset, char *line)
{
	char	*word;
	int		x;
	int		y;

	y = 0;
	x = offset;
	word = malloc(sizeof(char) * (i - offset + 1));
	while (y < i - offset)
	{
		word[y] = line[x];
		x++;
		y++;
	}
	word[y] = '\0';
	return (word);
}

void	add_word(t_shell *minishell, char *word, int flag)
{
	t_list	*new_word;

	if (!minishell->list->word)
	{
		minishell->list->word = word;
		if (flag == 1)
			minishell->list->token = SINGLE;
		else if (flag == 2)
			minishell->list->token = DOUBLE;
		else if (flag == 0)
			minishell->list->token = WORD;
	}
	else
	{
		ft_lstadd_back(&minishell->list, ft_lstnew(word));
		new_word = ft_lstlast(minishell->list);
		if (flag == 1)
			new_word->token = SINGLE;
		else if (flag == 2)
			new_word->token = DOUBLE;
		else if (flag == 0)
			new_word->token = WORD;
	}
}

//this one checks if the quote is in fact closed.
//either single or double quote.
int	check_quote(int type, char *line, int i)
{
	i++;
	if (type == 1)
	{
		while (line[i] != 39 && line[i] != '\0')
			i++;
	}
	if (type == 2)
	{
		while (line[i] != 34 && line[i] != '\0')
			i++;
	}
	return (i + 1);
}

int	determine_flag(char c)
{
	int	flag;

	flag = 0;
	if (c == 39)
		flag = 1;
	if (c == 34)
		flag = 2;
	return (flag);
}

//loop through line and split words based on whitespaces and quotes.
//will create a linked list and add the words to it
void	word_parse(char *line, t_shell *minishell, int i, int x)
{
	int	flag;

	while (line[i])
	{
		flag = 0;
		if (is_whitespace(line[i]))
		{
			while (is_whitespace(line[i]))
				i++;
			add_word(minishell, build_word(i - 1, x, line), flag);
			x = i;
		}
		flag = determine_flag(line[i]);
		if (flag)
		{
			i = check_quote(flag, line, i);
			add_word(minishell, build_word(i, x, line), flag);
			x = i;
		}
		if (i >= ft_strlen(line) - 1)
			add_word(minishell, build_word(ft_strlen(line), x, line), flag);
		if (i >= ft_strlen(line) - 1)
			break ;
		i++;
	}
}
