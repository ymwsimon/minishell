/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_tok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:05:22 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/13 11:37:06 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_double_quote_tok(t_token *t)
{
	return (t->toktype == OPEN_DOUBLE_QUOTE);
}

int	ft_is_single_quote_tok(t_token *t)
{
	return (t->toktype == OPEN_SINGLE_QUOTE);
}

int	ft_is_open_paren_tok(t_token *t)
{
	return (t->toktype == OPEN_PAREN);
}

int	ft_is_close_paren_tok(t_token *t)
{
	return (t->toktype == CLOSE_PAREN);
}

int	ft_is_pipe_tok(t_token *t)
{
	return (t->toktype == PIPE);
}
