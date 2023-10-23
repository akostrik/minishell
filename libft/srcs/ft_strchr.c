/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:29:30 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:31:40 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	len;

	c = (unsigned char)c;
	len = -1;
	while (s[++len])
	{
		if (s[len] == c)
			return ((char *)&s[len]);
	}
	if (c == 0)
		return ((char *)&s[len]);
	return (NULL);
}
