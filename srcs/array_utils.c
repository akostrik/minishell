/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 03:53:11 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/19 08:16:03 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		free(arr[i]);
	free(arr);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**ft_arrdup(char **arr, int size)
{
	char	**dup;
	int		i;

	if (!arr)
		return (NULL);
	dup = malloc((size + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
			return (free_arr(dup), NULL);
	}
	dup[i] = NULL;
	return (dup);
}
