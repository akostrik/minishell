/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 04:50:18 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 03:57:47 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_full_path(char *env, char **cmd)
{
	char	**pathes;
	char	**tmp;
	int		i;

	pathes = ft_split(env, ':');
	free(env);
	if (!pathes)
		return (NULL);
	tmp = malloc((ft_arrlen(pathes) + 1) * sizeof(char *));
	if (!tmp)
		return (free_arr(pathes), NULL);
	i = -1;
	while (pathes[++i])
	{
		tmp[i] = better_strjoin(pathes[i], "/", cmd[0]);
		if (!tmp[i])
			return (free_arr(tmp), free_arr(pathes), NULL);
	}
	tmp[i] = NULL;
	free_arr(pathes);
	return (tmp);
}

char	*check_access(char **pathes, char *cmd)
{
	char	*str;
	int		i;

	str = NULL;
	i = -1;
	while (pathes[++i])
	{
		if (!access(pathes[i], X_OK))
		{
			str = ft_strdup(pathes[i]);
			return (free_arr(pathes), str);
		}
		if (!access(pathes[i], F_OK))
		{
			free(str);
			str = ft_strdup(pathes[i]);
			if (!str)
				return (free_arr(pathes), NULL);
		}
	}
	if (!str)
		str = ft_strdup(cmd);
	free_arr(pathes);
	return (str);
}

char	*search_path(t_sh *sh, t_cmd *cmd)
{
	char	*env;
	char	**pathes;

	if (!cmd->cmd[0][0])
		return (ft_strdup(cmd->cmd[0]));
	env = find_env_var(sh->env, "PATH");
	if (!env)
		return (NULL);
	if (!*env)
		return (free(env), ft_strdup(cmd->cmd[0]));
	pathes = get_full_path(env, cmd->cmd);
	if (!pathes)
		return (NULL);
	if (ft_strchr(cmd->cmd[0], '/'))
		return (free_arr(pathes), ft_strdup(cmd->cmd[0]));
	return (check_access(pathes, cmd->cmd[0]));
}
