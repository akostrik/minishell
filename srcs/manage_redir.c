/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:44:08 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/20 04:00:35 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_out(t_cmd **cmd, t_redir *tmp)
{
	if (tmp->type == OUT)
		tmp->fd = open(tmp->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (tmp->type == OUT_A)
		tmp->fd = open(tmp->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (tmp->fd == -1)
		return (ft_error("minishell: ", tmp->file, "\0", 1));
	if ((*cmd)->fd_out != -1 && close((*cmd)->fd_out))
		return (perror("minishell: close error"), 1);
	(*cmd)->fd_out = tmp->fd;
	return (0);
}

int	dup_builtin_solo(t_sh *sh, t_cmd **cmd, int sof)
{
	if (sof)
	{
		if ((*cmd)->fd_in != -1)
			sh->fd_stdin = dup(STDIN_FILENO);
		if ((*cmd)->fd_out != -1)
			sh->fd_stdout = dup(STDOUT_FILENO);
		if (((*cmd)->fd_in != -1 && dup2((*cmd)->fd_in, 0) == -1)
			|| ((*cmd)->fd_out != -1 && dup2((*cmd)->fd_out, 1) == -1))
		{
			if (((*cmd)->fd_in != -1 && close((*cmd)->fd_in))
				|| ((*cmd)->fd_out != -1 && close((*cmd)->fd_out)))
				return (perror("minishell: close error"), 1);
			return (perror("minishell: dup2 error"), 1);
		}
		return (0);
	}
	if (((((*cmd)->fd_in != -1 && dup2(sh->fd_stdin, 0) == -1))
			|| ((*cmd)->fd_out != -1 && dup2(sh->fd_stdout, 1) == -1)))
	{
		if (((*cmd)->fd_in != -1 && close((*cmd)->fd_in))
			|| ((*cmd)->fd_out != -1 && close((*cmd)->fd_out)))
			return (perror("minishell: close error"), 1);
		return (perror("minishell: dup2 error"), 1);
	}
	return (0);
}

int	manage_redir(t_cmd **cmd)
{
	t_redir	*tmp;
	int		ret;

	ret = 0;
	tmp = (*cmd)->redir;
	while (tmp)
	{
		if (tmp->type == H_DOC || tmp->type == IN)
		{
			tmp->fd = open(tmp->file, O_RDONLY);
			if (tmp->fd == -1)
				return (ft_error("minishell: ", tmp->file, "\0", 1));
			if ((*cmd)->fd_in != -1 && close((*cmd)->fd_in))
				return (perror("minishell: close error"), 1);
			(*cmd)->fd_in = tmp->fd;
		}
		else if (tmp->type == OUT || tmp->type == OUT_A)
			ret = open_redir_out(cmd, tmp);
		if (ret)
			return (ret);
		tmp = tmp->next;
	}
	return (ret);
}
