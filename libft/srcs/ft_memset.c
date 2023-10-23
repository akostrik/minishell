/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:34:58 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:36:25 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	len;
	char	*str;

	len = -1;
	str = (char *)s;
	while (++len < n)
		str[len] = c;
	return (s);
}
