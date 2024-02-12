/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_tok4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:13:02 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/12 14:54:59 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_infile_tok(t_token_type t)
{
	return (t == INFILE);
}

int	ft_is_outfile_tok(t_token_type t)
{
	return (t == OUTFILE);
}
