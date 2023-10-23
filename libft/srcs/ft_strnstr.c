/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:29:30 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:32:59 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	big_count;
	size_t	little_count;

	if (!little[0])
		return ((char *)big);
	big_count = -1;
	while (++big_count < len && big[big_count])
	{
		little_count = -1;
		while (++little_count + big_count < len
			&& little[little_count] == big[big_count + little_count])
			if (!little[little_count + 1])
				return ((char *)&big[big_count]);
	}
	return (NULL);
}
