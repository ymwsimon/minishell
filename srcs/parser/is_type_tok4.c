/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_tok4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:13:02 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/10 10:48:54 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_infile_tok(t_token *t)
{
	return (t->toktype == INFILE);
}

int	ft_is_outfile_tok(t_token *t)
{
	return (t->toktype == OUTFILE);
}

int	ft_is_raw_tok(t_token *t)
{
	return (t->toktype == RAW);
}

int	ft_is_open_quote(t_token *t)
{
	return (ft_is_double_quote_tok(t)
		|| ft_is_single_quote_tok(t));
}
