/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseremet <aseremet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:16:08 by aseremet          #+#    #+#             */
/*   Updated: 2023/10/21 11:32:19 by aseremet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

# define NO_ARGS		"Error: minishell doesn't accept arguments\n"
# define PATHES			"/usr/local/sbin:/usr/local/bin:/usr/sbin:\
/usr/bin:/sbin:/bin"
# define UNCL_QUOTES	"minishell: syntax error: unclosed quotes\n"
# define PIP_SYN_ERR	"minishell: syntax error near unexpected token '|'\n"
# define TOK_SYN_ERR	"minishell: syntax error near unexpected token\n"
# define HD_ERR			"minishell: warning: here-document \
delimited by EOF (wanted '"
# define MLC_ERR		"minishell: malloc error"

# define EXIT_CODE_MALLOC 139
# define TRUE	1
# define FALSE	0

typedef enum e_redr_type
{
	IN = 1,
	H_DOC,
	OUT,
	OUT_A,
}	t_redr_type;

typedef struct s_redir
{
	char			*file;
	int				type;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*path;
	char			**cmd;
	int				pid;
	struct s_redir	*redir;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_sh
{
	char			*line;
	char			**env;
	t_cmd			*cmd;
	int				fd_stdin;
	int				fd_stdout;
	int				end[4];
	char			*heredoc;
	unsigned char	exit_s;
}	t_sh;

/* array_utils.c*/
char	**ft_arrdup(char **arr, int size);
int		ft_arrlen(char **arr);
void	free_arr(char **arr);

/* parser_utils.c */
int		not_valid_id(char c, char *str);
int		ft_isspace(char c);
int		skip_quotes(char *line, char type);
int		unclosed_quotes(char *line);
int		count_quotes(char *str);

/* parser_expand.c */
char	*empty_str(void);
char	*expand_var(t_sh *sh);
char	*find_env_var(char **envp, char *var);

/* parser_cmd.c */
int		read_line(t_sh *sh);

/* lst_utils.c */
int		lst_size(t_cmd *cmd);
void	free_lstcmd(t_cmd **cmd);
void	lstcmd_add_back(t_cmd **cmd, t_cmd *new);
void	lstredir_add_back(t_redir **redir, t_redir *new);

/* parser_cmd_add.c */
t_cmd	*init_cmd_lst(void);
char	**add_cmd(char *str, char ***og, int *ind);
int		add_redr(char *str, t_cmd **cmd, int *ind);

/* parser_cmd_utils.c */
int		in_quotes(char *str);
int		invalid_redir_token(char *str, size_t type);
int		ft_is_charset(char c, char *str);
int		get_str_size(char *str);
char	*unquote(char *str, int count);

/* signal.c */
void	set_signals(int mode);

/* executor.c */
int		executor(t_sh *sh);

/* manage_redir.c */
int		manage_redir(t_cmd **cmd);
int		dup_builtin_solo(t_sh *sh, t_cmd **cmd, int sof);

/* utils.c */
int		reset_hd(t_sh *sh);
int		redir_delone(t_cmd **cmd, t_redir *redir, t_sh *sh);
int		ft_error(char *err, char *var, char *end, int ret);
int		is_builtin(char *cmd);
char	*better_strjoin(char const *s1, char const *s2, char const *s3);

/* manage_builtins.c */
int		builtin_solo(t_sh *sh, t_cmd **cmd);
void	builtin_fork(t_sh *sh, t_cmd *cmd, int nb);

/* manage_fork.c */
void	ft_fork(t_sh *sh, t_cmd *cmd, int nb);

/* find_cmd_path.c */
char	*search_path(t_sh *sh, t_cmd *cmd);
int		close_fork(t_cmd *cmd, int end[4], int nb);
void	exit_fork(t_sh *sh, int ret, char *error);

/* heredoc.c */
int		launch_heredoc(t_sh *sh, t_cmd **cmd, int *ret);

/* builtins */
int		ft_echo(t_sh *sh, t_cmd *lst, char **cmd, char ***envp);
int		ft_exit(t_sh *sh, t_cmd *lst, char **cmd, char ***envp);
int		ft_env(t_sh *sh, t_cmd *lst, char **cmd, char ***envp);
int		ft_export(t_sh *sh, t_cmd *lst, char **cmd, char ***envp);
int		ft_unset(t_sh *sh, t_cmd *lst, char **cmd, char ***envp);
int		ft_cd(t_sh *sh, t_cmd *lst, char **cmd, char ***envp);
int		ft_pwd(t_sh *sh, t_cmd *lst, char **cmd, char ***envp);

/* builtins_utils.c */
char	*key_(char *key_and_val);
char	*ft_strcpy(char *src);
int		ft_strcmp(char *s1, char *s2);
int		ft_export_1_var(char *key_and_val0, char ***envp);
int		ft_unset_1_var(char *key, char ***envp);
int		update_pwd_and_oldpwd(char *abs_path, char ***envp);
void	remove_the_last_part(char *path);
int		remove_the_first_part(char **path);
void	free_(char **s);
int		key_is_valid(char *s);

void	remove_the_last_elt(char *path);
int		how_many_removed_from_pwd(char **pwd, char *path);

#endif
