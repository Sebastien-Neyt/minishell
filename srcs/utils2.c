/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:20:29 by sneyt             #+#    #+#             */
/*   Updated: 2023/01/13 11:17:22 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_chars(char *word)
{
	int	i;

	i = 0;
	while (word && word[i])
	{
		if (word[i] == '~' && (word[i + 1] != '/' && word[i + 1] != '\0'))
			return (0);
		else if (((word[i] == '$' || word[i] == '~')) \
			&& ((!is_one_of(word[i + 1]) && word[i + 1] != '$')))
			return (1);
		else if (word[i] == '~' && word[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	check_for_exp(t_shell *minishell)
{
	t_list	*tmp;

	tmp = minishell->list;
	while (tmp)
	{
		while (check_chars(tmp->word))
		{
			if (tmp->token == SINGLE)
			{
				tmp = tmp->next;
				continue ;
			}
			check_expansion(minishell, tmp, 0, NULL);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	trim_pipeline(t_shell *minishell)
{
	t_list	*tmp;
	char	*str;

	tmp = minishell->pipeline;
	while (tmp)
	{
		if (tmp->token == DOUBLE)
		{
			str = ft_strtrim(tmp->word, "\"");
			tmp->word = str;
		}
		else if (tmp->token == SINGLE)
		{
			str = ft_strtrim(tmp->word, "'");
			tmp->word = str;
		}
		tmp = tmp->next;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *s1)
{
	size_t	len;
	char	*dupe;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	dupe = (char *)malloc((len + 1) * sizeof(char));
	if (!dupe)
		return (0);
	while (i < len)
	{
		dupe[i] = s1[i];
		i++;
	}
	dupe[i] = '\0';
	return (dupe);
}
