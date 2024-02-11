/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:46:40 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/11 21:16:20 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_astnode	*ft_build_ast(t_list *tokens)
{
	t_astnode	*tree;
	t_list		*iter;

	if (!tokens)
		return (NULL);
	iter = tokens;
	while (iter)
	{

	}
	return (tree);
}
