/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_tok2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:08:34 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/12 14:54:51 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_here_doc_tok(t_token_type t)
{
	return (t == HERE_DOC);
}

int	ft_is_input_tok(t_token_type t)
{
	return (t == INPUT);
}

int	ft_is_output_tok(t_token_type t)
{
	return (t == OUTPUT);
}

int	ft_is_append_tok(t_token_type t)
{
	return (t == APPEND);
}

int	ft_is_and_tok(t_token_type t)
{
	return (t == AND);
}
