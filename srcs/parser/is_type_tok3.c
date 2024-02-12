/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_tok3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:10:57 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/12 14:54:55 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_or_tok(t_token_type t)
{
	return (t == OR);
}

int	ft_is_redir_tok(t_token_type t)
{
	return (ft_is_here_doc_tok(t)
		|| ft_is_input_tok(t)
		|| ft_is_output_tok(t)
		|| ft_is_append_tok(t));
}

int	ft_is_arg_tok(t_token_type t)
{
	return (t == ARG);
}

int	ft_is_delimiter_tok(t_token_type t)
{
	return (t == DELIMITER);
}
