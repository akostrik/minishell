/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:07:28 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 12:08:43 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// env[0] == NULL

#include "minishell.h"

#define MSG_NOT_ID	"': not a valid identifier\n"

char	*key_(char *key_and_val)
{
	int	len_key;

	len_key = ft_strlen(key_and_val) - ft_strlen(ft_strchr(key_and_val, '='));
	return (ft_substr(key_and_val, 0, len_key));
}

// char	*ft_strcpy(char *src)
// {
// 	char	*dest;

// 	dest = (char *)malloc(ft_strlen(src) + 1);
// 	if (!dest)
// 		return (NULL);
// 	ft_strlcpy(dest, src, ft_strlen(src) + 1);
// 	return (dest);
// }

int	ft_strcmp(char *s1, char *s2)
{
	int	len;
	int	len1;
	int	len2;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL || s2 == NULL)
		return (1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1;
	if (len > len2)
		len = len2;
	if (ft_strncmp(s1, s2, len) == 0)
	{
		if (len1 > len2)
			return (1);
		else if (len1 < len2)
			return (-1);
	}
	return (ft_strncmp(s1, s2, len));
}

int	key_is_valid(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (i != 0 && s[i] == '=')
			break ;
		if (not_valid_id(s[i], s))
			return (FALSE);
	}
	return (TRUE);
}

// abs_path freed in the calling function
int	update_pwd_and_oldpwd(char *abs_path, char ***envp)
{
	char	*val;
	char	*key_and_val;
	int		exit_code;

	val = find_env_var(*envp, "PWD");
	if (val == NULL)
		return (perror(MLC_ERR), EXIT_CODE_MALLOC);
	key_and_val = ft_strjoin("OLDPWD=", val);
	free(val);
	if (key_and_val == NULL)
		return (perror(MLC_ERR), EXIT_CODE_MALLOC);
	exit_code = ft_export_1_var(key_and_val, envp);
	free(key_and_val);
	key_and_val = NULL;
	if (exit_code != 0)
		return (exit_code);
	key_and_val = ft_strjoin("PWD=", abs_path);
	if (key_and_val == NULL)
		return (perror(MLC_ERR), EXIT_CODE_MALLOC);
	exit_code = ft_export_1_var(key_and_val, envp);
	free(key_and_val);
	key_and_val = NULL;
	if (exit_code != 0)
		return (exit_code);
	return (0);
}

void	free_(char **s)
{
	if (s != NULL && *s != NULL)
		free(*s);
}
