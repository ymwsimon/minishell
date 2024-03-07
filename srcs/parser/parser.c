/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:25:13 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/07 01:21:30 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_invalid_tok(t_list *n)
{
	t_token	*node;

	node = n->content;
	return (!node->toktype && (!(ft_strncmp(node->str, "&", ft_strlen("&") + 1))
			|| !(ft_strncmp(node->str, ";", ft_strlen(";") + 1))
			|| !(ft_strncmp(node->str, "((", ft_strlen("((") + 1))
			|| !(ft_strncmp(node->str, "))", ft_strlen("))") + 1))));
}

int	ft_need_more_input(t_token *t, int open_paren)
{
	return (ft_is_pipe_tok(t)
		|| ft_is_double_quote_tok(t)
		|| ft_is_single_quote_tok(t)
		|| ft_is_and_tok(t)
		|| ft_is_or_tok(t)
		|| ft_is_open_paren_tok(t)
		|| open_paren > 0);
}

void	ft_parse_token_helper1(t_list **node, t_token *last, int *open_paren)
{
	if (!node || !last || !open_paren)
		return ;
	if (ft_valid_output_tok(*node, last))
		((t_token *)(*node)->content)->toktype = OUTPUT;
	else if (ft_valid_here_doc_tok(*node, last))
		((t_token *)(*node)->content)->toktype = HERE_DOC;
	else if (ft_valid_append_tok(*node, last))
		((t_token *)(*node)->content)->toktype = APPEND;
	else if (ft_valid_delimiter_tok(*node, last))
		((t_token *)(*node)->content)->toktype = DELIMITER;
	else if (ft_valid_infile_tok(*node, last))
		((t_token *)(*node)->content)->toktype = INFILE;
	else if (ft_valid_outfile_tok(*node, last))
		((t_token *)(*node)->content)->toktype = OUTFILE;
	else if (ft_valid_and_tok(*node, last))
		((t_token *)(*node)->content)->toktype = AND;
	else if (ft_valid_or_tok(*node, last))
		((t_token *)(*node)->content)->toktype = OR;
	else if (ft_valid_open_paren_tok(*node, last, open_paren))
		((t_token *)(*node)->content)->toktype = OPEN_PAREN;
	else if (ft_valid_close_paren_tok(*node, last, open_paren))
		((t_token *)(*node)->content)->toktype = CLOSE_PAREN;
	else if (ft_valid_arg_tok(*node, last))
		((t_token *)(*node)->content)->toktype = ARG;
}

int	ft_parse_token_helper(t_list **node, t_token *last, int *open_paren)
{
	if (!node || !last || !open_paren)
		return (PARSE_FAIL);
	while (*node)
	{
		if (ft_valid_pipe_tok(*node, last))
			((t_token *)(*node)->content)->toktype = PIPE;
		else if (ft_valid_input_tok(*node, last))
			((t_token *)(*node)->content)->toktype = INPUT;
		else if (((t_token *)(*node)->content)->toktype != RAW)
			ft_parse_token_helper1(node, last, open_paren);
		else
		{
			printf("unexcepted token: %s\n", ((t_token *)(*node)->content)->str);
			return (PARSE_FAIL);
		}
		last->toktype = ((t_token *)(*node)->content)->toktype;
		(*node) = (*node)->next;
	}
	return (PARSE_OK);
}

int	ft_parse_token(t_list *node)
{
	t_token	last;
	int		open_paren;
	int		status;

	last.toktype = RAW;
	open_paren = 0;
	status = ft_parse_token_helper(&node, &last, &open_paren);
	if (status == PARSE_FAIL)
		return (status);
	if (!ft_is_raw_tok(&last) && ft_is_redir_tok(&last))
	{
		ft_putstr_fd("minishell: syntax "
			"error near unexpected token `newline'\n", 2);
		return (PARSE_FAIL);
	}
	if (ft_need_more_input(&last, open_paren))
		return (IMCOMPELETE_CMD);
	return (PARSE_OK);
}
