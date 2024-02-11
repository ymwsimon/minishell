/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:14:30 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/11 23:03:45 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_valid_pipe_tok(t_list *node, t_token_type tok)
{
	return (ft_is_pipe(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->tok == RAW
		&& (ft_is_close_paren_tok(tok) || ft_is_infile_tok(tok)
			|| ft_is_outfile_tok(tok) || ft_is_arg_tok(tok)));
}

int	ft_valid_input_tok(t_list *node, t_token_type tok)
{
	return (ft_is_input(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->tok == RAW
		&& (!tok || (!ft_is_redir_tok(tok) && !ft_is_close_paren_tok(tok))));
}

int	ft_valid_output_tok(t_list *node, t_token_type tok)
{
	return (ft_is_output(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->tok == RAW
		&& (!tok || (!ft_is_redir_tok(tok) && !ft_is_close_paren_tok(tok))));
}

int	ft_valid_here_doc_tok(t_list *node, t_token_type tok)
{
	return (ft_is_here_doc(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->tok == RAW
		&& (!tok || (!ft_is_redir_tok(tok) && !ft_is_close_paren_tok(tok))));
}

int	ft_valid_append_tok(t_list *node, t_token_type tok)
{
	return (ft_is_append(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->tok == RAW
		&& (!tok || (!ft_is_redir_tok(tok) && !ft_is_close_paren_tok(tok))));
}
