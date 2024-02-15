/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_tok2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:16:28 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/14 19:24:24 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_valid_infile_tok(t_list *node, t_token *tok)
{
	return (!ft_is_pipe(((t_token *)node->content)->str)
		&& !ft_is_redir(((t_token *)node->content)->str)
		&& !ft_is_and(((t_token *)node->content)->str)
		&& !ft_is_or(((t_token *)node->content)->str)
		&& !ft_is_open_paren(((t_token *)node->content)->str)
		&& !ft_is_close_paren(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->toktype == RAW
		&& ft_is_input_tok(tok));
}

int	ft_valid_delimiter_tok(t_list *node, t_token *tok)
{
	return (!ft_is_pipe(((t_token *)node->content)->str)
		&& !ft_is_redir(((t_token *)node->content)->str)
		&& !ft_is_and(((t_token *)node->content)->str)
		&& !ft_is_or(((t_token *)node->content)->str)
		&& !ft_is_open_paren(((t_token *)node->content)->str)
		&& !ft_is_close_paren(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->toktype == RAW
		&& ft_is_here_doc_tok(tok));
}

int	ft_valid_outfile_tok(t_list *node, t_token *tok)
{
	return (!ft_is_pipe(((t_token *)node->content)->str)
		&& !ft_is_redir(((t_token *)node->content)->str)
		&& !ft_is_and(((t_token *)node->content)->str)
		&& !ft_is_or(((t_token *)node->content)->str)
		&& !ft_is_open_paren(((t_token *)node->content)->str)
		&& !ft_is_close_paren(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->toktype == RAW
		&& (ft_is_append_tok(tok) || ft_is_output_tok(tok)));
}

int	ft_valid_and_tok(t_list *node, t_token *tok)
{
	return (ft_is_and(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->toktype == RAW
		&& (ft_is_infile_tok(tok) || ft_is_outfile_tok(tok)
			|| ft_is_close_paren_tok(tok) || ft_is_delimiter_tok(tok)
			|| ft_is_arg_tok(tok)));
}

int	ft_valid_arg_tok(t_list *node, t_token *tok)
{
	return (!ft_is_pipe(((t_token *)node->content)->str)
		&& !ft_is_redir(((t_token *)node->content)->str)
		&& !ft_is_and(((t_token *)node->content)->str)
		&& !ft_is_or(((t_token *)node->content)->str)
		&& !ft_is_open_paren(((t_token *)node->content)->str)
		&& !ft_is_close_paren(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->toktype == RAW
		&& (ft_is_raw_tok(tok) || !ft_is_redir_tok(tok))
		&& !ft_invalid_tok(node));
}
