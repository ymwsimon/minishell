/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:54:28 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/18 21:57:27 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getfullpath(char *pname, char *res)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	if (pname && ((pname[0] == '/') || pname[0] == '.'))
		return (ft_strdup(pname));
	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	pname = ft_strjoin("/", pname);
	if (!pname)
		return (ft_clear_char_arr(paths), NULL);
	i = 0;
	while (paths[i])
	{
		res = ft_strjoin(paths[i], pname);
		//printf("fullpath:%s\n", res);
		if (!access(res, F_OK | X_OK))
			return (ft_clear_char_arr(paths), free(pname), res);
		free(res);
		i++;
	}
	return (ft_clear_char_arr(paths), free(pname), NULL);
}