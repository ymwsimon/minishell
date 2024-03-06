/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:35:30 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/06 19:39:02 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast	*ft_allocate_mem_sc_node(t_ast *res, size_t nredirs, size_t narg)
{
	res->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!res->cmd)
		return (free(res), NULL);
	res->cmd->args = ft_calloc(narg + 1, sizeof(char *));
	if (!res->cmd->args)
		return (free(res->cmd), free(res), NULL);
	res->cmd->redirs = ft_calloc(nredirs * 2 + 1, sizeof(char *));
	if (!res->cmd->redirs)
		return (free(res->cmd->args), free(res->cmd), free(res), NULL);
	return (res);
}

t_ast	*ft_init_sc_node(t_list *tokens)
{
	t_ast	*res;
	t_list	*node;
	size_t	nredirs;
	size_t	narg;

	res = ft_calloc(1, sizeof(t_ast));
	if (!res)
		return (NULL);
	res->toktype = SIMPLE_CMD;
	narg = 0;
	nredirs = 0;
	node = tokens;
	while (node)
	{
		if (ft_is_arg_tok(node->content))
			narg++;
		else if (ft_is_redir_tok(node->content))
			nredirs++;
		node = node->next;
	}
	res = ft_allocate_mem_sc_node(res, nredirs, narg);
	return (res);
}

void	ft_process_making_sc_node(t_list *node, t_ast *res,
	size_t *nredirs, size_t *narg)
{
	if (ft_is_arg_tok(node->content))
		res->cmd->args[(*narg)++]
			= ft_string_resolve(((t_token *)node->content)->str, 0);
	else if (ft_is_redir_tok(node->content)
		|| ft_is_infile_tok(node->content)
		|| ft_is_outfile_tok(node->content))
		res->cmd->redirs[(*nredirs)++]
			= ft_string_resolve(((t_token *)node->content)->str, 0);
	else if (ft_is_delimiter_tok(node->content))
		res->cmd->redirs[(*nredirs)++]
			= ft_string_resolve(((t_token *)node->content)->str, 1);
}

t_ast	*ft_break_into_sc(t_list *tokens)
{
	t_ast	*res;
	t_list	*node;
	t_list	*old_node;
	size_t	nredirs;
	size_t	narg;

	res = ft_init_sc_node(tokens);
	if (!res)
		return (NULL);
	node = tokens;
	narg = 0;
	nredirs = 0;
	while (node)
	{
		ft_process_making_sc_node(node, res, &nredirs, &narg);
		old_node = node;
		node = node->next;
		free(old_node->content);
		free(old_node);
	}
	return (res);
}

void	ft_free_ast(t_ast **node, int del_hd)
{
	size_t	i;

	if (!node || !(*node))
		return ;
	if ((*node)->toktype == SIMPLE_CMD)
	{
		ft_clear_char_arr((*node)->cmd->args);
		ft_clear_char_arr((*node)->cmd->redirs);
		i = 0;
		while (del_hd && (*node)->cmd->here_doc_files
			&& (*node)->cmd->here_doc_files[i])
			unlink((*node)->cmd->here_doc_files[i++]);
		ft_clear_char_arr((*node)->cmd->here_doc_files);
		free((*node)->cmd);
	}
	ft_free_ast(&(*node)->left, del_hd);
	ft_free_ast(&(*node)->right, del_hd);
	free((*node));
	*node = NULL;
}
