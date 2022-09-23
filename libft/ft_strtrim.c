/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycollar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:52:17 by cycollar          #+#    #+#             */
/*   Updated: 2022/04/11 14:09:55 by cycollar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *src, size_t n)
{
	char	*copy;

	copy = malloc(sizeof(char) * (n + 1));
	if (copy == NULL)
		return (0);
	ft_strlcpy(copy, (char *)src, n + 1);
	return (copy);
}

static int	is_in_set(char car, char const *set)
{
	while (*set)
	{
		if (car == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*rt;
	int		start;
	int		end;

	if (s1 == NULL)
		return (NULL);
	end = ft_strlen(s1) - 1;
	start = 0;
	rt = NULL;
	if (!set || !(*set))
		return (ft_strdup(s1));
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	while (end >= start && is_in_set(s1[end], set))
		end--;
	return (ft_strndup((s1 + start), (end - start + 1)));
}
