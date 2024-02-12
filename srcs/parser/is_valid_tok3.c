/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_tok3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:20:08 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/12 18:00:32 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_valid_open_paren_tok(t_list *node, t_token_type tok, int *open_par)
{
	if (ft_is_open_paren(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->toktype == RAW
		&& (!tok || ft_is_pipe_tok(tok) || ft_is_and_tok(tok)
			|| ft_is_or_tok(tok) || ft_is_open_paren_tok(tok)))
	{
		*open_par += 1;
		return (1);
	}
	return (0);
}

int	ft_valid_close_paren_tok(t_list *node, t_token_type tok, int *open_par)
{
	if (ft_is_close_paren(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->toktype == RAW
		&& *open_par > 0
		&& (!ft_is_redir_tok(tok))
		&& (!ft_is_pipe_tok(tok))
		&& (ft_is_arg_tok(tok) || ft_is_outfile_tok(tok)
			|| ft_is_delimiter_tok(tok) || ft_is_infile_tok(tok)
			|| ft_is_close_paren_tok(tok)))
	{
		*open_par -= 1;
		return (1);
	}
	return (0);
}

int	ft_valid_or_tok(t_list *node, t_token_type tok)
{
	return (ft_is_or(((t_token *)node->content)->str)
		&& ((t_token *)node->content)->toktype == RAW
		&& (ft_is_infile_tok(tok) || ft_is_outfile_tok(tok)
			|| ft_is_close_paren_tok(tok) || ft_is_arg_tok(tok)));
}
