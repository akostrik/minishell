/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalimol <akalimol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:31:49 by akalimol          #+#    #+#             */
/*   Updated: 2023/07/08 19:32:59 by akalimol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
readline rl_clear_history, rl_on_new_line rl_replace_line rl_redisplay, add_history,
malloc free
printf write access open read close
fork wait waitpid wait3 wait4 
signal sigaction sigemptyset sigaddset kill
exit,
getcwd chdir stat lstat fstat unlink execve dup dup2 pipe
opendir readdir closedir
strerror perror
isatty ttyname ttyslot ioctl
getenv
tcsetattr tcgetattr tgetent tgetflag tgetnum tgetstr tgoto tputs

SIGQUIT = SIGINT, except that it’s controlled by C-\ 
and produces a core dump when it terminates the process, 
just like a program error signal. You can think of 
this as a program error condition “detected” by the user.

readline read a line from the terminal 
The line is allocated with malloc, the caller must free it.
Returns the line without \n, "" for "", NULL for "" + EOF
If an EOF is read with a non-empty line, it is treated as a newline.

/* linked list, where:
 * list->content	- full string (ex. "USER=akostrik")
 * list->type      - default or not */

#include "minishell.h"

int g_signal = 0;

void	init(char **env, t_data *data)
{
	t_list	*token;
	char	*str;
	int		i;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_handler_main);
	data->env = NULL;
	i = 0;
	while (env[i])
	{
		str = ft_strdup(env[i]);
		if (!str)
		{
			ft_lstclear(&data->env, &free);
			ft_error();
			return ;
		}
		token = ft_lstnew(str, 0);
		if (!token)
		{
			free(str);
			ft_lstclear(&token, &free);
			ft_error();
			return ;
		}
		ft_lstadd_back(&data->env, token);
		i++;
	}
	data->exit_code = 0;
}

int	parse(char *command, t_list *env, t_data *data)
{
	t_list	*head;
	char	*cmd_line;
	int		code;

	cmd_line = ft_add_spaces(command);
	if (!cmd_line)
		return (data->exit_code = 255, 255);
	head = ft_tokenization(cmd_line, env, data);
	free(cmd_line);
	if (!head)
		return (data->exit_code = 255, 255);
	ft_assign_types(head);
	if (ft_check_tokens(head) == 0)
		return (data->exit_code = 2, free_redirections(*(&head)), 2);
	code = ft_open_heredocs(head, env);
	if (code != 0)
		return (data->exit_code = code, free_redirections(*(&head)), code);
	data->node = NULL;
	data->node = ft_make_tree(head, NULL);
	if (data->node == NULL)
		return (data->exit_code = 255, free_redirections(*(&head)), 255);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*command;

	(void)argc;
	(void)argv;
	command = NULL;
	init(env, &data);
	while (1)
	{
		command = readline("$");
		if (command == NULL) // EOF
			break ;
		if (g_signal == 1)
		{
			g_signal = 0;
			data.exit_code = 130;
			continue;
		}
		add_history(command);
		data.exit_code = parse(command, data.env, &data);
		if (data.exit_code == 0)
			ft_execution(&data);
		ft_clean_tree(data.node);
	}
	free_redirections(*(&(data.env)));
	return (data.exit_code);
}
