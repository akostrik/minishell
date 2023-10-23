/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:02:44 by aseremet          #+#    #+#             */
/*   Updated: 2022/04/17 01:38:44 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_fail(char ***split)
{
	size_t	len;

	len = -1;
	while ((*split)[++len])
		free((*split)[len]);
	free((*split));
	return (NULL);
}

static size_t	how_many_words(char const *s, char c)
{
	size_t	len;
	size_t	nw;

	len = 0;
	nw = 0;
	if (s[len] && s[len] != c)
		nw++;
	while (s[len] && s[++len])
	{
		if (s[len - 1] == c && s[len] != c)
			nw++;
	}
	return (nw);
}

static char	*how_many_letter(char const *s, char c, size_t *len)
{
	size_t	nletter;
	char	*split;

	nletter = 0;
	while (s[*len] && s[*len] == c)
		*len += 1;
	while (s[*len + nletter] && s[*len + nletter] != c)
		nletter++;
	split = malloc((nletter + 1) * sizeof(char));
	if (!split)
		return (NULL);
	ft_memcpy((void *)split, s + *len, nletter);
	split[nletter] = 0;
	*len += nletter;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	size_t	nw;
	size_t	i;
	size_t	len;
	char	**split;

	if (!s)
		return (NULL);
	nw = how_many_words(s, c);
	split = malloc((nw + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (i < nw)
	{
		split[i] = how_many_letter(s, c, &len);
		if (!split[i])
			return (ft_fail(&split));
		i++;
	}
	split[i] = NULL;
	return (split);
}
