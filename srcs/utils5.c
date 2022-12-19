/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:25:36 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 09:26:17 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	append_str(char **str1, char *str2)
{
	char	*tmp;

	if (str2 == NULL)
		return (1);
	if (*str1 == NULL)
	{
		*str1 = str2;
		return (1);
	}
	tmp = ft_strjoin(*str1, str2);
	if (tmp == NULL)
		return (0);
	free(*str1);
	*str1 = tmp;
	return (1);
}
