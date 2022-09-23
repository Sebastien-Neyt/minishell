/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycollar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:46:45 by cycollar          #+#    #+#             */
/*   Updated: 2022/04/11 14:07:40 by cycollar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstlen >= size)
		return (size + srclen);
	if (srclen < (size - dstlen))
		ft_memcpy((dst + dstlen), src, (srclen + 1));
	else
	{
		ft_memcpy((dst + dstlen), src, (size - dstlen - 1));
		dst[size - 1] = '\0';
	}
	return (dstlen + srclen);
}