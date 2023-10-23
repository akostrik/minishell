/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:24:53 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:28:13 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	s_len;
	char	*dup;

	s_len = ft_strlen(s);
	dup = malloc((s_len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	len = -1;
	while (s[++len])
		dup[len] = s[len];
	dup[len] = 0;
	return (dup);
}
