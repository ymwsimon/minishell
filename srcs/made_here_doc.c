/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   made_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:23:11 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/14 13:07:04 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_create_here_doc(t_ast *node, int *id)
{
	int		i;
	int		nhere_doc;
	int		fd;
	char	*line;
	char	*tmp;

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
			i += 2;
		}
		node->cmd->here_doc_files = malloc(sizeof(char *) * (nhere_doc + 1));
		if (!node->cmd->here_doc_files)
			return (ALLOCATE_FAIL);
		i = 0;
		while (i <= nhere_doc)
		{
			node->cmd->here_doc_files[i] = ft_strjoin(".here_doc_", ft_itoa(*id));
			(*id)++;
			i++;
		}
		node->cmd->here_doc_files[i] = NULL;
		i = 0;
		while (node->cmd->redirs[i])
		{
			if (ft_is_here_doc(node->cmd->redirs[i]))
			{
				printf("file name = %s\n", node->cmd->here_doc_files[i / 2]);
				fd = open(node->cmd->here_doc_files[i / 2], O_WRONLY | O_TRUNC | O_CREAT, 0777);
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
			}
			i += 2;
		}
	}
	else
	{
		ft_create_here_doc(node->left, id);
		ft_create_here_doc(node->right, id);
	}
	return (1);
}
