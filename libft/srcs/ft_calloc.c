/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:38:24 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:40:58 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*memb;
	const size_t	m_comp = nmemb * size;

	if (m_comp && nmemb != m_comp / size)
		return (NULL);
	memb = malloc(nmemb * size);
	if (!memb)
		return (NULL);
	memb = ft_memset(memb, 0, nmemb * size);
	return (memb);
}
