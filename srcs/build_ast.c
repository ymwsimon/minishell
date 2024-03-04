/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:46:40 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/03 22:18:09 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_free_ast(t_ast *node)
{
	size_t	i;

	if (!node)
		return ;
	if (node->toktype == SIMPLE_CMD)
	{
		ft_clear_char_arr(node->cmd->args);
		ft_clear_char_arr(node->cmd->redirs);
		i = 0;
		while (node->cmd->here_doc_files && node->cmd->here_doc_files[i])
			unlink(node->cmd->here_doc_files[i++]);
		ft_clear_char_arr(node->cmd->here_doc_files);
		free(node->cmd);
	}
	ft_free_ast(node->left);
	ft_free_ast(node->right);
	free(node);
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

	res = ft_calloc(1, sizeof(t_ast));
	if (!res)
		return (NULL);
	res->toktype = ((t_token *)parent->content)->toktype;
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

	res = ft_calloc(1, sizeof(t_ast));
	if (!res)
		return (NULL);
	res->right = NULL;
	res->toktype = SUBSHELL;
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
	t_list	*old_node;
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
	res->cmd = ft_calloc(1, sizeof(t_cmd));
	if (!res->cmd)
		return (free(res), NULL);
	res->cmd->args = ft_calloc(narg + 1, sizeof(char *));
	if (!res->cmd->args)
		return (free(res->cmd), free(res), NULL);
	res->cmd->redirs = ft_calloc(nredirs * 2 + 1, sizeof(char *));
	if (!res->cmd->redirs)
		return (free(res->cmd->args), free(res->cmd), free(res), NULL);
	node = tokens;
	narg = 0;
	nredirs = 0;
	while (node)
	{
		if (ft_is_arg_tok(node->content))
			res->cmd->args[narg++] = ft_string_resolve(((t_token *)node->content)->str, 0);
		else if (ft_is_redir_tok(node->content)
			|| ft_is_infile_tok(node->content)
			|| ft_is_outfile_tok(node->content))
			res->cmd->redirs[nredirs++] = ft_string_resolve(((t_token *)node->content)->str, 0);
		else if (ft_is_delimiter_tok(node->content))
			res->cmd->redirs[nredirs++] = ft_string_resolve(((t_token *)node->content)->str, 1);
		old_node = node;
		node = node->next;
		free(old_node->content);
		free(old_node);
	}
	return (res);
}

t_ast	*ft_build_ast(t_list *tokens)
{
	t_list		*iter;
	t_list		*break_point;
	int			symbol_to_check;
	int			n_open_par;

	if (!tokens)
		return (NULL);
	iter = tokens;
	break_point = NULL;
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
			break_point = iter;
		iter = iter->next;
	}
	if (break_point)
		return (ft_break_into_ast_node(tokens, break_point, break_point->next));
	else if (ft_is_open_paren_tok(tokens->content))
		return (ft_break_into_subshell(tokens));
	else
		return (ft_break_into_sc(tokens));
}
