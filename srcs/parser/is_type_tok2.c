/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_tok2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:08:34 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/13 11:37:51 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_here_doc_tok(t_token *t)
{
	return (t->toktype == HERE_DOC);
}

int	ft_is_input_tok(t_token *t)
{
	return (t->toktype == INPUT);
}

int	ft_is_output_tok(t_token *t)
{
	return (t->toktype == OUTPUT);
}

int	ft_is_append_tok(t_token *t)
{
	return (t->toktype == APPEND);
}

int	ft_is_and_tok(t_token *t)
{
	return (t->toktype == AND);
}
