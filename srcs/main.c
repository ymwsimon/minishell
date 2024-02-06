/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:21:42 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/06 20:41:57 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_import_history(void)
{
	int		fd;
	char	*line;
	char	*trimmed_line;
	char	*path;

	path = ft_strjoin(getenv("HOME"), "/.minishell_cmd_history");
	fd = open(path, O_RDONLY);
	//printf("path of the history file=%s, fd=%d\n", path, fd);
	if (fd >= 0)
	{
		line = get_next_line(fd);
		trimmed_line = ft_strtrim(line, "\n");
		while (line)
		{
			add_history(trimmed_line);
			free(line);
			free(trimmed_line);
			line = get_next_line(fd);
			trimmed_line = ft_strtrim(line, "\n");
		}
		free(line);
		free(trimmed_line);
		close(fd);
	}
	free(path);
}

void	ft_trim_write_history(char **line)
{
	int		fd;
	char	*path;
	char	*line_with_newline;
	char	*trimmed;

	trimmed = ft_strtrim(*line, " ");
	free(*line);
	*line = trimmed;
	if (*line && !ft_strlen(*line))
		return ;
	path = ft_strjoin(getenv("HOME"), "/.minishell_cmd_history");
	add_history(*line);
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	//printf("path of the history file=%s, fd=%d\n", path, fd);
	if (fd >= 0)
	{
		line_with_newline = ft_strjoin(*line, "\n");
		write(fd, line_with_newline, ft_strlen(line_with_newline));
		free(line_with_newline);
		close(fd);
	}
	free(path);
}

void	ft_close_all_pipe(int *fds, size_t n)
{
	size_t	i;

	i = 0;
	while (i < (n - 1) * 2)
		close(fds[i++]);
}

int	*ft_init_pipe(size_t npipe)
{
	int		*res;
	size_t	i;

	res = malloc(sizeof(int) * npipe * 2);
	if (!res)
		return (NULL);
	i = 0;
	while (i < npipe)
	{
		if (pipe(&res[i * 2]) == -1)
			return (ft_close_all_pipe(res, i), free(res), NULL);
		i++;
	}
	return (res);
}

size_t	ft_char_arr_size(char **arr)
{
	size_t	res;

	res = 0;
	while (arr && arr[res])
		res++;
	return (res);
}

void	*ft_clear_char_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}
//don't need
t_cmd	*ft_parse_single_cmd(char *cmd, int *fds, size_t idx, size_t size)
{
	t_cmd	*res;

	res = malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	res->args = ft_split(cmd, ' ');
	if (!(res->args))
		return (free(res), NULL);
	res->cmd = res->args[0];
	if (!idx)
	{
		res->in_redir = NO_REDIRECT;
		res->infd = STDIN_FILENO;
	}
	else
	{
		res->in_redir = FROM_PIPE;
		res->infd = fds[idx * 2 - 2];
	}
	if (idx == (size - 1))
	{
		res->out_redir = NO_REDIRECT;
		res->outfd = STDOUT_FILENO;
	}
	else
	{
		res->out_redir = TO_PIPE;
		res->outfd = fds[idx * 2 + 1];
	}
	res->fds = fds;
	return (res);
}
//don't need
t_list	*ft_split_parse_cmds(char *line, char **env)
{
	char		**cmds;
	int			*fds;
	t_list		*res;
	t_cmd		*cmd_data;
	size_t		i;

	res = NULL;
	cmds = ft_split(line, '|');
	if (!cmds)
		return (NULL);
	//printf("total cmds:%ld\n", ft_char_arr_size(cmds));
	i = 0;
	fds = ft_init_pipe(ft_char_arr_size(cmds));
	if (!fds)
		return (ft_clear_char_arr(cmds), NULL);
	while (cmds[i])
	{
		//printf("raw cmd: %s\n", cmds[i]);
		cmd_data = ft_parse_single_cmd(cmds[i], fds, i, ft_char_arr_size(cmds));
		if (!cmd_data)
			return (ft_close_all_pipe(fds, ft_char_arr_size(cmds))
				, free(fds), ft_clear_char_arr(cmds), NULL);
		cmd_data->env = env;
		ft_lstadd_back(&res, ft_lstnew(cmd_data));
		i++;
	}
	return (res);
}
//????
void	ft_print_cmd_arg(char **args)
{
	printf("args: ");
	while (args && *args)
	{
		printf("%s ", *args);
		args++;
	}
}
//???
void	ft_print_cmds(t_list *cmds)
{
	t_cmd	*cmd;

	while (cmds)
	{
		cmd = cmds->content;
		printf("cmd: %s ", cmd->cmd);
		ft_print_cmd_arg(cmd->args);
		printf("in redir: %d, infd: %d, out redir: %d, outfd: %d\n", cmd->in_redir, cmd->infd, cmd->out_redir, cmd->outfd);
		cmds = cmds->next;
	}
}
//???
void	ft_redir_fds(int rfd, int wfd)
{
	dup2(rfd, STDIN_FILENO);
	dup2(wfd, STDOUT_FILENO);
}

