/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycollar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:41:26 by cycollar          #+#    #+#             */
/*   Updated: 2022/04/11 13:52:47 by cycollar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str(long long n2, int size, int sign, long long d)
{
	int		i;
	char	*string;

	i = 0;
	string = malloc(sizeof(char) * (size + 1));
	if (string == NULL)
		return (0);
	if (sign == -1)
	{
		string[i] = '-';
		i++;
	}
	while (d >= 1)
	{
		string[i] = ((n2 / d) + 48);
		i++;
		n2 -= ((n2 / d) * d);
		d /= 10;
	}
	string[i] = '\0';
	return (string);
}

char	*ft_itoa(int n)
{
	int			size;
	long long	d;
	int			sign;
	long long	n2;

	n2 = n;
	sign = 1;
	d = 1;
	size = 0;
	if (n2 == 0)
		return (ft_strdup("0"));
	if (n2 < 0)
	{
		size++;
		sign = -1;
		n2 *= -1;
	}
	while ((n2 / d) >= 1)
	{
		size++;
		d *= 10;
	}
	return (str(n2, size, sign, (d / 10)));
}
