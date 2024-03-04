/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:25:13 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/04 22:35:08 by mayeung          ###   ########.fr       */
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

int	ft_parse_token(t_list *node)
{
	t_token	last;
	int		open_paren;

	last.toktype = RAW;
	open_paren = 0;
	while (node)
	{
		if (ft_valid_pipe_tok(node, &last))
			((t_token *)node->content)->toktype = PIPE;
		else if (ft_valid_input_tok(node, &last))
			((t_token *)node->content)->toktype = INPUT;
		else if (ft_valid_output_tok(node, &last))
			((t_token *)node->content)->toktype = OUTPUT;
		else if (ft_valid_here_doc_tok(node, &last))
			((t_token *)node->content)->toktype = HERE_DOC;
		else if (ft_valid_append_tok(node, &last))
			((t_token *)node->content)->toktype = APPEND;
		else if (ft_valid_delimiter_tok(node, &last))
			((t_token *)node->content)->toktype = DELIMITER;
		else if (ft_valid_infile_tok(node, &last))
			((t_token *)node->content)->toktype = INFILE;
		else if (ft_valid_outfile_tok(node, &last))
			((t_token *)node->content)->toktype = OUTFILE;
		else if (ft_valid_and_tok(node, &last))
			((t_token *)node->content)->toktype = AND;
		else if (ft_valid_or_tok(node, &last))
			((t_token *)node->content)->toktype = OR;
		else if (ft_valid_open_paren_tok(node, &last, &open_paren))
			((t_token *)node->content)->toktype = OPEN_PAREN;
		else if (ft_valid_close_paren_tok(node, &last, &open_paren))
			((t_token *)node->content)->toktype = CLOSE_PAREN;
		else if (ft_valid_arg_tok(node, &last))
			((t_token *)node->content)->toktype = ARG;
		else if (((t_token *)node->content)->toktype == RAW)
		{
			printf("unexcepted token: %s\n", ((t_token *)node->content)->str);
			return (PARSE_FAIL);
		}
		//ft_lstadd_front(&stack, node);
		last.toktype = ((t_token *)node->content)->toktype;
		node = node->next;
	}
	//ft_print_enum(last);
	//printf("\n");
	if (!ft_is_raw_tok(&last) && ft_is_redir_tok(&last))
	{
		printf("the last tok ");
		ft_print_enum(last.toktype);
		printf("\n");
		return (PARSE_FAIL);
	}
	if (ft_need_more_input(&last, open_paren))
		return (IMCOMPELETE_CMD);
	return (PARSE_OK);
}
