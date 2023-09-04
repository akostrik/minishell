/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akostrik <akostrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:22:31 by akostrik          #+#    #+#             */
/*   Updated: 2023/09/04 02:15:55 by akostrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/signal.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>
# include "libft.h"

# define REINIT_QUOTES -1
# define QUOTES0 0
# define QUOTES1 1
# define QUOTES2 2
# define TMP_FILE "tmp"

extern int g_signal;

typedef struct		s_env
{
	char			*var;
	struct s_env	*nxt;
}					t_env;

// *cmd = currectly traited cmd
typedef struct		s_data
{
	t_env			**env;
	int				nb_args;
	char			**arg;
	int				nb_ins;
	int				*in;
	int				nb_outs;
	int				*out;
	int				saved_stdin;
	int				saved_stdout;
	int				exit_c;
}					t_data;

void		calc_dollar_conversions(char *s, t_data **d);
int		parse(char *s, int len, t_data **d);
void	exec(t_data **d);

// builtins                     min args    max   accept <in
int		exec_echo(t_data **d);   // 0           ...   no ?
int		exec_cd(t_data **d);     // 0           1     no ?
int		exec_pwd(t_data **d);    // 0           0     no
int		exec_export(t_data **d); // 0           ...   no ?
int		exec_unset(t_data **d);  // 1           ...   no ?
int		exec_env(t_data **d);    // 0           0     no
int		exec_exit(t_data **d);   // 0           1     no ?

// utils
void	*malloc_(int size, t_data **d);
void	sig_handler_main(int signal);
void	sig_handler_fork(int signal);
void	sig_handler_heredoc(int signal);
void	free_array(char **arr, int len);
void	free_all_and_exit(char *msg, int exit_c, t_data **d); /// ***d ?

// utils parse
void calc_nb_args_nb_ins_nb_outs(char *s, int len, t_data **d);

// utils exec
int		is_builtin(t_data **d);
char	*path_(t_data **d);

// utils env
char	*key_(char *s, t_data **d);
char 	*val_(char *s, t_data **d);
char	**env_to_array(t_data **d);
int		len_env_(t_data **d);
char	*get_value_from_env(char *key, t_data **d);

// utils str
char	*alphanum_(char *s, t_data **d);
char	*strdup_(char *s, t_data **d);
char	*strdup_and_erase_redirs(char *s0, t_data **d);
char	*strdup_and_erase_args_except_redirs(char *s0, t_data **d);
char	*strndup_and_trim(char *srs, int len, t_data **d);
int		strcmp_(char *s1, char *s2);
int		mod_(char c);
int		unclosed_quotes(char *s);

#endif