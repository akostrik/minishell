/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:29:30 by aseremet          #+#    #+#             */
/*   Updated: 2023/07/27 16:38:40 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	s_len;

	if (!s)
		return (NULL);
	c = (unsigned char)c;
	s_len = ft_strlen(s);
	if (c == 0)
		return ((char *)&s[s_len]);
	while (--s_len >= 0)
	{
		if (s[s_len] == c)
			return ((char *)&s[s_len]);
	}
	return (NULL);
}
