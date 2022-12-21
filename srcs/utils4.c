/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 09:48:24 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/21 11:24:27 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//checks if c is in set.
static int	ft_ispartofset(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

//creates a substring from start till len is reached.
char	*ft_substr(char *s, int start, int len)
{
	char	*ans;
	int		i;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (0);
	i = 0;
	while (i < len && start + i < ft_strlen(s))
	{
		ans[i] = s[start + i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

//trims all set chars in the front and back.
char	*ft_strtrim(char *s1, char *set)
{
	char	*ans;
	char	*start;
	char	*end;

	if (!s1 || !set)
		return (0);
	start = (char *)s1;
	end = start + ft_strlen(s1);
	while (*start && ft_ispartofset(*start, set))
		start++;
	while (start < end && ft_ispartofset(*(end - 1), set))
		end--;
	ans = ft_substr(start, 0, end - start);
	return (ans);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*rt;
	int		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	rt = malloc(ft_strlen(s1) * sizeof(*s1) + ft_strlen(s2) * sizeof(*s2) + 1);
	if (rt == NULL)
		return (0);
	while (*s1)
	{
		rt[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		rt[i] = *s2;
		s2++;
		i++;
	}
	rt[i] = '\0';
	return (rt);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = 0;
	while (src[n] != '\0')
		n++;
	if (size == 0)
		return (n);
	while (i < (size - 1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	i = 0;
	return (n);
}
