/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:07:39 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/02 15:15:55 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}


char	*build_word(int	i, int	offset, char *line)
{
	char *word;
	int	x;
	int	y;

	y = 0;
	x = offset;
	word = malloc(sizeof(char) * (i - offset + 1));
	//if (!word)
	//	error
	while (y < i - offset)
	{
		word[y] = line[x];
		x++;
		y++;
	}
	word[y] = '\0';
	return (word);	
}

void	add_word(t_shell *minishell, char *word)
{
	t_list *new_word;
	if (!minishell->list->word)
		minishell->list->word = word;
	else
	{
		new_word = ft_lstlast(minishell->list);
		ft_lstadd_back(&minishell->list, ft_lstnew(word));
	}
}

int	check_quote(int type, char *line, int i)
{
	int	flag;
	
	flag = 0;
	i++;
	while (type == 1 && (line[i] != 39)) // || line[i] != '\0'))i
	{
		i++;
		flag = 1;
	}
	while (type == 2 && (line[i] != 34)) //|| line[i] != '\0'))
	{	
		i++;
		flag = 1;
	}
	if (flag)
		return (-1);
	return (i + 1);
}

void	word_parse(char *line, t_shell *minishell)
{
	int	i;
	int	offset;
	int	flag;

	offset = 0;
	i = 0;
	while (line[i])
	{
		flag = 0;
		if (is_whitespace(line[i]))
		{
			while (is_whitespace(line[i]))
				i++;
			add_word(minishell, build_word(i - 1, offset, line));
			offset = i;
		}
		/*
		if (line[i] == 39)
			flag = 1;
		if (line[i] == 34)
			flag = 2;
		if (flag)
		{
			i = check_quote(flag, line, i);
			if (i < 0)
				break ;
			add_word(minishell, build_word(i, offset, line));
			offset = i;
		}
		*/
		if (i >= ft_strlen(line) - 1)
		{
				add_word(minishell, build_word(ft_strlen(line), offset, line));
				break ;
		}
		
		i++;
	}
}
