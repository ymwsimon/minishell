/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <luyang@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:23:11 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/06 20:54:48 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_create_hd_simple_cmd(t_ast **node, int *i, int *id, int nhere_doc)
{
	int		fd;
	char	*tmp;

	if (!node || !i || !id)
		return (INVALID_POINTER);
	(*node)->cmd->here_doc_files = ft_calloc(sizeof(char *), nhere_doc + 1);
	if (!(*node)->cmd->here_doc_files)
		return (ALLOCATE_FAIL);
	i = 0;
	while (*i < nhere_doc)
	{
		tmp = ft_itoa(*id);
		if (!tmp)
			return (ALLOCATE_FAIL);
		(*node)->cmd->here_doc_files[*i] = ft_strjoin(HERE_DOC_PREFIX, tmp);
		if (!(*node)->cmd->here_doc_files[*i])
			return (free(tmp), ALLOCATE_FAIL);
		fd = open((*node)->cmd->here_doc_files[(*i)++],
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd == -1)
			return (free(tmp), EXE_FAILURE);
		close(fd), free(tmp), (*id)++;
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
			if (ft_is_here_doc(node->cmd->redirs[i++]))
				nhere_doc++;
		}
		return (ft_create_hd_simple_cmd(&node, &i, id, nhere_doc));
	}
	else
	{
		status = ft_create_here_doc(node->left, id);
		if (node->toktype != SUBSHELL && status == EXE_SUCCESS)
			status = ft_create_here_doc(node->right, id);
		return (status);
	}
}

