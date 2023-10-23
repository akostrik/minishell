/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 04:45:12 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/23 17:18:04 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DIR_ERR	": Is a directory\n"

int	manage_dup(int end[4], t_cmd *cmd, int nb)
{
	const int	even = !(nb % 2);

	if (cmd->fd_in != -1 && dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (1);
	else if (cmd->fd_in == -1 && nb > 1 && !even && dup2(end[2], 0) == -1)
		return (1);
	else if (cmd->fd_in == -1 && nb > 1 && even && dup2(end[0], 0) == -1)
		return (1);
	if (cmd->fd_out != -1 && dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (1);
	else if (cmd->fd_out == -1 && cmd->next && !even && dup2(end[1], 1) == -1)
		return (1);
	else if (cmd->fd_out == -1 && cmd->next && even && dup2(end[3], 1) == -1)
		return (1);
	return (0);
}

int	close_fork(t_cmd *cmd, int end[4], int nb)
{
	int	ret;

	ret = 0;
	if ((cmd->fd_in != -1 && close(cmd->fd_in))
		|| (cmd->fd_out != -1 && close(cmd->fd_out)))
		ret = 1;
	if (nb == 1 && !cmd->next)
		return (0);
	else if (nb == 1 && (close(end[0]) || close(end[1])))
		return (1);
	else if (nb > 1 && !cmd->next && !(nb % 2)
		&& (close(end[0]) || close(end[1])))
		return (1);
	else if (nb > 2 && !cmd->next && nb % 2 && (close(end[2]) || close(end[3])))
		return (1);
	else if (nb > 1 && cmd->next
		&& ((end[0] != -1 && close(end[0])) || (end[1] != -1 && close(end[1]))
			|| (end[2] != -1 && close(end[2]))
			|| (end[3] != -1 && close(end[3]))))
		return (1);
	return (ret);
}

void	exit_fork(t_sh *sh, int ret, char *error)
{
	free_lstcmd(&(sh->cmd));
	free(sh->line);
	free_arr(sh->env);
	if (sh->heredoc)
		free(sh->heredoc);
	if (errno && error)
		perror(error);
	exit(ret);
}

int	print_exec_error(t_cmd *cmd)
{
	struct stat	path_stat;

	if (ft_strchr(cmd->path, '/') && errno == EACCES)
	{
		if (stat(cmd->path, &path_stat) == -1)
			return (perror("minishell: stat error"), 126);
		if (S_ISDIR(path_stat.st_mode))
		{
			errno = 0;
			return (ft_error("minishell: ", cmd->path, DIR_ERR, 126));
		}
		else
			return (ft_error("minishell: ", cmd->path, "", 126));
		return (126);
	}
	if (ft_strchr(cmd->path, '/') && errno == ENOTDIR)
		return (ft_error("minishell: ", cmd->path, "", 126));
	if (ft_strchr(cmd->path, '/') && errno)
		return (ft_error("minishell: ", cmd->path, "", 127));
	if (!ft_strchr(cmd->path, '/'))
	{
		return (errno = 0, ft_error("minishell: ", cmd->path,
				": command not found\n", 127));
	}
	return (0);
}

void	ft_fork(t_sh *sh, t_cmd *cmd, int nb)
{
	int	ret;
	
	ret = 0;
	set_signals(2);
	if (cmd->redir)
		ret = manage_redir(&cmd);
	if (ret && (close_fork(cmd, sh->end, nb) || 1))
		exit_fork(sh, ret, NULL);
	if (!cmd->cmd && (close_fork(cmd, sh->end, nb) || 1))
		exit_fork(sh, ret, NULL);
	ret = manage_dup(sh->end, cmd, nb);
	if (ret && (close_fork(cmd, sh->end, nb) || 1))
		exit_fork(sh, ret, "minishell: dup2 error");
	if (is_builtin(cmd->cmd[0]))
		builtin_fork(sh, cmd, nb);
	cmd->path = search_path(sh, cmd);
	if (!cmd->path && (close_fork(cmd, sh->end, nb) || 1))
		exit_fork(sh, 1, MLC_ERR);
	if (close_fork(cmd, sh->end, nb))
		exit_fork(sh, ret, "minishell: close error");
	if (execve(cmd->path, cmd->cmd, sh->env) == -1)
		ret = print_exec_error(cmd);
	exit_fork(sh, ret, NULL);
}
