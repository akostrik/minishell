/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:14:28 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 16:18:48 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// for tests:
// printf("%s\n", find_env_var(*envp, key_(cmd[i]))); // tmp

#include "minishell.h"

#define MSG_NOT_ID	"': not a valid identifier\n"

void	bubble_sort(char **arr)
{
	int		len;
	int		i;
	int		j;
	char	*tmp;

	len = -1;
	while (arr[++len] != NULL)
		;
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len)
		{
			if (ft_strcmp(arr[i], arr[j]) < 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

static int	printf_env_style_export(char **envp)
{
	int		p;
	int		i;
	char	*tmp;
	char	**bub;

	bub = ft_arrdup(envp, ft_arrlen(envp));
	bubble_sort(bub);
	i = -1;
	while (bub[++i] != NULL)
	{
		// an error here : we should provide the case where there is no '=' in the varibale 
		p = ft_strchr(bub[i], '=') - bub[i];
		tmp = ft_substr(bub[i], 0, p);
		if ((size_t)printf("export -x %s=\"%s\"\n", tmp,
				&bub[i][p + 1]) != ft_strlen(bub[i]) + 13)
			return (free_arr(bub), free(tmp),
				perror("minishell: export: write"), 1);
		free(tmp);
	}
	free_arr(bub);
	return (0);
}

static int	add_variable_to_env(char *key_and_val, char ***envp)
{
	char	**new_envp;
	int		new_len;

	new_len = ft_arrlen(*envp) + 1;
	new_envp = ft_arrdup(*envp, new_len);
	if (new_envp == NULL)
		return (free(key_and_val), perror(MLC_ERR), EXIT_CODE_MALLOC);
	new_envp[new_len - 1] = ft_strdup(key_and_val);
	if (new_envp[new_len - 1] == NULL)
		return (free_arr(new_envp), free(key_and_val),
			perror(MLC_ERR), EXIT_CODE_MALLOC);
	new_envp[new_len] = NULL;
	free(key_and_val);
	free_arr(*envp);
	*envp = new_envp;
	return (0);
}

int	ft_export_1_var(char *key_and_val0, char ***envp)
{
	char	*key_and_val;
	char	*key;
	int		exit_code;

	if (key_is_valid(key_and_val0) == FALSE)
		return (ft_error("minshell: export: '", key_and_val0, MSG_NOT_ID, 1));
	key_and_val = ft_strdup(key_and_val0);
	if (key_and_val == NULL)
		return (perror(MLC_ERR), EXIT_CODE_MALLOC);
	key = key_(key_and_val);
	if (!key)
		return (free(key_and_val), perror(MLC_ERR), EXIT_CODE_MALLOC);
	exit_code = ft_unset_1_var(key, envp);
	free(key);
	if (exit_code != 0)
		return (free(key_and_val), exit_code);
	exit_code = add_variable_to_env(key_and_val, envp);
	if (exit_code != 0)
		return (exit_code);
	return (0);
}

int	ft_export(t_sh *sh, t_cmd *lst, char **cmd, char ***envp)
{
	int		exit_code;
	int		exit_code_func;
	int		i;

	(void)sh;
	(void)lst;
	if (cmd[1] == NULL || (cmd[1] && ft_strcmp(cmd[1], "--") == 0
			&& cmd[2] == NULL))
	{
		exit_code = printf_env_style_export(*envp);
		if (exit_code != 0)
			return (exit_code);
		return (0);
	}
	i = 0;
	exit_code = 0;
	if (cmd[1] && ft_strcmp(cmd[1], "--") == 0)
		i++;
	while (cmd[++i] != NULL)
	{
		exit_code_func = ft_export_1_var(cmd[i], envp);
		if (exit_code_func != 0)
			exit_code = exit_code_func;
	}
	return (exit_code);
}
