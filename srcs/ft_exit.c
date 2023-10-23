/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:27:54 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 13:17:09 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define LLMAX	"9223372036854775807"
#define LLMIN	"9223372036854775808"
#define MANY_ARG	"minishell: exit: too many arguments\n"
#define NUM_ARG	": numeric argument required\n"

/*
maybe in need of ft_atoll because value at exit not always the same

exit takes to longlong max value then after that doesnt consider it a number
9,223,372,036,854,775,807 LLONG_MAX
Avec un 8 pour les négatifs LLONG_MIN
*/

static void	close_n_exit(t_sh *sh, t_cmd *lst, int n)
{
	dup_builtin_solo(sh, &lst, 0);
	if ((lst->fd_in != -1 && (close(lst->fd_in)
				|| (sh->fd_stdin != 0 && close(sh->fd_stdin))))
		|| (lst->fd_out != -1 && (close(lst->fd_out)
				|| (sh->fd_stdout != 1 && close(sh->fd_stdout)))))
		perror("minishell: close error");
	while (*sh->end)
	{
		if (*sh->end != -1 && close(*sh->end))
			perror("minishell: close error");
		(*sh->end)++;
	}
	if (n)
		exit_fork(sh, n, NULL);
	exit_fork(sh, sh->exit_s, NULL);
}

static int	len_dig(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	return (i);
}

static int	not_num_arg(char *str, char *after, int m)
{
	if ((((size_t)len_dig(str) != ft_strlen(str) || !ft_strlen(str))
			|| (ft_strlen(after) > 19 && m == 1)
			|| (ft_strlen(after) > 20 && m == -1)
			|| (ft_strlen(after) == 19 && strncmp(after, LLMAX, 19) > 0
				&& m == 1)
			|| (ft_strlen(after) == 19 && strncmp(after, LLMIN, 19) > 0
				&& m == -1)
			|| (ft_strlen(str) == 1 && (str[0] == '-' || str[0] == '+')))
		&& (write(2, "exit\n", 5) || 1))
		return (1);
	return (0);
}

int	ft_exit(t_sh *sh, t_cmd *lst, char **cmd, char ***envp)
{
	int		i;
	char	*tmp;
	int		m;

	if (ft_arrlen(cmd) == 1 && (write(2, "exit\n", 5) || 1))
		close_n_exit(sh, lst, sh->exit_s);
	i = 0;
	m = 1;
	if ((cmd[1][i] == '+' || cmd[1][i] == '-') && ++i)
		if (cmd[1][i - 1] == '-')
			m = -1;
	while (cmd[1][i] == '0' && cmd[1][i + 1])
		i++;
	if (not_num_arg(cmd[1], &cmd[1][i], m))
	{
		tmp = better_strjoin("minishell: exit: ", cmd[1], NUM_ARG);
		if (!tmp)
			return (perror(MLC_ERR), EXIT_CODE_MALLOC);
		ft_putstr_fd(tmp, 2);
		free(tmp);
		close_n_exit(sh, lst, 2);
	}
	if (ft_arrlen(cmd) == 2 && (write(2, "exit\n", 5) || 1))
		close_n_exit(sh, lst, ft_atoi(cmd[1]));
	return ((void)envp, write(2, "exit\n", 5), ft_putstr_fd(MANY_ARG, 2), 1);
}
