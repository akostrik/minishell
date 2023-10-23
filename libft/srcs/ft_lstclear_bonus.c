/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:52:13 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:54:17 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*first;
	t_list	*mem;

	if (!lst)
		return ;
	first = *lst;
	while (first)
	{
		mem = first->next;
		ft_lstdelone(first, del);
		first = mem;
	}
	*lst = NULL;
}
