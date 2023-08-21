#include "minishell.h"

void	sig_handler_main(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 1;
	}
}

void	sig_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		close(STDIN_FILENO);
		g_signal = 1;
	}
}

void	sig_handler_fork(int signal)
{
	if (signal == SIGINT)
		exit(130);
	if (signal == SIGQUIT)
		exit(131);
}

void	free_redirections(t_list *head)
{
	t_list	*token;

	token = head;
	while (token)
	{
		if (token->type == HEREDOC && token->next && token->next->next)
			close(*((int *)token->content));
		token = token->next;
	}
	ft_lstclear(&head, &free);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		((unsigned char *)b)[i++] = c;
	return (b);
}

void	memset_(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = '\0';
}

void	ft_remove_quotes_string(char *str)
{
	char	mode;
	int		i;
	int		j;

	i = 0;
	j = 0;
	mode = '\0';
	while (str[i])
	{
		if (mode == '\0' && str[i] == '\'')
			mode = 's';
		else if (mode == 's' && str[i] == '\'')
			mode = '\0';
		else if (mode == '\0' && str[i] == '\"')
			mode = 'd';
		else if (mode == 'd' && str[i] == '\"')
			mode = '\0';
		else
			str[j++] = str[i];
		i++;
	}
	while (j != i)
		str[j++] = '\0';
}

void	ft_remove_quotes_list(t_list *head)
{
	t_list	*token;
	char	*str;

	token = head;
	while (token)
	{
		str = (char *)token->content;
		ft_remove_quotes_string(str);
		token = token->next;
	}
}

void	exit_(int exit_code, char *msg, char *msg_param, t_list **lst_to_clear, void (*func_to_clear_lst)(void*), char **str_to_free)
{
	if (msg == NULL)
		printf("%s\n", strerror(errno));
	else if (msg != NULL && msg_param == NULL)
		printf("bash: %s\n", msg);
	else if (msg != NULL && msg_param != NULL)
		printf(msg, msg_param);
	if (lst_to_clear != NULL)
	ft_lstclear(lst_to_clear, func_to_clear_lst);
	if (str_to_free != NULL)
		free(*str_to_free);
	if (exit_code != -1)
		exit(exit_code);
}
