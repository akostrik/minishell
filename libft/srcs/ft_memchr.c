/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:34:58 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:37:24 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			len;
	unsigned char	*str;

	len = -1;
	str = (unsigned char *)s;
	c = (unsigned char)c;
	while (++len < n)
	{
		if (str[len] == c)
			return ((void *)&str[len]);
	}
	return (NULL);
}
