/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalimol <akalimol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 03:32:32 by akalimol          #+#    #+#             */
/*   Updated: 2023/06/01 19:43:05 by akalimol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_heredoc
{
	char	*line;
	int		fd[2];
	int		fd_cpy;
	int		status;	
}	t_heredoc;

void	close_heredoc(int fd, int fd_cpy)
{
	close(fd);
	dup2(fd_cpy, STDIN_FILENO); // зачем
	close(fd_cpy);
}

int	get_heredoc(char *delimiter, t_list *env, int *my_fd)
{
	t_heredoc	a;

	a = (t_heredoc){NULL, {0, 0}, dup(STDIN_FILENO), 0};
	if (pipe(a.fd) == -1)
		return (exit_(-1, NULL, NULL, NULL, NULL, NULL), errno);
	signal(SIGINT, &sig_handler_heredoc);
	a.line = readline(">");
	while (a.line && ft_strcmp(a.line, delimiter) != 0)
	{
		a.line = ft_strjoin(ft_expand_string(a.line, env, NULL), "\n"); ///
		if (!a.line && a.status++ < 2)
			break ;
		ft_remove_quotes_string(a.line);
		ft_putstr_fd(a.line, a.fd[1]);
		free(a.line);
		a.line = readline(">");
	}
	if (a.status != 1)
		free(a.line);
	close_heredoc(a.fd[1], a.fd_cpy);
	if (g_signal == 1)
		return (g_signal--, close(a.fd[0]), signal(SIGINT, &sig_handler_main), 130);
	if (a.status != 0)
		return (signal(SIGINT, &sig_handler_main), close(a.fd[0]), 255);
	return (signal(SIGINT, &sig_handler_main), *my_fd = a.fd[0], 0);
}

int	open_heredocs(t_list *head, t_list *env)
{
	t_list	*token;
	void	*temp;
	int		*fd;
	int		status;

	token = head;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			temp = token->next->content;
			fd = (int *)malloc(sizeof(int));
			if (!fd)
				return (-1);
			status = get_heredoc((char *)temp, env, fd);
			if (status != 0)
				return (free(fd), status);
			token->next->content = fd;
			free(temp);
		}
		token = token->next;
	}
	return (0);
}
