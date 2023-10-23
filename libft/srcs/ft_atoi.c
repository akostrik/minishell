/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:38:24 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 03:17:17 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		len;
	int		minus;
	int		n;

	len = 0;
	minus = 1;
	n = 0;
	while ((nptr[len] > 8 && nptr[len] < 14) || nptr[len] == 32)
		len++;
	if (nptr[len] == 43 || nptr[len] == 45)
	{
		if (nptr[len] == 45)
			minus = -1;
		len++;
	}
	while (ft_isdigit(nptr[len]))
	{
		n = (n * 10) + nptr[len] - 48;
		len++;
	}
	if (minus < 0 && n == INT_MIN)
		return (n);
	return (n * minus);
}
