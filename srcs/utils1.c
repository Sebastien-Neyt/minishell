/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:11:57 by sneyt             #+#    #+#             */
/*   Updated: 2022/11/16 12:00:43 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*env_dup(char *s1)
{
	size_t	len;
	char	*dupe;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	dupe = (char *)malloc((len + 1) * sizeof(char));
	if (!dupe)
		return (0);
	while (i < len)
	{
		dupe[i] = s1[i];
		i++;
	}
	dupe[i] = '\0';
	return (dupe);
}

t_list	*ft_lstnew(char	*content)
{
	t_list	*ans;

	ans = malloc(sizeof(t_list));
	if (!ans)
		return (0);
	ans->word = content;
	ans->next = 0;
	return (ans);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = ft_lstlast(*lst);
	if (!temp)
		*lst = new;
	else
		temp->next = new;
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *s1)
{
	size_t	len;
	char	*dupe;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	dupe = (char *)malloc((len + 1) * sizeof(char));
	if (!dupe)
		return (0);
	while (i < len)
	{
		dupe[i] = s1[i];
		i++;
	}
	dupe[i] = '\0';
	return (dupe);
}

static int	ft_ispartofset(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_substr(char *s,  int start, int len)
{
	char			*ans;
	 int	i;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (0);
	i = 0;
	while (i < len && start + i < ft_strlen(s))
	{
		ans[i] = s[start + i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*ans;
	char	*start;
	char	*end;

	if (!s1 || !set)
		return (0);
	start = (char *)s1;
	end = start + ft_strlen(s1);
	while (*start && ft_ispartofset(*start, set))
		start++;
	while (start < end && ft_ispartofset(*(end - 1), set))
		end--;
	ans = ft_substr(start, 0, end - start);
	return (ans);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rt;
	int		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	rt = malloc(ft_strlen(s1) * sizeof(*s1) + ft_strlen(s2) * sizeof(*s2) + 1);
	if (rt == NULL)
		return (0);
	while (*s1)
	{
		rt[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		rt[i] = *s2;
		s2++;
		i++;
	}
	rt[i] = '\0';
	return (rt);
}
