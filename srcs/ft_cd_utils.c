/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 11:01:53 by akostrik          #+#    #+#             */
/*   Updated: 2023/10/21 11:04:34 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_the_last_elt(char *path)
{
	int	i;

	if (ft_strcmp(path, "/") == 0)
		return ;
	i = ft_strlen(path) - 1;
	if (path[i] == '/')
		path[i] = '\0';
	while (--i >= 0 && path[i] != '/')
		path[i] = '\0';
	if (path[i] == '/')
		path[i] = '\0';
}

static int	how_many_can_remove_from_path_(char *path)
{
	char	*tmp;
	int		how_many;

	how_many = 0;
	tmp = path;
	while (ft_strncmp(tmp, "../", 3) == 0)
	{
		how_many++;
		tmp = &tmp[3];
	}
	if (ft_strcmp(tmp, "..") == 0)
		how_many++;
	return (how_many);
}

int	how_many_removed_from_pwd(char **pwd, char *path)
{
	int	i;
	int	how_many_can_remove_from_path;

	how_many_can_remove_from_path = how_many_can_remove_from_path_(path);
	i = -1;
	while (++i < how_many_can_remove_from_path && ft_strcmp(*pwd, "") > 0)
		remove_the_last_elt(*pwd);
	return (i);
}
