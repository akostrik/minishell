/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 04:25:00 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 13:47:39 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*empty_str(void)
{
	char	*str;

	str = malloc(1 * sizeof(char));
	if (!str)
		NULL;
	str[0] = 0;
	return (str);
}

char	*find_env_var(char **envp, char *str)
{
	int		i;
	int		n;
	char	*var;

	if (!envp)
		return (NULL);
	var = ft_strjoin(str, "=");
	if (!var)
		return (NULL);
	n = ft_strlen(var);
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], var, n))
			return (free(var),
				ft_substr(envp[i], n, ft_strlen(envp[i]) - n));
	return (free(var), empty_str());
}

static char	*substitue_value(int len, int end[2], char *og_line, char *value)
{
	int		i;
	int		j;
	char	*line;

	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (free(og_line), NULL);
	i = 0;
	j = 0;
	while (j < len)
	{
		if (i == end[1])
		{
			j += ft_strlcpy(&line[j], value, ft_strlen(value) + 1);
			i += end[0];
		}
		if (j < len)
			line[j++] = og_line[i++];
	}
	line[j] = 0;
	free(og_line);
	free(value);
	return (line);
}

	// if (!*value)
	// 	(*dol)--;
static char	*apply_value(char *search, int end, t_sh *sh, int *dol)
{
	char	*var;
	char	*value;
	int		new_len;
	int		ind[2];

	ind[0] = end;
	ind[1] = *dol;
	var = malloc(end * sizeof(char));
	if (!var)
		return (free(sh->line), NULL);
	ft_strlcpy(var, search, end);
	if (!ft_strncmp(var, "?", 1))
		value = ft_itoa((int)sh->exit_s);
	else
		value = find_env_var(sh->env, var);
	free(var);
	if (!value)
		return (free(sh->line), NULL);
	new_len = ft_strlen(sh->line) - end + ft_strlen(value);
	if (!new_len)
		return (free(value), free(sh->line), empty_str());
	return (substitue_value(new_len, ind, sh->line, value));
}

char	*expand_var(t_sh *sh)
{
	int		i;
	int		j;

	i = -1;
	while (sh->line && sh->line[++i])
	{
		if (sh->line[i] == '\'')
			i += skip_quotes(&sh->line[i + 1], '\'');
		j = 0;
		while (sh->line[i] == '$' && ++j && sh->line[i + j])
		{
			if ((j == 1 && sh->line[i + j] == '?' && ++j)
				|| (ft_isspace(sh->line[i + j])
					|| not_valid_id(sh->line[i + j], &sh->line[i])))
				break ;
		}
		if (sh->line[i] == '$' && (j > 1))
			sh->line = apply_value(&sh->line[i + 1], j, sh, &i);
		if (!sh->line)
			return (NULL);
		if (!sh->line[i])
			break ;
	}
	return (sh->line);
}
