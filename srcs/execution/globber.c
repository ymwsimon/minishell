/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:36:20 by luyang            #+#    #+#             */
/*   Updated: 2024/03/04 16:39:57 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_globbing(char *arg)
{
	
}

char	**ft_globber(char **args)
{
	int		n_args;
	char	***globbed;
	int		i;

	i = 0;
	n_args = ft_count_args(args);
	globbed = ft_calloc(n_args + 1, sizeof(char **));
	while (args[i])
	{
		globbed[i] = ft_globbing(args[i]);
	}
}
