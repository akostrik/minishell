/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 00:12:57 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 13:59:34 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
only need malloc include
*/
#include "libft.h"

int	in_quotes(char *str);

/*
var name cannot have these char
bash: export: `poru+t=mouche': not a valid identifier for export error
*/
int	not_valid_id(char c, char *str)
{
	if ((c >= 32 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 94)
		|| (c == 96) || (c >= 123 && c <= 126))
		return (1);
	if (str[0] >= 48 && str[0] <= 57)
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

int	skip_quotes(char *line, char type)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != type)
		i++;
	return (i);
}

int	unclosed_quotes(char *line)
{
	int		i;
	char	type;

	i = -1;
	type = 0;
	while (line[++i])
	{
		if (line[i] == '"' || line[i] == '\'')
			type = line[i];
		while (type != 0 && line[++i])
		{
			if (line[i] == type)
				type = 0;
		}
		if (!line[i])
			break ;
	}
	if (type == '"' || type == '\'')
		return (1);
	return (0);
}

int	count_quotes(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (in_quotes(&str[i]))
		{
			i += skip_quotes(&str[i + 1], str[i]) + 1;
			count += 2;
		}
		i++;
	}
	return (count);
}
