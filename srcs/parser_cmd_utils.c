/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 23:02:20 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/13 15:54:34 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_quotes(char *line, char type);

int	in_quotes(char *str)
{
	return (str[0 + 1] && ((str[0] == '"' && ft_strchr(&str[0 + 1], '"'))
			|| (str[0] == '\'' && ft_strchr(&str[0 + 1], '\''))));
}

int	ft_is_charset(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	invalid_redir_token(char *str, size_t type)
{
	if ((type < 3 && (ft_is_charset(str[type], "<>")
				|| ft_strlen(str) == type))
		|| (type == 3 && (str[1] == '<' || ft_strlen(str) == 1))
		|| (type == 4 && (ft_is_charset(str[2], "<>") || ft_strlen(str) == 2)))
		return (1);
	return (0);
}

int	get_str_size(char *str)
{
	int		i;
	char	type;

	i = 0;
	type = 0;
	while (str[i] && (!ft_is_charset(str[i], " \t<>") || type))
	{
		if (str[i] == '\'' && !type && str[i + 1]
			&& ft_strchr(&str[i + 1], '\''))
		{
			type = '\'';
			i++;
		}
		else if (str[i] == '"' && !type && str[i + 1]
			&& ft_strchr(&str[i + 1], '"'))
		{
			type = '"';
			i++;
		}
		if (type && str[i] == type)
			type = 0;
		i++;
	}
	return (i);
}

char	*unquote(char *str, int count)
{
	char	*unq;
	int		i;
	int		j;

	if (count < 2 || (!str && !str[0]))
		return (str);
	unq = malloc((ft_strlen(str) - count + 1) * sizeof(char));
	if (!unq)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (in_quotes(&str[i]) && ft_strlcpy(&unq[j], &str[i + 1],
				skip_quotes(&str[i + 1], str[i]) + 1))
		{
			j += skip_quotes(&str[i + 1], str[i]);
			i += skip_quotes(&str[i + 1], str[i]) + 2;
		}
		else
			unq[j++] = str[i++];
	}
	unq[j] = 0;
	free(str);
	return (unq);
}
