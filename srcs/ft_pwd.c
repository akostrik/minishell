/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:43:03 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 13:17:17 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_sh *sh, t_cmd *lst, char **cmd, char ***envp)
{
	char	*out;

	(void)cmd;
	(void)sh;
	(void)envp;
	(void)lst;
	out = getcwd(NULL, 0);
	if (out == NULL)
		return (perror("minishell: pwd: getcwd"), 1);
	if ((size_t)printf("%s\n", out) != ft_strlen(out) + 1)
		return (free(out), perror("minishell: pwd: write"), 1);
	free(out);
	return (0);
}
