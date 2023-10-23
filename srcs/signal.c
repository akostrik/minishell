/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:09:50 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/20 08:35:30 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>
#include "libft.h"

extern unsigned char	g_exit_status;

// exit status = 130
static	void	shell_ctrl_c(int signal)
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 128 + (char)signal;
}

// rl_redisplay();
// rl_replace_line("", 0);
// static	void	heredoc_ctrl_c(int signal)
// {
// 	g_exit_status = 128 + (char)signal;
// 	write(2, "\n", 1);
// 	close(STDIN_FILENO);
// }

/*
mode 0 parent during fork
mode 1 readline
mode 2 child process
mode 3 heredoc
*/
void	set_signals(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1 || mode == 3)
	{
		if (mode == 1)
			signal(SIGINT, shell_ctrl_c);
		if (mode == 3)
			signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
