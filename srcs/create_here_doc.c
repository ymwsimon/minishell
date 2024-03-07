/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:23:11 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/07 17:17:45 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_create_hd_simple_cmd(t_ast **node, int i, int *id, int nhere_doc)
{
	int		fd;
	char	*tmp;

	if (!node || !id)
		return (INVALID_POINTER);
	(*node)->cmd->here_doc_files = ft_calloc(sizeof(char *), nhere_doc + 1);
	if (!(*node)->cmd->here_doc_files)
		return (ALLOCATE_FAIL);
	while (i < nhere_doc)
	{
		tmp = ft_free_join_str(ft_strdup(HERE_DOC_PREFIX), ft_itoa(*id));
		(*node)->cmd->here_doc_files[i] = ft_free_join_str(ft_free_join_str
				(ft_strdup(ft_getenv("HOME")), ft_strdup("/")), tmp);
		if (!(*node)->cmd->here_doc_files[i])
			return (ALLOCATE_FAIL);
		fd = open((*node)->cmd->here_doc_files[i++],
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd == -1)
			return (EXE_FAILURE);
		(close(fd), (*id)++);
	}
	return (EXE_SUCCESS);
}

int	ft_create_here_doc(t_ast *node, int *id)
{
	int		i;
	int		nhere_doc;
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
		return (ft_create_hd_simple_cmd(&node, 0, id, nhere_doc));
	}
	else
	{
		status = ft_create_here_doc(node->left, id);
		if (node->toktype != SUBSHELL && status == EXE_SUCCESS)
			status = ft_create_here_doc(node->right, id);
		return (status);
	}
}
