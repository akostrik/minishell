/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:49:37 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 14:00:17 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset_hd(t_sh *sh)
{
	if (sh->heredoc && unlink(sh->heredoc) == -1)
	{
		free(sh->heredoc);
		sh->heredoc = NULL;
		return (perror("minishell: unlink error"), 1);
	}
	if (sh->heredoc)
		free(sh->heredoc);
	sh->heredoc = NULL;
	return (0);
}

int	redir_delone(t_cmd **cmd, t_redir *redir, t_sh *sh)
{
	t_redir	*tmp;
	t_redir	*last;

	tmp = redir;
	last = NULL;
	while (tmp)
	{
		if (redir->type == H_DOC)
		{
			if (!last)
				(*cmd)->redir = tmp->next;
			else
				last->next = tmp->next;
			free(tmp->file);
			free(tmp);
			return (reset_hd(sh));
		}
		tmp = tmp->next;
	}
	return (reset_hd(sh));
}

char	*better_strjoin(char const *s1, char const *s2, char const *s3)
{
	char	*join;
	size_t	len;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	len = s1_len + s2_len + s3_len;
	join = malloc((len + 1) * sizeof(char));
	if (!join)
		return (NULL);
	join[0] = 0;
	ft_strlcat(join, s1, len + 1);
	ft_strlcat(join, s2, len + 1);
	ft_strlcat(join, s3, len + 1);
	return (join);
}

int	ft_error(char *err, char *var, char *end, int ret)
{
	char	*join;

	join = better_strjoin(err, var, end);
	if (!join)
		return (perror(MLC_ERR), 1);
	if (errno)
		perror(join);
	else
		ft_putstr_fd(join, 2);
	free(join);
	return (ret);
}

int	is_builtin(char *cmd)
{
	int			len;

	if (!cmd)
		return (0);
	len = ft_strlen(cmd) + 1;
	if (!ft_strncmp("echo", cmd, len) || !ft_strncmp("cd", cmd, len)
		|| !ft_strncmp("pwd", cmd, len) || !ft_strncmp("export", cmd, len)
		|| !ft_strncmp("unset", cmd, len) || !ft_strncmp("env", cmd, len)
		|| !ft_strncmp("exit", cmd, len))
		return (1);
	return (0);
}
