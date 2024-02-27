/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:54:28 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/27 18:05:02 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getfullpath(char *pname, char *res)
{
	int		i;
	char	**paths;

	i = 0;
	if (pname && ((pname[0] == '/') || pname[0] == '.'))
		return (ft_strdup(pname));
	paths = ft_split(ft_getenv("PATH"), ':');
	if (!paths)
		return (NULL);
	pname = ft_strjoin("/", pname);
	if (!pname)
		return (ft_clear_char_arr(paths), NULL);
	i = 0;
	while (paths[i])
	{
		res = ft_strjoin(paths[i], pname);
		if (!res)
			return (ft_clear_char_arr(paths), free(pname), NULL);
		if (!access(res, F_OK | X_OK))
			return (ft_clear_char_arr(paths), free(pname), res);
		free(res);
		i++;
	}
	return (ft_clear_char_arr(paths), free(pname), NULL);
}
