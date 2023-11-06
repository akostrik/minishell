/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:30:12 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 14:32:15 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// an error here : cd ../../../../../../../../../../../usr doesn't work

#include "minishell.h"

#define MSG_NOT_HOME "minishell: cd: HOME not set\n"
#define MSG_NOT_OLDPWD "minishell: cd: OLDPWD not set\n"

void	remove_k_from_path(char **path, int k)
{
	int		i;
	int		new_begin;
	int		nb_removed_elts;

	new_begin = 0;
	nb_removed_elts = 0;
	while (new_begin < (int)ft_strlen(*path) && nb_removed_elts < k && \
		ft_strncmp(&((*path)[new_begin]), "../", 3) == 0)
	{
		new_begin += 3;
		nb_removed_elts++;
	}
	if (ft_strncmp(&((*path)[new_begin]), "..", 2) == 0 && nb_removed_elts < k)
	{
		new_begin += 2;
		nb_removed_elts++;
	}
	i = -1;
	while (++i < (int)ft_strlen(*path) - new_begin + 1)
		(*path)[i] = (*path)[new_begin + i];
	while (++i < (int)ft_strlen(*path))
		(*path)[i] = '\0';
}

// path_ freed_ in the calling function
// pwd_ freed_ in the calling function
int	join_pwd_to_path(char *pwd, char **path)
{
	int		i;
	int		j;
	char	*abs_path;

	remove_k_from_path(path, how_many_removed_from_pwd(&pwd, *path));
	if (ft_strlen(pwd) == 0 && ft_strlen(*path) == 0)
		return (free(*path), *path = ft_strjoin("/", ""), 0);
	if (ft_strlen(pwd) == 0 && ft_strncmp(*path, "..", 2) == 0)
		return (free(*path), *path = ft_strjoin("/", ""), 0);
	abs_path = (char *)malloc(ft_strlen(pwd) + ft_strlen(*path) + 2);
	if (abs_path == NULL)
		return (perror(MLC_ERR), EXIT_CODE_MALLOC);
	ft_memset(abs_path, '\0', ft_strlen(pwd) + ft_strlen(*path) + 2);
	i = -1;
	while (++i < (int)ft_strlen(pwd))
		abs_path[i] = pwd[i];
	if (ft_strlen(*path) > 0)
	{
		abs_path[i++] = '/';
		j = 0;
		while ((size_t)j < ft_strlen(*path))
			abs_path[i++] = (*path)[j++];
	}
	return (free(*path), *path = ft_strjoin(abs_path, ""), free(abs_path), 0);
}

// called only if cmd1 != NULL
// path_ freed_ in the calling function
int	put_abs_path_to_var_path(char *cmd1, char **path)
{
	char	*pwd;
	char	*path2;
	int		exit_code;

	*path = ft_strjoin(cmd1, "");
	if (*path == NULL)
		return (perror(MLC_ERR), EXIT_CODE_MALLOC);
	if ((*path)[0] == '/')
		return (0);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (perror("minishell: cd: getcwd"), 1);
	if (ft_strncmp(*path, "./", 2) == 0)
	{
		path2 = ft_strjoin(&((*path)[2]), "");
		free_(path);
		if (path2 == NULL)
			return (perror(MLC_ERR), free(pwd), EXIT_CODE_MALLOC);
		*path = path2;
	}
	exit_code = join_pwd_to_path(pwd, path);
	if (exit_code != 0)
		return (free(pwd), exit_code);
	return (free(pwd), 0);
}

// path_ freed_ in the calling function
int	put_path_to_var_path(char *cmd1, char **envp, char **path)
{
	int	exit_code;

	if (cmd1 == NULL || ft_strcmp(cmd1, "--") == 0 || ft_strcmp(cmd1, "~") == 0)
	{
		*path = find_env_var(envp, "HOME");
		if (*path == NULL)
			return (perror(MLC_ERR), EXIT_CODE_MALLOC);
		if (ft_strlen(*path) == 0)
			return (ft_putstr_fd(MSG_NOT_HOME, 2), 1);
		return (0);
	}
	if (ft_strcmp(cmd1, "-") == 0)
	{
		*path = find_env_var(envp, "OLDPWD");
		if (*path == NULL)
			return (perror(MLC_ERR), EXIT_CODE_MALLOC);
		if (ft_strlen(*path) == 0)
			return (ft_putstr_fd(MSG_NOT_OLDPWD, 2), 1);
		return (0);
	}
	exit_code = put_abs_path_to_var_path(cmd1, path);
	if (exit_code != 0)
		return (exit_code);
	return (0);
}

// cmd1 freed_ in the calling funciton
// path_ freed_ in the calling function
// static int	opendir_2(char *cmd1, char **path)
// {
// 	char	*out;
// 	DIR		*dir;

// 	out = NULL;
// 	dir = opendir(*path);
// 	if (dir == NULL)
// 	{
// 		fprintf(stderr, "test\n");
// 		out = ft_strjoin("minishell: cd: ", cmd1);
// 		if (out == NULL)
// 			return (perror(MLC_ERR), EXIT_CODE_MALLOC);
// 		return (perror(out), free(out), 1);
// 	}
// 	fprintf(stderr, "test7867\n");
// 	closedir(dir);
// 	return (0);
// }

	// exit_code = opendir_2(cmd[1], &path);
	// if (exit_code != 0)
	// 	return (free_(&path), exit_code);

int	ft_cd(t_sh *sh, t_cmd *lst, char **cmd, char ***envp)
{
	char	*path;
	int		exit_code;

	if (cmd[1] != NULL && cmd[2] != NULL)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (ft_strcmp(cmd[1], ".") == 0 || ft_strcmp(cmd[1], "./") == 0)
		return (0);
	path = NULL;
	exit_code = put_path_to_var_path(cmd[1], *envp, &path);
	if (exit_code != 0)
		return (free_(&path), exit_code);
	if (chdir(path) == -1)
		return (perror("minishell: cd: chdir"), free_(&path), 1);
	if (ft_strcmp(cmd[1], "-") == 0)
		if ((size_t)printf("%s\n", path) != ft_strlen(path) + 1)
			return (perror("minishell: env: printf"), 1);
	exit_code = update_pwd_and_oldpwd(path, envp);
	if (exit_code != 0)
		return (free_(&path), exit_code);
	return (free_(&path), (void)sh, (void)lst, 0);
}
