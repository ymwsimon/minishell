/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:06:31 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/09 20:28:04 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_cd_error_message(char *dir)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(dir, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else if (errno == ENOTDIR)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(dir, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(dir, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
}

char	*ft_resolve_folder_path(char *path)
{
	char	*res;

	res = NULL;
	if (path && path[0] == '~')
	{
		res = ft_getenv("HOME");
		if (!res)
			return (NULL);
		res = ft_strjoin(res, path + 1);
	}
	else if (path && (path[0] == '/'
			|| !ft_strncmp(path, ".", 2) || !ft_strncmp(path, "..", 3)))
		res = ft_strdup(path);
	else
	{
		res = ft_free_join_str(getcwd(NULL, 0), ft_strdup("/"));
		if (!res)
			return (NULL);
		res = ft_free_join_str(res, ft_strdup(path));
	}
	return (res);
}

int	ft_cd(char **args)
{
	char	*path;

	if (ft_char_arr_size(args) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (ft_char_arr_size(args) == 1)
	{
		if (chdir(ft_getenv("HOME")))
			return (perror("cannot change to home directory\n"), 1);
		return (0);
	}
	path = ft_resolve_folder_path(args[1]);
	if (chdir(path))
	{
		ft_print_cd_error_message(args[1]);
		return (free(path), 1);
	}
	return (free(path), 0);
}