char	*ft_getfullpath(char *pname, char *res)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	if (pname && ((pname[0] == '/') || pname[0] == '.'))
		return (ft_strdup(pname));
	path = getenv("PATH");
	/*if (path)
		printf("PATH=%s\n", path);
	else
		printf("PATH is empty\n");*/
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	pname = ft_strjoin("/", pname);
	if (!pname)
		return (ft_clear_char_arr(paths), NULL);
	i = 0;
	while (paths[i])
	{
		res = ft_strjoin(paths[i], pname);
		//printf("fullpath:%s\n", res);
		if (!access(res, F_OK | X_OK))
			return (ft_clear_char_arr(paths), free(pname), res);
		free(res);
		i++;
	}
	return (ft_clear_char_arr(paths), free(pname), NULL);
}

void	ft_errmsgname(int error_type, char *fname)
{
	if (error_type == CMD_NOT_FOUND)
		ft_putstr_fd("Command not found", STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(fname, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (error_type == CMD_NOT_FOUND)
		exit(CMD_NOT_FOUND);
	exit(1);
}
//don't need -- for ref
void	ft_exec_cmds(t_list *cmds)
{
	pid_t	cpid;
	t_cmd	*cmd;
	t_list	*node;
	char	*full_path;
	int		r;
	//int		fd;
	//size_t	i;

	//i = 0;
	node = cmds;
	while (node)
	{
		cpid = fork();
		cmd = node->content;
		if (!cpid)
		{	
			/*if (!node->next && 0)
			{
				fd = open("testout", O_WRONLY | O_CREAT | O_TRUNC, 0777);
				cmd->outfd = fd;
			}*/
			ft_redir_fds(cmd->infd, cmd->outfd);
			/*if (!node->next && 0)
				close(fd);*/
			ft_close_all_pipe(cmd->fds, ft_lstsize(cmds));
			full_path = ft_getfullpath(cmd->cmd, NULL);
			//ft_putstr_fd(full_path, STDERR_FILENO);
			if (!full_path)
				ft_errmsgname(CMD_NOT_FOUND, cmd->cmd);
			execve(full_path, cmd->args, cmd->env);
		}
		node = node->next;
	}
	ft_close_all_pipe(cmd->fds, ft_lstsize(cmds));
	waitpid(cpid, &r, 0);
}

int	ft_push_token_to_list(t_list **list, char *str)
{
	t_token	*tok;
	t_list	*new_node;

	if (!str)
		return (0);
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (free(str), 0);
	tok->str = str;
	tok->tok = RAW;
	new_node = ft_lstnew(tok);
	if (!new_node)
		return (free(tok), free(str), 0);
	ft_lstadd_back(list, new_node);
	return (1);
}

int	ft_is_double_quote(char *str)
{
	return (!ft_strncmp(str, "\"", ft_strlen("\"") + 1));
}

int ft_is_double_quote_tok(t_token_type t)
{
	return (t == OPEN_DOUBLE_QUOTE);
}

int	ft_is_single_quote(char *str)
{
	return (!ft_strncmp(str, "'", ft_strlen("'") + 1));
}

int	ft_is_single_quote_tok(t_token_type t)
{
	return (t == OPEN_SINGLE_QUOTE);
}

int	ft_is_open_paren(char *str)
{
	return (!ft_strncmp(str, "(", ft_strlen("(") + 1));
}

int	ft_is_open_paren_tok(t_token_type t)
{
	return (t == OPEN_PAREN);
}

int	ft_is_close_paren(char *str)
{
	return (!ft_strncmp(str, ")", ft_strlen(")") + 1));
}

int	ft_is_close_paren_tok(t_token_type t)
{
	return (t == CLOSE_PAREN);
}

void	ft_print_enum(t_token_type tok)
{
	if (tok == RAW)
		printf("RAW");
	else if (tok == PIPE)
		printf("PIPE_|");
	else if (tok == HERE_DOC)
		printf("HERE_DOC_<<");
	else if (tok == INPUT)
		printf("INPUT_<");
	else if (tok == OUTPUT)
		printf("OUTPUT_>");
	else if (tok == APPEND)
		printf("APPEND_>>");
	else if (tok == ARG)
		printf("JUST_ARG");
	else if (tok == INFILE)
		printf("INFILE");
	else if (tok == OUTFILE)
		printf("OUTFILE");
	else if (tok == DELIMITER)
		printf("DELIMITER");
	else if (tok == OPEN_DOUBLE_QUOTE)
		printf("OPEN_DOUBLE_QUOTE");
	else if (tok == OPEN_SINGLE_QUOTE)
		printf("OPEN_SINGLE_QUOTE");
}

t_list	*ft_tokenize(char *line)
{
	t_list	*res;
	t_list	*stack;
	t_list	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	res = NULL;
	stack = NULL;
	while (line && line[i])
	{
		ft_lstadd_front(&stack, ft_lstnew(ft_strdup(" |<>\"'")));
		while (line[i] && line[i] == ' ')
			i++;
		j = i;
		while (stack && line[j])
		{
			while (line[j] && !ft_strrchr(stack->content, line[j]))
				j++;
			if ((ft_strlen(stack->content) == 1 && ((char *)stack->content)[0] == line[j])
				|| (line[j] != '"' && line[j] != '\'' && line[j]))
			{
				tmp = stack->next;
				ft_lstdelone(stack, &free);
				stack = tmp;
				if (i == j && (line[j] == '<' || line[j] == '>')
					&& line[j] == line[j + 1])
					j += 2;
				if (line[j] == '"' || line[j] == '\'')
					j++;
			}
			else if (line[j])
				ft_lstadd_front(&stack, ft_lstnew(ft_substr(line, j++, 1)));
		}
		j += j == i;
		if (!ft_push_token_to_list(&res, ft_substr(line, i, j - i)))
			free(NULL);//clean up res
		i = j;
	}

	if (stack && ft_strlen(stack->content) == 1
		&& ft_is_double_quote(stack->content))
		((t_token *)ft_lstlast(res)->content)->tok = OPEN_DOUBLE_QUOTE;
	if (stack && ft_strlen(stack->content) == 1
		&& ft_is_single_quote(stack->content))
		((t_token *)ft_lstlast(res)->content)->tok = OPEN_SINGLE_QUOTE;
	//printf("stack content%s\n", (char *)stack->content);
	//ft_print_enum(((t_token *)ft_lstlast(res)->content)->tok);
	//printf("\n");
	return (res);
}

void	ft_print_tokens(t_list *tokens)
{
	t_token	*t;

	printf("tokens:\n");
	while (tokens)
	{
		t = tokens->content;
		printf("data:%s tok_type:", t->str);
		ft_print_enum(t->tok);
		printf("\n");
		tokens = tokens->next;
	}
}

int	ft_is_pipe(char *str)
{
	return (!ft_strncmp(str, "|", ft_strlen("|") + 1));
}
//???
int	ft_is_pipe_tok(t_token_type t)
{
	return (t == PIPE);
}

int	ft_is_here_doc(char *str)
{
	return (!ft_strncmp(str, "<<", ft_strlen("<<") + 1));
}
//???
int	ft_is_here_doc_tok(t_token_type t)
{
	return (t == HERE_DOC);
}

int	ft_is_input(char *str)
{
	return (!ft_strncmp(str, "<", ft_strlen("<") + 1));
}
//???
int	ft_is_input_tok(t_token_type t)
{
	return (t == INPUT);
}

int	ft_is_output(char *str)
{
	return (!ft_strncmp(str, ">", ft_strlen(">") + 1));
}
//???
int	ft_is_output_tok(t_token_type t)
{
	return (t == OUTPUT);
}

int	ft_is_append(char *str)
{
	return (!ft_strncmp(str, ">>", ft_strlen(">>") + 1));
}
//???
int	ft_is_append_tok(t_token_type t)
{
	return (t == APPEND);
}

int	ft_is_redir(char *str)
{
	return (ft_is_here_doc(str)
			|| ft_is_input(str)
			|| ft_is_output(str)
			|| ft_is_append(str));
}

int	ft_is_redir_tok(t_token_type t)
{
	return (ft_is_here_doc_tok(t)
			|| ft_is_input_tok(t)
			|| ft_is_output_tok(t)
			|| ft_is_append_tok(t));
}

int	ft_valid_pipe_tok(t_list *node, t_token_type tok)
{
	return (ft_is_pipe(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->tok == RAW
		&& tok && !ft_is_redir_tok(tok) && !ft_is_pipe_tok(tok));
}

int	ft_valid_input_tok(t_list *node, t_token_type tok)
{
	return (ft_is_input(((t_token *)node->content)->str)
			&& ((t_token *)node->content)->tok == RAW
			&& (!tok || !ft_is_redir_tok(tok)));
}

int	ft_valid_output_tok(t_list *node, t_token_type tok)
{
	return (ft_is_output(((t_token *)node->content)->str)
			&& ((t_token *)node->content)->tok == RAW
			&& (!tok || !ft_is_redir_tok(tok)));
}

int	ft_valid_here_doc_tok(t_list *node, t_token_type tok)
{
	return (ft_is_here_doc(((t_token *)node->content)->str)
			&& ((t_token *)node->content)->tok == RAW
			&& (!tok || !ft_is_redir_tok(tok)));
}

int	ft_valid_append_tok(t_list *node, t_token_type tok)
{
	return (ft_is_append(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->tok == RAW
			&& (!tok || !ft_is_redir_tok(tok)));
}

int	ft_valid_infile_tok(t_list *node, t_token_type tok)
{
	return (!ft_is_pipe(((t_token *)node->content)->str)
			&& !ft_is_redir(((t_token *)node->content)->str)
			&& ((t_token *)node->content)->tok == RAW
			&& tok && ft_is_input_tok(tok));
}

int	ft_valid_delimiter_tok(t_list *node, t_token_type tok)
{
	return (!ft_is_pipe(((t_token *)node->content)->str)
			&& !ft_is_redir(((t_token *)node->content)->str)
			&& ((t_token *)node->content)->tok == RAW
			&& tok && ft_is_here_doc_tok(tok));
}

int	ft_valid_outfile_tok(t_list *node, t_token_type tok)
{
	return (!ft_is_pipe(((t_token *)node->content)->str)
			&& !ft_is_redir(((t_token *)node->content)->str)
			&& ((t_token *)node->content)->tok == RAW
			&& tok && (ft_is_append_tok(tok) || ft_is_output_tok(tok)));
}

int	ft_valid_arg_tok(t_list *node, t_token_type tok)
{
	return (!ft_is_pipe(((t_token *)node->content)->str)
			&& !ft_is_redir(((t_token *)node->content)->str)
			&& ((t_token *)node->content)->tok == RAW
			&& (!tok || !ft_is_redir_tok(tok)));
}

//int	ft_pipe_need_more_input(t_list *node, t_list *stack)

//t_list	*ft_lst_dup(t_list *)

int	ft_parse_token(t_list *node)
{
	t_token_type	last;

	last = RAW;
	while (node)
	{
		if (ft_valid_pipe_tok(node, last))
			((t_token *)node->content)->tok = PIPE;
		else if (ft_valid_input_tok(node, last))
			((t_token *)node->content)->tok = INPUT;
		else if (ft_valid_output_tok(node, last))
			((t_token *)node->content)->tok = OUTPUT;
		else if (ft_valid_here_doc_tok(node, last))
			((t_token *)node->content)->tok = HERE_DOC;
		else if (ft_valid_append_tok(node, last))
			((t_token *)node->content)->tok = APPEND;
		else if (ft_valid_delimiter_tok(node, last))
			((t_token *)node->content)->tok = DELIMITER;
		else if (ft_valid_infile_tok(node, last))
			((t_token *)node->content)->tok = INFILE;
		else if (ft_valid_outfile_tok(node, last))
			((t_token *)node->content)->tok = OUTFILE;
		else if (ft_valid_arg_tok(node, last))
			((t_token *)node->content)->tok = ARG;
		else if (((t_token *)node->content)->tok == RAW)
			return (0);
		//ft_lstadd_front(&stack, node);
		last = ((t_token *)node->content)->tok;
		node = node->next;
	}
	//ft_print_enum(last);
	//printf("\n");
	if (last && ft_is_redir_tok(last))
		return (0); // clean up
	if (last && (ft_is_pipe_tok(last)
		|| ft_is_double_quote_tok(last)
		|| ft_is_single_quote_tok(last))) // or unfinished quote
		return (2); // clean up
	// if pipe or unfinished quote is at the top of the stack, clean up and return 2
	//clean up stack
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	char			cwd[2000];
	//struct termios	ter;
	t_list			*cmds;
	t_list			*tokens;
	int				parse_res;

	//tcgetattr(1, &ter);
	//ter.c_lflag |= ECHOCTL;
	//ter.c_lflag |= ICANON;t_list
	//tcsetattr(1, 0, &ter);
	argc += 0;
	argv += 0;
	env += 0;
	cmds = 0;
	cmds += 0;
	printf("current working path=%s\n", getcwd(cwd, 2000));
	ft_import_history();
	while (1)
	{
		line = readline("42minishell>>> ");
		if (!line)
			break ;
		ft_trim_write_history(&line);
		printf("input=%s\n", line);
		if (ft_strlen(line))
		{
			tokens = ft_tokenize(line);
			parse_res = ft_parse_token(tokens);
			if (parse_res == 1)
				ft_print_tokens(tokens);
			else if (parse_res == 2)
				printf("need more input\n");
			else
				printf("parse error\n");
			//cmds = ft_split_parse_cmds(line, env);
			//ft_exec_cmds(cmds);
			//ft_print_cmds(cmds);
		}
		//else
			//exe single cmd
		free(line);
	}
	return (0);
}