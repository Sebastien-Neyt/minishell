/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:25:36 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/19 13:38:36 by sneyt            ###   ########.fr       */
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
		tmp = ft_strdup(str2);
		if (tmp)
			*str1 = tmp;
		else
			return (0);
		return (1);
	}
	add_nl(str1);
	tmp = ft_strjoin(*str1, str2);
	if (tmp == NULL)
		return (0);
	free(*str1);
	*str1 = tmp;
	return (1);
}

int	add_nl(char **str)
{
	char	*new_str;

	if (*str)
	{
		new_str = ft_strjoin(*str, "\n");
		if (new_str == NULL)
			return (0);
		free(*str);
		*str = new_str;
	}
	return (1);
}
