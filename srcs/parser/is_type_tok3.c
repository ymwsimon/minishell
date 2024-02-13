/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_tok3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:10:57 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/13 11:38:28 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_or_tok(t_token *t)
{
	return (t->toktype == OR);
}

int	ft_is_redir_tok(t_token *t)
{
	return (ft_is_here_doc_tok(t)
		|| ft_is_input_tok(t)
		|| ft_is_output_tok(t)
		|| ft_is_append_tok(t));
}

int	ft_is_arg_tok(t_token *t)
{
	return (t->toktype == ARG);
}

int	ft_is_delimiter_tok(t_token *t)
{
	return (t->toktype == DELIMITER);
}
