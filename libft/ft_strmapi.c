/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycollar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:09 by cycollar          #+#    #+#             */
/*   Updated: 2022/04/11 14:08:46 by cycollar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*rt;

	i = 0;
	if (s == NULL || f == NULL)
		return (0);
	rt = malloc((ft_strlen(s) + 1) * (sizeof(char)));
	if (rt == NULL)
		return (0);
	while (s[i])
	{
		rt[i] = (*f)(i, s[i]);
		i++;
	}
	rt[i] = '\0';
	return (rt);
}
