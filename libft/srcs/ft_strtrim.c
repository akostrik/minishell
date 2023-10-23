/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:42:05 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:45:25 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	end;
	size_t	start;
	char	*trim;

	start = 0;
	if (!s1)
		return (NULL);
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]) && s1[end - 1])
		end--;
	len = end - start;
	trim = malloc((len + 1) * sizeof(char));
	if (!trim)
		return (NULL);
	trim[len] = 0;
	while (len--)
		trim[len] = s1[--end];
	return (trim);
}
