/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:24:53 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:26:43 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	len;

	src_len = ft_strlen(src);
	len = -1;
	if (size > 0)
	{
		while (++len < size - 1 && src[len])
			dst[len] = src[len];
		dst[len] = 0;
	}
	return (src_len);
}
