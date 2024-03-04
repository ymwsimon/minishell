/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   made_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:23:11 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/03 22:54:24 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_create_here_doc(t_ast *node, int *id)
{
	int		i;
	int		j;
	int		nhere_doc;
	int		fd;
	char	*line;
	char	*tmp;
	pid_t	pid;
	int		status;

	if (!node)
		return (0);
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
			if (!node->cmd->here_doc_files[i])
				return (ALLOCATE_FAIL);
			free(tmp);
			(*id)++;
			i++;
		}
		pid = fork();
		if(pid == 0)
		{
			i = 0;
			j = 0;
			while (node->cmd->redirs[i])
			{
				if (ft_is_here_doc(node->cmd->redirs[i]))
				{
					printf("file name = %s delimiter = %s \n", node->cmd->here_doc_files[j], node->cmd->redirs[i + 1]);
					fd = open(node->cmd->here_doc_files[j], O_WRONLY | O_TRUNC | O_CREAT, 0777);
					if (fd == -1)
						return (0);
					printf("%s", PROMPT_CON);
					line = get_next_line(STDIN_FILENO);
					tmp = ft_strjoin(node->cmd->redirs[i + 1], "\n");
					if (!tmp)
						return (ALLOCATE_FAIL);
					while (line && ft_strncmp(line, tmp, ft_strlen(tmp) + 1))
					{
						if (write(fd, line, ft_strlen(line)) == -1)
							return (close(fd), 0);
						free(line);
						printf("%s", PROMPT_CON);
						line = get_next_line(STDIN_FILENO);
					}
					close(fd);
					free(tmp);
					j++;
				}
				i++;
			}
			ft_free_res();
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
		status = ft_create_here_doc(node->left, id);
		if (node->toktype != SUBSHELL)
			status |= ft_create_here_doc(node->right, id);
		return (status);
	}
}
