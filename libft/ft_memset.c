/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycollar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:43:26 by cycollar          #+#    #+#             */
/*   Updated: 2022/04/11 13:59:37 by cycollar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	c2;

	c2 = c;
	i = 0;
	s = (unsigned char *)b;
	while (i < len)
	{
		s[i] = c2;
		i++;
	}
	return (b);
}
