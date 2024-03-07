/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 20:52:47 by luyang            #+#    #+#             */
/*   Updated: 2024/03/07 01:16:21 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_fill_hd_child_helper(t_ast **node, int i, int fd)
{
	char	*line;
	char	*tmp;

	if (!node)
		return (INVALID_POINTER);
	line = readline(PROMPT_CON);
	tmp = (*node)->cmd->redirs[i + 1];
	while (line && ft_strncmp(line, tmp, ft_strlen(tmp) + 1))
	{
		if (write(fd, line, ft_strlen(line)) == -1
			|| write(fd, "\n", 1) == -1)
			return (close(fd), EXE_FAILURE);
		free(line);
		line = readline(PROMPT_CON);
	}
	free(line);
	if (!line)
	{
		printf(HD_NULL_MSG);
		printf(HD_NULL_MSG2, tmp);
	}
	close(fd);
	return (EXE_SUCCESS);
}

int	ft_fill_hd_child(t_ast **node)
{
	int	i;
	int	j;
	int	fd;
	int	status;

	if (!node)
		return (INVALID_POINTER);
	i = 0;
	j = 0;
	while ((*node)->cmd->redirs[i])
	{
		if (ft_is_here_doc((*node)->cmd->redirs[i]))
		{
			fd = open((*node)->cmd->here_doc_files[j++],
					O_WRONLY | O_TRUNC | O_CREAT, 0777);
			if (fd == -1)
				return (EXE_FAILURE);
			status = ft_fill_hd_child_helper(node, i, fd);
			if (status != EXE_SUCCESS)
				return (status);
		}
		i++;
	}
	return (EXE_SUCCESS);
}

int	ft_fill_hd_simple_cmd(t_ast **node, int status)
{
	pid_t	pid;

	if (!node)
		return (INVALID_POINTER);
	ft_setup_signal_handler_child(TRUE);
	pid = fork();
	if (pid == -1)
		return (EXE_FAILURE);
	else if (pid == 0)
	{
		status = ft_fill_hd_child(node);
		if (status == EXE_FAILURE || status == INVALID_POINTER)
			return (status);
		(ft_free_res(FALSE), exit(EXE_SUCCESS));
	}
	else
	{
		signal(SIGINT, &ft_signal_handler_exe_parent);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (ft_get_exit_status(status))
			ft_vars()->last_exe_res = ft_get_exit_status(status);
		return (ft_get_exit_status(status));
	}
}

int	ft_fill_here_doc(t_ast *node)
{
	int	status;

	status = EXE_SUCCESS;
	if (!node)
		return (INVALID_POINTER);
	if (node->toktype == SIMPLE_CMD)
		return (ft_fill_hd_simple_cmd(&node, status));
	else
	{
		status = ft_fill_here_doc(node->left);
		if (node->toktype != SUBSHELL && status == EXE_SUCCESS)
			status = ft_fill_here_doc(node->right);
		return (status);
	}
}
