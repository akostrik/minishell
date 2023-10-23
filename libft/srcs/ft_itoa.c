/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:42:05 by aseremet          #+#    #+#             */
/*   Updated: 2022/05/04 13:45:38 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	size_t	digits;
	long	nbr;
	char	*str;

	nbr = (long)n;
	digits = 1;
	if (nbr < 0 && digits++)
		nbr *= -1;
	while ((n > 9 || n < -9) && digits++)
		n = n / 10;
	str = malloc((digits + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '-';
	str[digits] = 0;
	while (nbr || (!n && digits))
	{
		str[--digits] = nbr % 10 + 48;
		nbr /= 10;
	}
	return (str);
}
