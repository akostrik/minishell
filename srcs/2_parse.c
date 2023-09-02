/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:22:26 by akostrik          #+#    #+#             */
/*   Updated: 2023/09/03 00:57:42 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.h"

// >out1 >out1+ >> out2 < in >> out2+ < in+ <in++
static void put_full_cmd_to_arg0_1(char *full_cmd, int len, t_data **d)
{
	t_cmd *cmd;
	t_cmd *last;
	int i;

	init_cmd(&cmd, d);
	(*d)->curr_cmd = cmd;
	cmd->nb_args = nb_args_(full_cmd, len, d);
	cmd->arg = (char **)malloc_((cmd->nb_args + 1) * sizeof(char *), d);
	cmd->arg[0] = (char *)malloc_(len + 1, d);
	i = 0;
	while (++i < cmd->nb_args + 1)
		cmd->arg[i] = NULL;
	i = -1;
	while (++i < len)
		cmd->arg[0][i] = full_cmd[i];
	cmd->arg[0][i] = '\0';
	if (*((*d)->cmds) == NULL)
		*((*d)->cmds) = cmd;
	else
	{
		last = *((*d)->cmds);
		while (last != NULL && last->nxt != NULL)
			last = last->nxt;
		last->nxt = cmd;
		cmd->prv = last;
	}
}

void	*open_file(char *redir, char *file, t_cmd *cmd, t_data **d)
{
	//if ((**d)->saved_stdin == -1)
	if (file != NULL && ft_strlen(file) == 0)
			return (printf("%s : err syntaxe\n", cmd->arg[0]), rmv_cmd(cmd, d), NULL);
	if (strcmp_(redir, "<") == 0)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		cmd->fd_in = open(file, O_RDONLY);
		if (!cmd->fd_in)
			return (printf("%s : open file pb\n", cmd->arg[0]), rmv_cmd(cmd, d), NULL);
	}
	else if (strcmp_(redir, "<<") == 0)
	{
		heredoc_to_tmp_file(file, cmd, d); // delimitor = file
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		cmd->fd_in = open(TMP_FILE, O_RDONLY);
		if (!cmd->fd_in)
			return (printf("%s : open file pb\n", cmd->arg[0]), rmv_cmd(cmd, d), NULL);
	}
	else if (strcmp_(redir, "| >") == 0 && cmd->prv != NULL)
	{
		// if (cmd->fd_in != STDIN_FILENO)
		// 	close(cmd->fd_in);
		cmd->fd_in = cmd->prv->fd_pipe[0];
		if (!cmd->fd_in)
			return (printf("%s : pipe pb\n", cmd->arg[0]), rmv_cmd(cmd, d), NULL);
	}
	else if (strcmp_(redir, ">") == 0)
	{
		if (cmd->fd_out != STDIN_FILENO)
			close(cmd->fd_out);
		cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (!cmd->fd_out)
			return (printf("%s : open file pb\n", cmd->arg[0]), rmv_cmd(cmd, d), NULL);
	}
	else if (strcmp_(redir, ">>") == 0)
	{
		if (cmd->fd_out != STDIN_FILENO)
			close(cmd->fd_out);
		cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (!cmd->fd_out)
			return (printf("%s : open file pb\n", cmd->arg[0]), rmv_cmd(cmd, d), NULL);
	}
	else if (strcmp_(redir, "> |") == 0 && cmd->nxt != NULL)
	{
		if (cmd->fd_out != STDIN_FILENO)
			close(cmd->fd_out);
		cmd->fd_out = cmd->fd_pipe[1];
		if (!cmd->fd_out)
			return (printf("%s : pipe pb\n", cmd->arg[0]), rmv_cmd(cmd, d), NULL);
		// if (cmd->fd_out != -1 && cmd->fd_out != STDOUT_FILENO)
		// 	close(cmd->fd_out);
	}
	return (NULL);
}

static void put_redirs(t_cmd *cmd, t_data **d)
{
	char *s;
	int i;
	int i_beg;
	char *redir;
	char *file;

	open_file("| >", NULL, cmd, d);
	mod_(REINIT_QUOTES);
	s = strdup_and_erase_args_except_redirs(cmd->arg[0], d);
	i = -1;
	while (s[++i] != '\0')
	{
		redir = redir_(&s[i]);
		if (mod_(s[i]) == QUOTES0 && ft_strlen(redir) > 0)
		{
			i += ft_strlen(redir);
			i_beg = i;
			while (s[i] == ' ')
				i++;
			while (s[i] != ' ' && s[i] != '>' && s[i] != '<' && s[i] != '\0') // alphanum ?
				i++;
			file = strndup_and_trim(&s[i_beg], i - i_beg + 1, d);
			// remove_quotes(file);
			open_file(redir, file, cmd, d);
		}
		open_file("> |", NULL, cmd, d);
	}
}

static void put_args(t_cmd *cmd, t_data **d)
{
	char	*s;
	int		i;
	int		i_beg;
	int		i_end_arg0;
	int		k;

	if (cmd->nb_args == 0)
		return ;
	mod_(REINIT_QUOTES);
	i_beg = 0;
	k = -1;
	i = -1;
	s = strdup_and_erase_redirs(cmd->arg[0], d);
	while (s[++i] != '\0')
		if (mod_(s[i]) == QUOTES0 && s[i] != ' ' && (s[i + 1] == ' ' \
			|| s[i + 1] == '\0' || s[i + 1] == '\'' || s[i + 1] == '\"'))
		{
			if (++k == 0)
				i_end_arg0 = i + 1;
			else
				cmd->arg[k] = strndup_and_trim(&s[i_beg], i - i_beg + 1, d);
			i_beg = i + 1;
		}
	free(s);
	cmd->arg[0][i_end_arg0] = '\0';
	s = strndup_and_trim(cmd->arg[0], ft_strlen(cmd->arg[0]), d); // strdup_and_trim
	free(cmd->arg[0]);
	cmd->arg[0] = s;
	cmd->arg[cmd->nb_args] = NULL;
}

void	*parse(char *s, t_data **d)
{
	int i_beg;
	int i;

	mod_(REINIT_QUOTES);
	i_beg = 0;
	i = -1;
	while (1)
		if ((mod_(s[++i]) == QUOTES0 && s[i + 1] == '|') || s[i + 1] == '\0')
		{
			put_full_cmd_to_arg0_1(&s[i_beg], i - i_beg + 1, d);
			if (pipe((*d)->curr_cmd->fd_pipe) == -1)
				return (free_all_and_exit("", -1, d), NULL); // no need of pipe for the last cmd
			put_redirs((*d)->curr_cmd, d);
			put_args((*d)->curr_cmd, d);
			if (s[i + 1] == '\0') // ++i
				break;
			i++;
			i_beg = i + 1;
		}
	(*d)->curr_cmd = NULL;
	return (NULL);
}
