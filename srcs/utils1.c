/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:11:57 by sneyt             #+#    #+#             */
/*   Updated: 2022/12/21 09:20:30 by sneyt            ###   ########.fr       */
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

//legit the same as a strdupe.
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

//creates a new list node.
t_list	*ft_lstnew(char	*content, t_shell *minishell)
{
	t_list	*ans;

	ans = malloc(sizeof(t_list));
	if (!ans)
		ft_exit(minishell, FAILED_MALLOC);
	ans->word = content;
	ans->token = 0;
	ans->next = 0;
	return (ans);
}

//gets the last node of our linked list.
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

//adds our new node as the last node in our list.
int	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return (1);
	temp = ft_lstlast(*lst);
	if (!temp)
		*lst = new;
	else
		temp->next = new;
	return (0);
}
