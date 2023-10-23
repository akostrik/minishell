/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 01:36:36 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/17 11:28:50 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd_lst(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->path = NULL;
	cmd->cmd = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	cmd->pid = -1;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	return (cmd);
}

t_redir	*init_redir_lst(char *str)
{
	t_redir	*redir;
	int		i;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = NULL;
	redir->next = NULL;
	redir->fd = -1;
	redir->type = 0;
	i = 0;
	while (str[i] == '<' && i < 2)
		i++;
	if (i)
		redir->type = i;
	while (!redir->type && str[i] == '>' && i < 2)
		i++;
	if (i && !redir->type)
		redir->type = i + 2;
	return (redir);
}

char	**redo_cmd(char ***og, int *i)
{
	char	**arr;

	if (*og)
	{
		arr = ft_arrdup(*og, ft_arrlen(*og) + 1);
		free_arr(*og);
	}
	else
	{
		arr = malloc(2 * sizeof(char *));
		arr[0] = NULL;
	}
	if (!arr)
		return (NULL);
	*i = 0;
	while (arr && arr[*i])
		(*i)++;
	return (arr);
}

char	**add_cmd(char *str, char ***og, int *ind)
{
	int		len;
	char	**arr;
	int		i;

	i = 0;
	arr = redo_cmd(og, &i);
	if (!arr)
		return (NULL);
	len = get_str_size(str);
	arr[i] = ft_substr(str, 0, len);
	if (!arr[i])
		return (free_arr(arr), NULL);
	arr[i] = unquote(arr[i], count_quotes(arr[i]));
	if (!arr[i])
		return (free_arr(arr), NULL);
	arr[i + 1] = NULL;
	*og = arr;
	(*ind) = (*ind) + len;
	return (*og);
}

int	add_redr(char *str, t_cmd **cmd, int *ind)
{
	t_redir	*redir;
	int		len;
	int		start;

	redir = init_redir_lst(str);
	if (!redir)
		return (0);
	if (invalid_redir_token(str, (size_t)redir->type))
	{
		*ind = -1;
		return (free(redir), *ind);
	}
	start = 1;
	if (redir->type == 2 || redir->type == 4)
		start++;
	while (ft_is_charset(str[start], " \t"))
		start++;
	len = get_str_size(&str[start]);
	redir->file = ft_substr(str, start, len);
	redir->file = unquote(redir->file, count_quotes(redir->file));
	if (!redir->file)
		return (free(redir), 0);
	(*ind) = (*ind) + len + start;
	lstredir_add_back(&((*cmd)->redir), redir);
	return (*ind);
}
