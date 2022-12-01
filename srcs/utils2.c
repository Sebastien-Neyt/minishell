/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:20:29 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/25 10:21:19 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_chars(char *word)
{
	int	i;

	i = 0;
	while (word && word[i])
	{
		if (word[i] == '$' || word[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

int	check_for_exp(t_shell *minishell)
{
	t_list *tmp;

	tmp = minishell->list;
	while (tmp)
	{
		while (check_chars(tmp->word))
		{
			if (tmp->token == SINGLE)
			{
				tmp = tmp->next;
				continue;
			}
			check_expansion(tmp->word, minishell, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}

void trim_pipeline(t_shell *minishell)
{
	t_list *tmp;
	tmp = minishell->pipeline;
	while (tmp)
	{
		//printf("TOKEN: %d || WORD: %s\n", tmp->token, tmp->word);
		if (tmp->token == DOUBLE)
			tmp->word = ft_strtrim(tmp->word, "\"");
		else if (tmp->token == SINGLE)
			tmp->word = ft_strtrim(tmp->word, "'");
		tmp = tmp->next;
	}
}
