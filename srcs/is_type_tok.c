/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:05:22 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/11 18:08:13 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_double_quote_tok(t_token_type t)
{
	return (t == OPEN_DOUBLE_QUOTE);
}

int	ft_is_single_quote_tok(t_token_type t)
{
	return (t == OPEN_SINGLE_QUOTE);
}

int	ft_is_open_paren_tok(t_token_type t)
{
	return (t == OPEN_PAREN);
}

int	ft_is_close_paren_tok(t_token_type t)
{
	return (t == CLOSE_PAREN);
}

int	ft_is_pipe_tok(t_token_type t)
{
	return (t == PIPE);
}
