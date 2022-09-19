/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:02:38 by sneyt             #+#    #+#             */
/*   Updated: 2022/09/19 12:08:56 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char const *s1, char const *s2)
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
