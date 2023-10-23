/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 05:28:15 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 00:54:30 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_cmd_lst_loop(char *line, t_cmd **cmd)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if ((line[i] == '<' || line[i] == '>'))
		{
			if (!add_redr(&line[i], cmd, &i))
				return (free(line), perror(MLC_ERR), 1);
		}
		else if (!add_cmd(&line[i], &((*cmd)->cmd), &i))
			return (free(line), perror(MLC_ERR), 1);
		if (i < 0)
			return (free(line), ft_putstr_fd(TOK_SYN_ERR, 2), 2);
	}
	free(line);
	return (0);
}

int	add_cmd_lst(t_sh *sh, char *cmd_line)
{
	t_cmd	*cmd;
	char	*line;
	int		ret;

	if (!cmd_line)
		return (perror(MLC_ERR), 1);
	line = ft_strtrim(cmd_line, " \t");
	free(cmd_line);
	if (!*line)
		return (free(line), ft_putstr_fd(PIP_SYN_ERR, 2), 2);
	cmd = init_cmd_lst();
	if (!cmd)
		return (free(line), perror(MLC_ERR), 1);
	ret = add_cmd_lst_loop(line, &cmd);
	if (ret)
		return (free_lstcmd(&cmd), ret);
	lstcmd_add_back(&(sh->cmd), cmd);
	return (0);
}

int	count_cmd_line(char *str)
{
	int	j;

	j = 0;
	while (str[j] != '|' && str[j])
	{
		if (in_quotes(&str[j]))
			j += skip_quotes(&str[j + 1], str[j]) + 1;
		j++;
	}
	return (j);
}

char	setup_line(t_sh *sh)
{
	int	i;
	int	j;
	int	ret;

	i = -1;
	while (sh->line[++i])
	{
		j = count_cmd_line(&sh->line[i]);
		if (sh->line[i + j] == '|' || !sh->line[i + j])
		{
			ret = add_cmd_lst(sh, ft_substr(sh->line, i, j));
			if (ret)
				return (ret);
		}
		i = i + j;
		if (!sh->line[i])
			break ;
	}
	if (sh->line[i - 1] == '|')
		return (ft_putstr_fd(PIP_SYN_ERR, 2), 2);
	return (0);
}

//	if (unclosed_quotes(sh->line))
//		return (ft_putstr_fd(UNCL_QUOTES, 2), 2);
int	read_line(t_sh *sh)
{
	char	*line;
	int		ret;

	line = ft_strtrim(sh->line, " \t");
	free(sh->line);
	sh->line = line;
	if (!sh->line || (sh->line && !*sh->line))
		return (0);
	sh->line = expand_var(sh);
	if (!sh->line)
		return (perror(MLC_ERR), 1);
	if (!*sh->line)
		return (0);
	ret = setup_line(sh);
	if (ret)
		return (free_lstcmd(&(sh->cmd)), ret);
	if (sh->cmd)
		if (launch_heredoc(sh, &sh->cmd, &ret))
			return (free_lstcmd(&sh->cmd), reset_hd(sh), ret);
	if (sh->cmd)
		ret = executor(sh);
	return (ret);
}
