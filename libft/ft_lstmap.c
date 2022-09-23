/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycollar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:56:07 by cycollar          #+#    #+#             */
/*   Updated: 2022/04/11 14:25:45 by cycollar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cpy;
	t_list	*start;

	if (!f || !del || !lst)
		return (NULL);
	cpy = NULL;
	start = cpy;
	while (lst)
	{
		cpy = ft_lstnew((*f)(lst->content));
		if (cpy->content == NULL)
			ft_lstclear(&start, del);
		ft_lstadd_back(&start, cpy);
		lst = lst->next;
	}
	return (start);
}
