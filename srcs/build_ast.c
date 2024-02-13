/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:46:40 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/13 11:59:27 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_ast(t_ast *node)
{
	size_t	i;

	if (!node)
		return ;
	if (ft_is_pipe_tok(node->tok) || ft_is_and_tok(node->tok)
		|| ft_is_or_tok(node->tok))
	{
		ft_print_ast(node->left);
		printf(" %s ", node->tok->str);
		ft_print_ast(node->right);
	}
	else if (node->tok->toktype == SIMPLE_CMD)
	{
		i = 0;
		while (node->tok->cmd->args[i])
			printf("%s ", node->tok->cmd->args[i++]);
		i = 0;
		while (node->tok->cmd->redirs[i])
			printf("%s ", node->tok->cmd->redirs[i++]);
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
		return (ft_is_open_paren_tok(t) || ft_is_and_tok(t)
			|| ft_is_or_tok(t) || ft_is_pipe_tok(t));
	else
		return (ft_is_open_paren_tok(t) || ft_is_close_paren_tok(t));
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
	return (res);
}

t_ast	*ft_break_into_subshell(t_list *tokens)
{
	t_ast	*res;
	t_list	*last;
	t_list	*node;

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
	node = tokens->next;
	ft_lstdelone(tokens, &ft_free_token_node);
	res->left = ft_build_ast(node);
	return (res);
}

t_ast	*ft_break_into_sc(t_list *tokens)
{
	t_ast	*res;
	t_list	*node;
	size_t	nredirs;
	size_t	narg;

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
		if (ft_is_arg_tok(node->content))
			narg++;
		else if (ft_is_redir_tok(node->content))
			nredirs++;
		node = node->next;
	}
	res->tok->cmd = malloc(sizeof(t_cmd));
	if (!res->tok->cmd)
		return (free(res->tok), free(res), NULL);
	res->tok->cmd->args = malloc(sizeof(char *) * (narg + 1));
	res->tok->cmd->redirs = malloc(sizeof(char *) * (nredirs * 2 + 1));
	node = tokens;
	narg = 0;
	nredirs = 0;
	while (node)
	{
		if (ft_is_arg_tok(node->content))
			res->tok->cmd->args[narg++] = ft_strdup(((t_token *)node->content)->str);
		else if (ft_is_redir_tok(node->content)
			|| ft_is_infile_tok(node->content)
			|| ft_is_outfile_tok(node->content)
			|| ft_is_delimiter_tok(node->content))
			res->tok->cmd->redirs[nredirs++] = ft_strdup(((t_token *)node->content)->str);
		node = node->next;
	}
	res->tok->cmd->args[narg] = NULL;
	res->tok->cmd->redirs[nredirs] = NULL;
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
			&& ft_is_open_paren_tok(iter->content))
		{
			symbol_to_check = PAREN;
			n_open_par++;
		}
		else if (ft_check_sym(iter, symbol_to_check)
			&& ft_is_close_paren_tok(iter->content))
		{
			n_open_par--;
			if (!n_open_par)
				symbol_to_check = OPENPAR_AND_OR_PIPE;
		}
		else if (ft_check_sym(iter, symbol_to_check))
			return (ft_break_into_ast_node(tokens, iter, iter->next));
		iter = iter->next;
	}
	if (ft_is_open_paren_tok(tokens->content))
		return (ft_break_into_subshell(tokens));
	else
		return (ft_break_into_sc(tokens));
}
