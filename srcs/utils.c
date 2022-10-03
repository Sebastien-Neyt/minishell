/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:02:38 by sneyt             #+#    #+#             */
/*   Updated: 2022/10/03 11:07:16 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"
int	ft_strcmpv2(char const *s1, char const *s2)
{
	int	c;

	c = 0;
	while (s1[c] || s2[c])
	{
		if (s1[c] != s2[c])
			return ((unsigned char)(s1[c]) - (unsigned char)(s2[c]));
		c++;
	}
	return (0);
}
