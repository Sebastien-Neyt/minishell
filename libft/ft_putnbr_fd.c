/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycollar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:44:01 by cycollar          #+#    #+#             */
/*   Updated: 2022/04/11 14:00:27 by cycollar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	nb2;
	char		a;

	nb2 = n;
	if (fd < 0)
		return ;
	if (n < 0)
	{
		nb2 *= -1;
		ft_putchar_fd('-', fd);
	}
	if (nb2 > 9)
		ft_putnbr_fd(nb2 / 10, fd);
	a = nb2 % 10;
	ft_putchar_fd(a + 48, fd);
}
