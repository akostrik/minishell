/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:08:53 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/20 06:34:03 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_fd(t_cmd *cmd, int end[4], int nb)
{
	const int	even = !(nb % 2);

	if (nb == 1 && !cmd->next)
		return (0);
	if (nb > 1 && even && (close(end[0]) || close(end[1])))
		return (1);
	else if (nb > 2 && !even && (close(end[2]) || close(end[3])))
		return (1);
	return (0);
}

int	open_pipe(t_sh *sh, int nb)
{
	if (nb % 2 && pipe(sh->end))
	{
		if (nb > 1 && (close(sh->end[2]) || close(sh->end[3])))
			perror("minishell: close error");
		return (1);
	}
	else if (!(nb % 2) && pipe(sh->end + 2))
	{
		if (close(sh->end[0]) || close(sh->end[1]))
			perror("minishell: close error");
		return (1);
	}
	return (0);
}

int	catch_status(t_sh *sh, t_cmd *cmd)
{
	int	wstatus;

	while (cmd)
	{
		if (cmd->pid)
			waitpid(cmd->pid, &wstatus, 0);
		cmd = cmd->next;
	}
	if (reset_hd(sh))
		return (1);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == 2)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		return (130);
	}
	else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == 3)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		rl_on_new_line();
		return (131);
	}
	return (-1);
}

int	executor(t_sh *sh)
{
	t_cmd	*tmp;
	int		nb;

	tmp = sh->cmd;
	set_signals(0);
	if (sh->cmd->cmd && lst_size(sh->cmd) == 1 && is_builtin(sh->cmd->cmd[0]))
		return (builtin_solo(sh, &sh->cmd));
	nb = 0;
	while (tmp && ++nb)
	{
		if (tmp->next && open_pipe(sh, nb))
			return (catch_status(sh, sh->cmd),
				perror("minishell: pipe error"), 129);
		tmp->pid = fork();
		if (tmp->pid == -1)
			return (catch_status(sh, sh->cmd), perror("minishell: fork"), 254);
		if (tmp->pid == 0)
			ft_fork(sh, tmp, nb);
		if (close_fd(tmp, sh->end, nb))
			return (catch_status(sh, sh->cmd),
				perror("minishell: close error"), 1);
		tmp = tmp->next;
	}
	return (catch_status(sh, sh->cmd));
}
