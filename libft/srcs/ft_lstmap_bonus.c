/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:52:13 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:54:43 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*map;
	t_list	*previous;

	if (!lst)
		return (NULL);
	first = NULL;
	while (lst)
	{
		previous = map;
		map = ft_lstnew((*f)(lst->content));
		if (!map)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		if (!first)
			first = map;
		else
			previous->next = map;
		lst = lst->next;
	}
	return (first);
}
