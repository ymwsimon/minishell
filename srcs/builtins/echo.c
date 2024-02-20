/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:09:45 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/20 18:09:45 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	size_t	i;
	char	*line;

	i = 1 + (args[1] && !ft_strncmp(args[1], "-n", 3));
	line = ft_strdup("");
	if (!line)
		return (1);
	while (args[i])
	{
		line = ft_free_join_str(line, ft_strdup(args[i]));
		if (!line)
			return (1);
		if (args[i + 1])
		{
			line = ft_free_join_str(line, ft_strdup(" "));
			if (!line)
				return (1);
		}
		i++;
	}
	printf("%s", line);
	free(line);
	if (args[1] && ft_strncmp(args[1], "-n", 3))
		printf("\n");
	return (0);
}
