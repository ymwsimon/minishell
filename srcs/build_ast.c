/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:46:40 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/08 19:44:42 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	ft_break_into_ast_node(t_ast **ast, t_list *lhead,
	t_list *parent, t_list *rhead)
{
	t_list	*node;
	int		status;

	if (!ast || !lhead || !parent || !rhead)
		return (INVALID_POINTER);
	*ast = ft_calloc(1, sizeof(t_ast));
	if (!(*ast))
		return (ft_lstclear(&ft_vars()->toklist, &ft_free_token_node),
			ft_vars()->toklist = NULL, ALLOCATE_FAIL);
	(*ast)->toktype = ((t_token *)parent->content)->toktype;
	node = lhead;
	while (node->next != parent)
		node = node->next;
	node->next = NULL;
	status = ft_build_ast(&(*ast)->left, lhead);
	if (!status)
		status = ft_build_ast(&(*ast)->right, rhead);
	if (!status)
		ft_lstdelone(parent, &ft_free_token_node);
	return (status);
}

int	ft_break_into_subshell(t_ast **ast, t_list *tokens)
{
	t_list	*last;
	t_list	*node;

	if (!ast || !tokens)
		return (INVALID_POINTER);
	*ast = ft_calloc(1, sizeof(t_ast));
	if (!(*ast))
		return (ft_lstclear(&ft_vars()->toklist, &ft_free_token_node),
			ft_vars()->toklist = NULL, ALLOCATE_FAIL);
	(*ast)->right = NULL;
	(*ast)->toktype = SUBSHELL;
	last = ft_lstlast(tokens);
	node = tokens;
	while (node->next != last)
		node = node->next;
	node->next = NULL;
	ft_lstdelone(last, &ft_free_token_node);
	node = tokens->next;
	ft_lstdelone(tokens, &ft_free_token_node);
	return (ft_build_ast(&(*ast)->left, node));
}

void	ft_ast_process_node(t_list *iter, int *n_open_par,
	int *symbol_to_check, t_list **break_point)
{
	if (!iter || !n_open_par || !symbol_to_check || !break_point)
		return ;
	if (ft_check_sym(iter, *symbol_to_check)
		&& ft_is_open_paren_tok(iter->content))
	{
		*symbol_to_check = PAREN;
		(*n_open_par)++;
	}
	else if (ft_check_sym(iter, *symbol_to_check)
		&& ft_is_close_paren_tok(iter->content))
	{
		(*n_open_par)--;
		if ((*n_open_par) == 0)
			*symbol_to_check = OPENPAR_AND_OR_PIPE;
	}
	else if (ft_check_sym(iter, *symbol_to_check))
		*break_point = iter;
}

int	ft_build_ast(t_ast **ast, t_list *tokens)
{
	t_list		*iter;
	t_list		*break_point;
	int			symbol_to_check;
	int			n_open_par;

	if (!tokens)
		return (INVALID_POINTER);
	iter = tokens;
	break_point = NULL;
	symbol_to_check = OPENPAR_AND_OR_PIPE;
	n_open_par = 0;
	while (iter)
	{
		ft_ast_process_node(iter, &n_open_par, &symbol_to_check, &break_point);
		iter = iter->next;
	}
	if (break_point)
		return (ft_break_into_ast_node(ast, tokens, break_point,
				break_point->next));
	else if (ft_is_open_paren_tok(tokens->content))
		return (ft_break_into_subshell(ast, tokens));
	else
		return (ft_break_into_sc(ast, tokens));
}

/*
char	*ft_enum_to_str(t_token_type t)
{
	char	*res;

	res = NULL;
	if (t == PIPE)
		res = "|";
	else if (t == HERE_DOC)
		res = "<<";
	else if (t == INPUT)
		res = "<";
	else if (t == OUTPUT)
		res = ">";
	else if (t == APPEND)
		res = ">>";
	else if (t == AND)
		res = "&&";
	else if (t == OR)
		res = "||";
	return (res);
}



void	ft_print_ast(t_ast *node)
{
	size_t	i;
	t_token	t;

	if (!node)
		return ;
	t.toktype = node->toktype;
	if (ft_is_pipe_tok(&t) || ft_is_and_tok(&t)
		|| ft_is_or_tok(&t))
	{
		ft_print_ast(node->left);
		printf(" %s ", ft_enum_to_str(node->toktype));
		ft_print_ast(node->right);
	}
	else if (node->toktype == SIMPLE_CMD)
	{
		i = 0;
		while (node->cmd->args[i])
			printf("%s ", node->cmd->args[i++]);
		i = 0;
		while (node->cmd->redirs[i])
			printf("%s ", node->cmd->redirs[i++]);
	}
	else if (node->toktype == SUBSHELL)
	{
		printf("(");
		ft_print_ast(node->left);
		printf(")");
	}
}
*/