/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:46:40 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/13 01:13:57 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_ast(t_ast *node)
{
	size_t	i;

	if (!node)
		return ;
	if (ft_is_pipe_tok(node->tok->toktype) || ft_is_and_tok(node->tok->toktype)
		|| ft_is_or_tok(node->tok->toktype))
	{
		ft_print_ast(node->left);
		printf(" %s ", node->tok->str);
		ft_print_ast(node->right);
	}
	else if (node->tok->toktype == SIMPLE_CMD)
	{
		i = 0;
		while (((t_cmd *)node->tok->cmd)->args[i])
			printf("%s ", ((t_cmd *)node->tok->cmd)->args[i++]);
		i = 0;
		while (((t_cmd *)node->tok->cmd)->redirs[i])
			printf("%s ", ((t_cmd *)node->tok->cmd)->redirs[i++]);
	}
	else if (node->tok->toktype == SUBSHELL)
	{
		printf("(");
		ft_print_ast(node->left);
		printf(")");
	}
}

int	ft_check_sym(t_list *n, int symbol_to_check)
{
	t_token	*t;

	t = n->content;
	if (symbol_to_check == OPENPAR_AND_OR_PIPE)
		return (ft_is_open_paren_tok(t->toktype) || ft_is_and_tok(t->toktype)
			|| ft_is_or_tok(t->toktype) || ft_is_pipe_tok(t->toktype));
	else
		return (ft_is_open_paren_tok(t->toktype)
			|| ft_is_close_paren_tok(t->toktype));
}

t_ast	*ft_break_into_ast_node(t_list *lhead, t_list *parent, t_list *rhead)
{
	t_ast	*res;
	t_list	*node;

	res = malloc(sizeof(t_ast));
	if (!res)
		return (NULL);
	res->tok = malloc(sizeof(t_token));
	if (!res->tok)
		return (free(res), NULL);
	res->tok->toktype = ((t_token *)parent->content)->toktype;
	res->tok->str = ft_strdup(((t_token *)parent->content)->str);
	node = lhead;
	while (node->next != parent)
		node = node->next;
	node->next = NULL;
	res->left = ft_build_ast(lhead);
	res->right = ft_build_ast(rhead);
	ft_lstdelone(parent, &ft_free_token_node);
	//free(parent);
	return (res);
}

t_ast	*ft_break_into_subshell(t_list *tokens)
{
	t_ast	*res;
	t_list		*last;
	t_list		*node;

	res = malloc(sizeof(t_ast));
	if (!res)
		return (NULL);
	res->right = NULL;
	res->tok = malloc(sizeof(t_token));
	if (!res->tok)
		return (free(res), NULL);
	res->tok->toktype = SUBSHELL;
	last = ft_lstlast(tokens);
	node = tokens;
	while (node->next != last)
		node = node->next;
	node->next = NULL;
	ft_lstdelone(last, &ft_free_token_node);
	//free(last);
	node = tokens->next;
	ft_lstdelone(tokens, &ft_free_token_node);
	//free(tokens);
	res->left = ft_build_ast(node);
	return (res);
}

t_ast	*ft_break_into_sc(t_list *tokens)
{
	t_ast	*res;
	t_list		*node;
	size_t		nredirs;
	size_t		narg;

	res = malloc(sizeof(t_ast));
	if (!res)
		return (NULL);
	res->left = NULL;
	res->right = NULL;
	res->tok = malloc(sizeof(t_token));
	if (!res->tok)
		return (free(res), NULL);
	res->tok->toktype = SIMPLE_CMD;
	narg = 0;
	nredirs = 0;
	node = tokens;
	while (node)
	{
		if (((t_token *)node->content)->toktype == ARG)
			narg++;
		else if (ft_is_redir_tok(((t_token *)node->content)->toktype))
			nredirs++;
		node = node->next;
	}
	res->tok->cmd = malloc(sizeof(t_cmd));
	if (!res->tok->cmd)
		return (free(res->tok), free(res), NULL);
	((t_cmd *)res->tok->cmd)->args = malloc(sizeof(char *) * (narg + 1));
	((t_cmd *)res->tok->cmd)->redirs = malloc(sizeof(char *) * (nredirs * 2 + 1));
	node = tokens;
	narg = 0;
	nredirs = 0;
	while (node)
	{
		if (((t_token *)node->content)->toktype == ARG)
			((t_cmd *)res->tok->cmd)->args[narg++] = ft_strdup(((t_token *)node->content)->str);
		else if (ft_is_redir_tok(((t_token *)node->content)->toktype)
			|| ft_is_infile_tok(((t_token *)node->content)->toktype)
			|| ft_is_outfile_tok(((t_token *)node->content)->toktype)
			|| ft_is_delimiter_tok(((t_token *)node->content)->toktype))
			((t_cmd *)res->tok->cmd)->redirs[nredirs++] = ft_strdup(((t_token *)node->content)->str);
		node = node->next;
	}
	((t_cmd *)res->tok->cmd)->args[narg] = NULL;
	((t_cmd *)res->tok->cmd)->redirs[nredirs] = NULL;
	return (res);
}

t_ast	*ft_build_ast(t_list *tokens)
{
	t_list		*iter;
	int			symbol_to_check;
	int			n_open_par;

	if (!tokens)
		return (NULL);
	iter = tokens;
	symbol_to_check = OPENPAR_AND_OR_PIPE;
	n_open_par = 0;
	while (iter)
	{
		if (ft_check_sym(iter, symbol_to_check)
			&& ft_is_open_paren_tok(((t_token *)iter->content)->toktype))
		{
			symbol_to_check = PAREN;
			n_open_par++;
		}
		else if (ft_check_sym(iter, symbol_to_check)
			&& ft_is_close_paren_tok(((t_token *)iter->content)->toktype))
		{
			n_open_par--;
			if (!n_open_par)
				symbol_to_check = OPENPAR_AND_OR_PIPE;
		}
		else if (ft_check_sym(iter, symbol_to_check))
			return (ft_break_into_ast_node(tokens, iter, iter->next));
		iter = iter->next;
	}
	if (ft_is_open_paren_tok(((t_token *)tokens->content)->toktype))
		return (ft_break_into_subshell(tokens));
	else
		return (ft_break_into_sc(tokens));
}
