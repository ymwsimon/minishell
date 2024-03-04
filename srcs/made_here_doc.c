/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   made_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:23:11 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/04 22:41:28 by mayeung          ###   ########.fr       */
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
			node->cmd->here_doc_files[i] = ft_strjoin(".here_doc_", tmp);
			printf("the file name is %s\n", node->cmd->here_doc_files[i]);
			if (!node->cmd->here_doc_files[i])
				return (ALLOCATE_FAIL);
			fd = open(node->cmd->here_doc_files[i], O_WRONLY | O_TRUNC | O_CREAT, 0777);
			close(fd);
			free(tmp);
			(*id)++;
			i++;
		}
		return (0);
	}
	else
	{
		status = ft_create_here_doc(node->left, id);
		if (node->toktype != SUBSHELL)
			status |= ft_create_here_doc(node->right, id);
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
		ft_setup_signal_handler_child();
		pid = fork();
		if(pid == 0)
		{
			i = 0;
			j = 0;
			while (node->cmd->redirs[i])
			{
				if (ft_is_here_doc(node->cmd->redirs[i]))
				{
					//printf("file name = %s delimiter = %s \n", node->cmd->here_doc_files[j], node->cmd->redirs[i + 1]);
					fd = open(node->cmd->here_doc_files[j], O_WRONLY | O_TRUNC | O_CREAT, 0777);
					if (fd == -1)
						return (-1);
					line = readline(PROMPT_CON);
					tmp = node->cmd->redirs[i + 1];
					//printf("the deli %s\n", tmp);
					//printf("the line %s\n", line);
					while (line && ft_strncmp(line, tmp, ft_strlen(tmp) + 1))
					{
						if (write(fd, line, ft_strlen(line)) == -1)
							return (close(fd), ALLOCATE_FAIL);
						free(line);
						line = readline(PROMPT_CON);
					}
					if (!line)
						printf("warning: here-document delimited by end-of-file (wanted `%s')\n", tmp);
					close(fd);
					j++;
				}
				i++;
			}
			ft_free_res(0);
			exit(0);
		}
		else
		{
			signal(SIGINT, &ft_signal_handler_exe_parent);
			signal(SIGQUIT, &ft_signal_handler_exe_parent);
			waitpid(pid, &status, 0);
			//printf("%d\n", status);
			return (ft_get_exit_status(status));
		}
	}
	else
	{
		status = ft_fill_here_doc(node->left);
		if (node->toktype != SUBSHELL && status == 0)
			status = ft_fill_here_doc(node->right);
		return (status);
	}
}
