/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 09:45:08 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/13 09:46:00 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(char *src, int n)
{
	char	*copy;

	copy = malloc(sizeof(char) * (n + 1));
	if (copy == NULL)
		return (0);
	ft_strlcpy(copy, (char *)src, n + 1);
	return (copy);
}

static char	*ft_wordup(char *s, char c, int i)
{
	int	start;
	int	len;

	start = 0;
	len = 0;
	while (s[start] == c && s[start])
		start++;
	while (i > 0)
	{
		while (s[start] && s[start] != c)
			start++;
		while (s[start] && s[start] == c)
			start++;
		i--;
	}
	while (s[start + len] != c && s[start + len])
		len++;
	return (ft_strndup(&s[start], len));
}

static void	clean(char **rt, int word)
{
	while (word >= 0)
	{
		if (rt[word] != NULL)
			free(rt[word]);
		word--;
	}
	free(rt);
}

static int	count_words(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		if (*s && *s != c)
		{
			while (*s && *s != c)
				s++;
			words++;
		}
		else
			while (*s && *s == c)
				s++;
	}
	return (words);
}

char	**ft_split(char *s, char c)
{
	char	**rt;
	int		i;
	int		words;

	words = 0;
	i = 0;
	rt = NULL;
	if (s == NULL)
		return (0);
	words = count_words(s, c);
	rt = malloc(sizeof(char *) * (words + 1));
	if (rt == NULL)
		return (0);
	rt[words] = NULL;
	while (i < words)
	{
		rt[i] = ft_wordup((char *)s, c, i);
		if (rt[i] == NULL)
		{
			clean(rt, words);
			return (0);
		}
		i++;
	}
	return (rt);
}
