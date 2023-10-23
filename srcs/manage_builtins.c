/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 07:28:30 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 11:31:54 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_option(char **cmd)
{
	char	*out;
	char	*out2;

	if (cmd[1] == NULL)
		return (0);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (0);
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (0);
	if (cmd[1][0] != '-')
		return (0);
	if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		return (0);
	if (cmd[1][0] == '-' && cmd[1][1] == '-' && cmd[1][2] == '\0')
		return (0);
	out2 = better_strjoin(": ", cmd[1], ": invalid option\n");
	if (out2 == NULL)
		return (perror(MLC_ERR), EXIT_CODE_MALLOC);
	out = better_strjoin("minishell: ", cmd[0], out2);
	if (out == NULL)
		return (free(out2), perror(MLC_ERR), EXIT_CODE_MALLOC);
	return (free(out2), ft_putstr_fd(out, 2), free(out), 2);
}

// int	(*launch_builtin(t_sh *sh))
//(t_sh *sh, t_cmd *lst, char **cmd, char ***env)
// {
// 	const void	*builtins[7][2] = {
// 	{"echo", ft_echo},
// 	{"cd", ft_cd},
// 	{"pwd", ft_pwd},
// 	{"export", ft_export},
// 	{"unset", ft_unset},
// 	{"env", ft_env},
// 	{"exit", ft_exit}};
// 	int			i;

// 	i = 0;

// 	while (i < 7)
// 	{
// 		if (!ft_strncmp(builtins[i][0], sh->cmd->cmd[0],
// 			ft_strlen((builtins[i][0]))))
// 			return (builtins[i][1]);
// 		i++;
// 	}
// 	return (NULL);
// }

int	launch_builtin(t_sh *sh, t_cmd *lst, char **cmd, char ***env)
{
	if (!ft_strncmp(cmd[0], "pwd", 4))
		return (ft_pwd(sh, lst, cmd, env));
	if (!ft_strncmp(cmd[0], "echo", 5))
		return (ft_echo(sh, lst, cmd, env));
	if (!ft_strncmp(cmd[0], "cd", 3))
		return (ft_cd(sh, lst, cmd, env));
	if (!ft_strncmp(cmd[0], "env", 4))
		return (ft_env(sh, lst, cmd, env));
	if (!ft_strncmp(cmd[0], "unset", 6))
		return (ft_unset(sh, lst, cmd, env));
	if (!ft_strncmp(cmd[0], "export", 7))
		return (ft_export(sh, lst, cmd, env));
	if (!ft_strncmp(cmd[0], "exit", 5))
		return (ft_exit(sh, lst, cmd, env));
	return (-1);
}

int	builtin_solo(t_sh *sh, t_cmd **cmd)
{
	int	ret;

	ret = 0;
	if (sh->cmd->redir)
		ret = manage_redir(cmd);
	if (!ret)
		ret = dup_builtin_solo(sh, cmd, 1);
	if (!ret)
		ret = invalid_option((*cmd)->cmd);
	if (!ret)
		ret = launch_builtin(sh, *cmd, (*cmd)->cmd, &(sh->env));
	if (dup_builtin_solo(sh, cmd, 0))
		ret = 1;
	if (((*cmd)->fd_in != -1 && (close((*cmd)->fd_in)
				|| (sh->fd_stdin != 0 && close(sh->fd_stdin))))
		|| ((*cmd)->fd_out != -1 && (close((*cmd)->fd_out)
				|| (sh->fd_stdout != 1 && close(sh->fd_stdout)))))
		return (perror("minishell: close error"), 1);
	if (reset_hd(sh))
		return (1);
	return (ret);
}

void	builtin_fork(t_sh *sh, t_cmd *cmd, int nb)
{
	int	ret;

	ret = launch_builtin(sh, cmd, cmd->cmd, &(sh->env));
	close_fork(sh->cmd, sh->end, nb);
	exit_fork(sh, ret, NULL);
}
