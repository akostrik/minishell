/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:11:30 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 13:17:00 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option_n(char *s)
{
	if (s[0] != '-')
		return (FALSE);
	if (ft_strcmp(s, "-") == 0)
		return (FALSE);
	s++;
	while (*s != '\0')
	{
		if (*s != 'n')
			return (FALSE);
		s++;
	}
	return (TRUE);
}

static int	i_after_options_(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[++i] != NULL && is_option_n(cmd[i]))
		;
	return (i);
}

int	ft_echo(t_sh *sh, t_cmd *lst, char **cmd, char ***envp)
{
	int		i;
	int		i_after_options;

	(void)envp;
	(void)sh;
	(void)lst;
	i_after_options = i_after_options_(cmd);
	i = i_after_options - 1;
	while (cmd[++i] != NULL)
	{
		if ((size_t)printf("%s", cmd[i]) != ft_strlen(cmd[i]))
			return (perror("minishell: echo: printf"), 1);
		if (cmd[i + 1] != NULL && (size_t)printf(" ") != 1)
			return (perror("minishell: echo: printf"), 1);
	}
	if (i_after_options == 1)
		if ((size_t)printf("\n") != 1)
			return (perror("minishell: echo: printf"), 1);
	return (0);
}
