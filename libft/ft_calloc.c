/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycollar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:00:18 by cycollar          #+#    #+#             */
/*   Updated: 2022/04/12 10:37:16 by cycollar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pt;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if ((SIZE_MAX / count < size) || (SIZE_MAX / size < count))
		return (NULL);
	pt = malloc(count * size);
	if (pt == NULL)
		return (NULL);
	ft_bzero(pt, count * size);
	return (pt);
}
