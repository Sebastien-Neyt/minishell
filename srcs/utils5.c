/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 09:25:36 by sneyt             #+#    #+#             */
/*   Updated: 2023/01/02 16:49:54 by sneyt            ###   ########.fr       */
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

int	ft_atoi(char *str)
{
	int					sign;
	unsigned long long	nb;

	sign = 1;
	nb = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		nb = nb * 10 + *str - 48;
		if (nb > LONG_MAX && sign == 1)
			return (-1);
		if (nb > ((unsigned long)LONG_MAX + 1) && sign == -1)
			return (0);
		str++;
	}
	return ((int)(nb * sign));
}

int	ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9'));
}

int	is_num(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
