/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:21:42 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/03 00:32:35 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	import_history(void)
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

void	ft_write_history(char *line)
{
	int		fd;
	char	*path;
	char	*line_with_newline;

	if (line && !ft_strlen(line))
		return ;
	path = ft_strjoin(getenv("HOME"), "/.minishell_cmd_history");
	add_history(line);
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	//printf("path of the history file=%s, fd=%d\n", path, fd);
	if (fd >= 0)
	{
		line_with_newline = ft_strjoin(line, "\n");
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

int	*ft_init_pipe(size_t ncmd)
{
	int		*res;
	size_t	i;

	res = malloc(sizeof(int) * (ncmd - 1) * 2);
	if (!res)
		return (NULL);
	i = 0;
	while (i < ncmd - 1)
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

void	ft_print_cmd_arg(char **args)
{
	printf("args: ");
	while (args && *args)
	{
		printf("%s ", *args);
		args++;
	}
}

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

void	ft_exec_cmds(t_list *cmds)
{
	pid_t	cpid;
	t_cmd	*cmd;
	t_list	*node;
	char	*full_path;
	int		r;
	int		fd;
	//size_t	i;

	//i = 0;
	node = cmds;
	while (node)
	{
		cpid = fork();
		cmd = node->content;
		if (!cpid)
		{	
			if (!node->next && 0)
			{
				fd = open("testout", O_WRONLY | O_CREAT | O_TRUNC, 0777);
				cmd->outfd = fd;
			}
			ft_redir_fds(cmd->infd, cmd->outfd);
			if (!node->next && 0)
				close(fd);
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

int	main(int argc, char **argv, char **env)
{
	char			*line;
	char			cwd[2000];
	//struct termios	ter;
	t_list			*cmds;

	//tcgetattr(1, &ter);
	//ter.c_lflag |= ECHOCTL;
	//ter.c_lflag |= ICANON;
	//tcsetattr(1, 0, &ter);
	argc += 0;
	argv += 0;
	printf("current working path=%s\n", getcwd(cwd, 2000));
	import_history();
	while (1)
	{
		line = readline("42minishell>>> ");
		if (!line)
			break ;
		ft_write_history(line);
		printf("input=%s\n", line);
		if (ft_strchr(line, '|'))
		{
			cmds = ft_split_parse_cmds(line, env);
			ft_exec_cmds(cmds);
			//ft_print_cmds(cmds);
		}
		//else
			//exe single cmd
		free(line);
	}
	return (0);
}