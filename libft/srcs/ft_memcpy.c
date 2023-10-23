/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:34:58 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:36:45 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		len;
	char		*s_dest;
	const char	*s_src;

	len = -1;
	if (!dest && !src)
		return (NULL);
	s_dest = (char *)dest;
	s_src = (const char *)src;
	while (++len < n)
		s_dest[len] = s_src[len];
	return (dest);
}
