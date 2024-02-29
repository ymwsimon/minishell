/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   made_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:23:11 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/29 20:17:41 by mayeung          ###   ########.fr       */
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
		return (1);
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
			node->cmd->here_doc_files[i] = ft_strjoin(".here_doc_", tmp);
			free(tmp);
			(*id)++;
			i++;
		}
		i = 0;
		j = 0;
		while (node->cmd->redirs[i])
		{
			if (ft_is_here_doc(node->cmd->redirs[i]))
			{
				pid = fork();
				if (pid == -1)
					return (-1);
				else if (pid == 0)
				{
					printf("file name = %s delimiter = %s \n", node->cmd->here_doc_files[j], node->cmd->redirs[i + 1]);
					fd = open(node->cmd->here_doc_files[j], O_WRONLY | O_TRUNC | O_CREAT, 0777);
					line = get_next_line(STDIN_FILENO);
					tmp = ft_strjoin(node->cmd->redirs[i + 1], "\n");
					while (line && ft_strncmp(line, tmp, ft_strlen(tmp) + 1))
					{
						write(fd, line, ft_strlen(line));
						free(line);
						line = get_next_line(STDIN_FILENO);
					}
					close(fd);
					free(tmp);
					exit(1);
				}
				else
				{
					signal(SIGINT, &ft_signal_exe_parent);
					signal(SIGQUIT, &ft_signal_exe_parent);
					waitpid(pid, &status, 0);
				}
				j++;
			}
			i++;
		}
	}
	else
	{
		status = ft_create_here_doc(node->left, id);
		status |= ft_create_here_doc(node->right, id);
		return (status);
	}
	return (status);
}
