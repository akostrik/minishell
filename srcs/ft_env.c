/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:42:00 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 13:17:04 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_sh *sh, t_cmd *lst, char **cmd, char ***envp)
{
	int		i;
	char	**tmp;

	(void)sh;
	(void)lst;
	if (ft_strlen(cmd[1]) == 1 && cmd[1][0] == '-')
		return (0);
	tmp = *envp;
	i = 0;
	while (tmp[i] != NULL)
	{
		if (!ft_strchr(tmp[i], '=') && ++i)
			continue ;
		if ((size_t)printf("%s\n", tmp[i]) != ft_strlen(tmp[i]) + 1)
			return (perror("minishell: env: printf"), 1);
		i++;
	}
	return (0);
}
