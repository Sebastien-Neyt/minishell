/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycollar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:46:32 by cycollar          #+#    #+#             */
/*   Updated: 2022/04/11 14:07:37 by cycollar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
