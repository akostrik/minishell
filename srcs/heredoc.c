/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 03:58:53 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 16:13:54 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	generate_hd_name(t_sh *sh)
{
	static int	i = 0;
	char		*num;

	num = ft_itoa(i++);
	if (!num)
		return (perror(MLC_ERR), 1);
	sh->heredoc = ft_strjoin(".tmp_hd_", num);
	free(num);
	if (!sh->heredoc)
		return (perror(MLC_ERR), 1);
	return (0);
}

int	read_heredoc(t_sh *sh, t_redir *tmp)
{
	free(sh->line);
	sh->line = readline("> ");
	while (sh->line)
	{
		sh->line = expand_var(sh);
		if (!sh->line)
			return (perror(MLC_ERR), 1);
		if (!ft_strncmp(tmp->file, sh->line, ft_strlen(tmp->file) + 1))
			break ;
		if (write(tmp->fd, sh->line, ft_strlen(sh->line))
			< (ssize_t)ft_strlen(sh->line))
			return (perror("minishell: write error"), 1);
		if (write(tmp->fd, "\n", 1) < 1)
			return (perror("minishell: write error"), 1);
		free(sh->line);
		sh->line = readline("> ");
	}
	if (close(tmp->fd))
		return (perror("minishell: close error"), 1);
	if (!sh->line && tmp->file)
		return (ft_error(HD_ERR, tmp->file, "')\n", 0));
	if (!sh->line)
		free(sh->line);
	sh->line = NULL;
	return (0);
}

int	catch_status_hd(int pid, t_sh *sh, t_redir *tmp)
{
	int	wstatus;

	waitpid(pid, &wstatus, 0);
	free(tmp->file);
	tmp->file = ft_strdup(sh->heredoc);
	if (close(tmp->fd))
		return (perror("minishell: close error"), 1);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == 2)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		return (130);
	}
	return (0);
}

int	prepare_heredoc(t_sh *sh, t_redir *tmp, int *first)
{
	int	pid;

	if (generate_hd_name(sh))
		return (1);
	tmp->fd = open(sh->heredoc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp->fd == -1)
		return (perror("minishell: open error"), 1);
	*first = 1;
	pid = fork();
	if (pid < 0)
		return (perror("minishell: fork"), 254);
	if (pid == 0)
	{
		set_signals(3);
		if (read_heredoc(sh, tmp))
			exit_fork(sh, 1, NULL);
		exit_fork(sh, 0, NULL);
	}
	return (catch_status_hd(pid, sh, tmp));
}

// int	prepare_heredoc(t_sh *sh, t_redir *tmp)
// {
// 	if (generate_hd_name(sh))
// 		return (1);
// 	sh->fd_stdin = dup(STDIN_FILENO);
// 	tmp->fd = open(sh->heredoc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (tmp->fd == -1)
// 		return (perror("minishell: open error"), 1);
// 	set_signals(3);
// 	sh->exit_s = 0;
// 	if (read_heredoc(sh, tmp))
// 		return (set_signals(1), 1);
// 	set_signals(1);
// 	dup2(sh->fd_stdin, STDIN_FILENO);
// 	close(sh->fd_stdin);
// 	sh->fd_stdin = 0;
// 	free(tmp->file);
// 	tmp->file = ft_strdup(sh->heredoc);
// 	if (sh->exit_s)
// 		return (sh->exit_s);
// 	return (0);
// }

int	launch_heredoc(t_sh *sh, t_cmd **cmd, int *ret)
{
	t_redir	*tmp;
	t_cmd	*top;
	int		first;

	*ret = 0;
	top = *cmd;
	while (top)
	{
		first = 0;
		tmp = top->redir;
		while (tmp)
		{
			if (tmp->type == H_DOC)
				if (first)
					*ret = redir_delone(&top, (*cmd)->redir, sh);
			if (!(*ret) && tmp->type == H_DOC)
				*ret = prepare_heredoc(sh, tmp, &first);
			if (*ret)
				return (*ret);
			tmp = tmp->next;
			first = 1;
		}
		top = top->next;
	}
	return (0);
}
