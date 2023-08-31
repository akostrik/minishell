#include "headers.h"

void	init_cmd(t_cmds **new, t_data **d)
{
	*new = (t_cmds *)malloc_(sizeof(t_cmds), d);
	(*new)->nb_max_args = INT_MAX;
	(*new)->args = NULL;
	(*new)->redir_in = NULL;
	(*new)->redir_out = NULL;
	(*new)->redir_out2 = NULL;
	(*new)->to_free = NULL;
	(*new)->fd_in = STDIN_FILENO;
	(*new)->fd_out = STDOUT_FILENO;
	(*new)->nxt = NULL;
	(*new)->prv = NULL;
}

int	mod_(char c)
{
	static char	mod = QUOTES0;

	if (c == REINIT_QUOTES)
		mod = QUOTES0;
	else if (mod == QUOTES0 && c == '\'')
		mod = QUOTES1;
	else if (mod == QUOTES0 && c == '\"')
		mod = QUOTES2;
	else if (mod == QUOTES1 && c == '\'')
		mod = QUOTES0;
	else if (mod == QUOTES2 && c == '\"')
		mod = QUOTES0;
	return (mod);
}

char	*redir_(char *s)
{
	if (s[0] == '>' && s[1] == '>')
		return (">>");
	else if (s[0] == '<' && s[1] == '<')
		return ("<<");
	else if (s[0] == '>')
		return (">");
	else if (s[0] == '<')
		return ("<");
	else
		return ("");
}

int	nb_args_(char *s0, int len)
{
	int		nb_args;
	int		i;
	char	*s;

	i = 0;
	mod_(REINIT_QUOTES);
	s = ft_strdup(s0);
	while (i < len) // erase redirections
	{
		if (mod_(s[i]) == QUOTES0 && ft_strlen(redir_(&s[i])) > 0)
		{
			s[i++] = ' ';
			if (s[i] == '>' || s[i] == '<')
				s[i++] = ' ';
			while(s[i] == ' ')
				i++;
			while(mod_(s[i]) == QUOTES0 && (s[i] != ' ' && s[i] != '>' && s[i] != '<' && s[i] != '\0'))
				s[i++] = ' ';
		}
		else
			i++;
	}
	mod_(REINIT_QUOTES);
	nb_args = 0;
	i = -1;
	while (++i < len)
		if (mod_(s[i]) == QUOTES0 && s[i] != ' ' && (s[i + 1] == ' ' || s[i + 1] == '\0' || s[i + 1] == '\'' || s[i + 1] == '\"' || i == len - 1))
				nb_args++;
	return (nb_args);
}

void print_cmds(char *msg, t_data **d)
{
	int		i;
	t_cmds	*cmd;

	printf("LIST %s %14p->%14p:\n", msg, (*d)->cmds, (*d)->cmds == NULL ? 0 : *((*d)->cmds));
	if ((*d)->cmds == NULL || *((*d)->cmds) == NULL)
	{
		printf("  empty\n");
		return ;
	}
	cmd = *((*d)->cmds);
	while (cmd != NULL)
	{
		printf("  %p [%s]\n%d args :\n", cmd, cmd->args[0], cmd->nb_args);
		if (cmd->args != NULL)
		{
			i = -1;
			while (++i < cmd->nb_args)
				printf("%s : ", cmd->args[i]);
		}
		printf("\n  redirs [%s %s %s]\n", cmd->redir_out, cmd->redir_out2, cmd->redir_in);
		if (cmd == NULL)
			break ; ////
		cmd = cmd->nxt;
	}
}

void del_cmd_from_list(t_cmds *cmd, t_data **d)
{
	int		i;
	t_cmds	*to_free;

	printf("del %s\n", cmd == NULL ? "NULL" : cmd->args[0]);
	if (cmd == NULL)
		return ;
	i = -1;
	while(++i < cmd->nb_args)
	{
		free(cmd->args[i]);
		cmd->args[i] = NULL;
	}
	free(cmd->args);
	cmd->args = NULL;
	printf("del %s\n", cmd == NULL ? "NULL" : cmd->args[0]);
	if (cmd->prv == NULL)
	{
		to_free = *((*d)->cmds);
		printf("del 1st elt %s\n", to_free->args[0]);
		*((*d)->cmds) = cmd->nxt;
	}
	else
	{
		to_free = cmd->prv->nxt;
		printf("del elt %s\n", to_free->args[0]);
		cmd->prv->nxt = cmd->nxt;
	}
	free(to_free); // & ?
	to_free = NULL;
}

// void	delete_cmds(t_data **d)
// {
// 	t_cmds	*cmd_to_del;
// 	t_cmds	*cur;

// 	cur = *((*d)->cmds);
// 	while(cur != NULL)
// 	{
// 		cmd_to_del = *((*d)->cmds);
// 		*((*d)->cmds) = (*((*d)->cmds))->nxt;
// 		printf("delete %s\n", cmd_to_del->args[0]);
// 		//delete_cmd_from_list(cmd_to_del, d);
// 		cur = cur->nxt;
// 	}
// }