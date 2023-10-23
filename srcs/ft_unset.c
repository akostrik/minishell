/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:19:37 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 13:17:21 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**remove_var_number_k_from_env(int k, char ***envp)
{
	int		i;
	int		j;
	int		len;
	char	**new;

	len = ft_arrlen(*envp);
	new = malloc(len * sizeof(char *));
	if (!new)
		return (free_arr(*envp), NULL);
	i = -1;
	j = 0;
	while ((*envp)[++i] && j < len)
	{
		if (i == k)
			i++;
		if (!(*envp)[i])
			break ;
		new[j] = ft_strdup((*envp)[i]);
		if (!new[j])
			return (free_arr(new), free_arr(*envp), NULL);
		j++;
	}
	new[j] = NULL;
	free_arr(*envp);
	return (new);
}

int	ft_unset_1_var(char *key, char ***envp)
{
	char	*key_env;
	int		i;

	if (key == NULL || *envp == NULL)
		return (0);
	i = -1;
	while (*envp != NULL && (*envp)[++i] != NULL)
	{
		key_env = key_((*envp)[i]);
		if (key_env == NULL)
			return (perror(MLC_ERR), EXIT_CODE_MALLOC);
		if (ft_strcmp(key, key_env) == 0)
		{
			*envp = remove_var_number_k_from_env(i, envp);
			if (!*envp)
				return (free(key_env), perror(MLC_ERR),
					EXIT_CODE_MALLOC);
			return (free(key_env), 0);
		}
		free(key_env);
	}
	return (0);
}

int	ft_unset(t_sh *sh, t_cmd *lst, char **cmd, char ***envp)
{
	char	*key;
	int		exit_code;
	int		i;

	(void)envp;
	(void)lst;
	i = 0;
	while (cmd[++i] != NULL)
	{
		key = key_(cmd[i]);
		if (key == NULL)
			return (perror(MLC_ERR), EXIT_CODE_MALLOC);
		exit_code = ft_unset_1_var(key, &sh->env);
		if (exit_code != 0)
			return (free(key), exit_code);
		free(key);
	}
	return (0);
}
