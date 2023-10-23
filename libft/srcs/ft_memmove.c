/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:34:58 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:37:04 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*s_dest;
	const char	*s_src;

	if (!dest && !src)
		return (NULL);
	s_dest = (char *)dest;
	s_src = (const char *)src;
	if (s_src < s_dest)
	{
		while (n--)
			s_dest[n] = s_src[n];
	}
	else
		dest = ft_memcpy(dest, src, n);
	return (dest);
}
