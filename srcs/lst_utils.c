/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:56:02 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/18 09:53:22 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// only need free include
#include "minishell.h"

int	lst_size(t_cmd *cmd)
{
	int	len;

	len = 0;
	if (!cmd)
		return (len);
	while (cmd && ++len)
		cmd = cmd->next;
	return (len);
}

void	free_lstredir(t_redir **redir)
{
	t_redir	*first;
	t_redir	*mem;

	if (!redir)
		return ;
	first = *redir;
	while (first)
	{
		mem = first->next;
		free(first->file);
		free(first);
		first = mem;
	}
	*redir = NULL;
}

void	free_lstcmd(t_cmd **cmd)
{
	t_cmd	*first;
	t_cmd	*mem;

	if (!cmd)
		return ;
	first = *cmd;
	while (first)
	{
		mem = first->next;
		if (first->path)
			free(first->path);
		if (first->cmd)
			free_arr(first->cmd);
		free_lstredir(&(first->redir));
		free(first);
		first = mem;
	}
	*cmd = NULL;
}

void	lstredir_add_back(t_redir **redir, t_redir *new)
{
	t_redir	*last;

	if (!redir)
		return ;
	if (!*redir)
		*redir = new;
	else
	{
		last = *redir;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	lstcmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last;

	if (!cmd)
		return ;
	if (!*cmd)
		*cmd = new;
	else
	{
		last = *cmd;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
