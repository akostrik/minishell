/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:16:19 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 10:01:43 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	g_exit_status = 0;

/*
char	**create_env(void)
{
	char	**env;
	char	buf[4096];

	if (getcwd(buf, sizeof(buf)) == NULL)
		return (perror("minishell: getcwd error"), NULL);
	env = malloc(4 * sizeof(char *));
	if (!env)
		return (NULL);
	env[0] = ft_strjoin("PWD=", buf);
	if (!env[0])
		return (free(env), NULL);
	env[1] = ft_strdup("SHLVL=1");
	if (!env[1])
		return (free_arr(env), NULL);
	env[2] = ft_strjoin("_=", buf);
	if (!env[2])
		return (free_arr(env), NULL);
	env[3] = NULL;

	return (env);
}
*/
void	reset_sh(t_sh *sh)
{
	set_signals(1);
	free_lstcmd(&(sh->cmd));
	sh->cmd = NULL;
	sh->fd_stdin = 0;
	sh->fd_stdout = 1;
	ft_memset(sh->end, -1, 4 * sizeof(int));
	free(sh->line);
}

int	init_sh(char **av, char **envp, t_sh *sh)
{
	(void)av;
	sh->line = NULL;
	sh->env = ft_arrdup(envp, ft_arrlen(envp));
	if (!sh->env)
		return (perror(MLC_ERR), 1);
	sh->cmd = NULL;
	sh->heredoc = NULL;
	sh->fd_stdin = 0;
	sh->fd_stdout = 1;
	sh->exit_s = 0;
	ft_memset(sh->end, -1, 4 * sizeof(int));
	set_signals(1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_sh	sh;

	if (ac != 1)
		return (ft_putstr_fd(NO_ARGS, 2), 127);
	if (init_sh(av, envp, &sh))
		return (1);
	g_exit_status = 0;
	while (1)
	{
		sh.line = readline("minishell$ ");
		if (g_exit_status > 0)
		{
			sh.exit_s = g_exit_status;
			g_exit_status = 0;
		}
		if (!sh.line)
			break ;
		if (*sh.line)
			add_history(sh.line);
		if (sh.line && *(sh.line))
			sh.exit_s = (unsigned char)read_line(&sh);
		reset_sh(&sh);
	}
	ft_putstr_fd("exit\n", 2);
	return (exit_fork(&sh, sh.exit_s, NULL), sh.exit_s);
}
