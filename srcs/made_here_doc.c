/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   made_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:23:11 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/06 16:55:04 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_create_here_doc(t_ast *node, int *id)
{
	int		i;
	int		nhere_doc;
	int		fd;
	char	*tmp;
	int		status;

	if (!node || !id)
		return (INVALID_POINTER);
	if (node->toktype == SIMPLE_CMD)
	{
		i = 0;
		nhere_doc = 0;
		while (node->cmd->redirs[i])
		{
			if (ft_is_here_doc(node->cmd->redirs[i]))
				nhere_doc++;
			i++;
		}
		node->cmd->here_doc_files = ft_calloc(sizeof(char *), nhere_doc + 1);
		if (!node->cmd->here_doc_files)
			return (ALLOCATE_FAIL);
		i = 0;
		while (i < nhere_doc)
		{
			tmp = ft_itoa(*id);
			if (!tmp)
				return (ALLOCATE_FAIL);
			node->cmd->here_doc_files[i] = ft_strjoin(HERE_DOC_PREFIX, tmp);
			if (!node->cmd->here_doc_files[i])
				return (free(tmp), ALLOCATE_FAIL);
			fd = open(node->cmd->here_doc_files[i],
					O_WRONLY | O_TRUNC | O_CREAT, 0777);
			if (fd == -1)
				return (free(tmp), EXE_FAILURE);
			close(fd);
			free(tmp);
			(*id)++;
			i++;
		}
		return (EXE_SUCCESS);
	}
	else
	{
		status = ft_create_here_doc(node->left, id);
		if (node->toktype != SUBSHELL && status == EXE_SUCCESS)
			status = ft_create_here_doc(node->right, id);
		return (status);
	}
}

int	ft_fill_here_doc(t_ast *node)
{
	int		i;
	int		j;
	int		fd;
	char	*line;
	char	*tmp;
	pid_t	pid;
	int		status;

	if (!node)
		return (INVALID_POINTER);
	if (node->toktype == SIMPLE_CMD)
	{
		ft_setup_signal_handler_child(TRUE);
		pid = fork();
		if (pid == -1)
			return (EXE_FAILURE);
		else if (pid == 0)
		{
			i = 0;
			j = 0;
			while (node->cmd->redirs[i])
			{
				if (ft_is_here_doc(node->cmd->redirs[i]))
				{
					fd = open(node->cmd->here_doc_files[j],
							O_WRONLY | O_TRUNC | O_CREAT, 0777);
					if (fd == -1)
						return (EXE_FAILURE);
					line = readline(PROMPT_CON);
					tmp = node->cmd->redirs[i + 1];
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
					j++;
				}
				i++;
			}
			ft_free_res(FALSE);
			exit(EXE_SUCCESS);
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
	else
	{
		status = ft_fill_here_doc(node->left);
		if (node->toktype != SUBSHELL && status == EXE_SUCCESS)
			status = ft_fill_here_doc(node->right);
		return (status);
	}
}
