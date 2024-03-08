/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:35:30 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/08 16:11:08 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_allocate_mem_sc_node(t_ast *res, size_t nredirs, size_t narg)
{
	res->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!res->cmd)
		return (ALLOCATE_FAIL);
	res->cmd->args = ft_calloc(narg + 1, sizeof(char *));
	if (!res->cmd->args)
		return (free(res->cmd), ALLOCATE_FAIL);
	res->cmd->redirs = ft_calloc(nredirs * 2 + 1, sizeof(char *));
	if (!res->cmd->redirs)
		return (free(res->cmd->args), free(res->cmd), ALLOCATE_FAIL);
	return (EXE_SUCCESS);
}

int	ft_init_sc_node(t_ast **ast, t_list *tokens)
{
	t_list	*node;
	size_t	nredirs;
	size_t	narg;

	*ast = ft_calloc(1, sizeof(t_ast));
	if (!(*ast))
		return (ALLOCATE_FAIL);
	(*ast)->toktype = SIMPLE_CMD;
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
	if (ft_allocate_mem_sc_node(*ast, nredirs, narg))
		return (free(*ast), ALLOCATE_FAIL);
	return (EXE_SUCCESS);
}

int	ft_process_making_sc_node(t_list *node, t_ast *res,
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
	return (EXE_SUCCESS);
}

int	ft_break_into_sc(t_ast **ast, t_list *tokens)
{
	t_list	*node;
	t_list	*old_node;
	size_t	nredirs;
	size_t	narg;

	if (!ast || !tokens)
		return (INVALID_POINTER);
	if (ft_init_sc_node(ast, tokens))
		return (ALLOCATE_FAIL);
	node = tokens;
	narg = 0;
	nredirs = 0;
	while (node)
	{
		if (ft_process_making_sc_node(node, *ast, &nredirs, &narg))
			return (ft_free_ast(ast, FALSE), EXE_FAILURE); // free linked list
		old_node = node;
		node = node->next;
		free(old_node->content);
		free(old_node);
	}
	return (EXE_SUCCESS);
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
