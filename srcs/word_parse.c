/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:07:39 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/16 13:48:03 by sneyt            ###   ########.fr       */
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
	//printf("%s\n", line);
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
	t_list *new_word;
	if (!minishell->list->word)
	{
		minishell->list->word = word;
		if (flag == 1)
			minishell->list->token = SINGLE;
		else if (flag == 2)
			minishell->list->token = DOUBLE;
		else if (flag == 0)
			minishell->list->token = DEFAULT;
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
			new_word->token = DEFAULT;
	}

}

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

void	word_parse(char *line, t_shell *minishell)
{
	int	i;
	int	offset;
	int flag;

	offset = 0;
	i = 0;
	while (line[i])
	{
		flag = 0;
		if (is_whitespace(line[i]))
		{
			while (is_whitespace(line[i]))
				i++;
			add_word(minishell, build_word(i - 1, offset, line), flag);
			offset = i;
		}	
		if (line[i] == 39)
			flag = 1;
		if (line[i] == 34)
			flag = 2;
		if (flag)
		{
			i = check_quote(flag, line, i);
			
			//if (i < 0)
			//	break ;
			add_word(minishell, build_word(i, offset, line), flag);
			offset = i;
		}
		
		if (i >= ft_strlen(line) - 1)
		{
				add_word(minishell, build_word(ft_strlen(line), offset, line), flag);
				break ;
		}
		
		i++;
	}
}
