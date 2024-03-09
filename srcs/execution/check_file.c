/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:08:37 by luyang            #+#    #+#             */
/*   Updated: 2024/03/09 20:12:02 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_err	ft_check_read(char *file)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK) == -1)
			return ((t_err){EFD_GENERAL, ERR_PERM_DENIED, file});
		return ((t_err){EFD_SUCCESS, 42, NULL});
	}
	return ((t_err){EFD_NOT_FOUND, ERR_NO_SUCH_FILE, file});
}

t_err	ft_check_write(char *file)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return ((t_err){EFD_GENERAL, ERR_PERM_DENIED, file});
		return ((t_err){EFD_SUCCESS, 42, NULL});
	}
	return ((t_err){EFD_NOT_FOUND, ERR_NO_SUCH_FILE, file});
}

int	ft_check_dir(char *file, int need_slash)
{
	DIR	*directory;
	int	i;

	i = 0;
	while (file[i])
	{
		i++;
	}
	if (file[i - 1] == '/' || (file[0] == '.'
			&& file[1] == '/') || !need_slash)
	{
		directory = opendir(file);
		if (directory)
			return (closedir(directory), 1);
	}
	return (0);
}

t_err	ft_check_exec(char *path, char *file, int need_slash)
{
	if (ft_check_dir(file, need_slash))
		return ((t_err){EFD_EXEC, ERR_IS_DIR, file});
	if (!path || !ft_strncmp(path, "..", 3))
		return ((t_err){EFD_NOT_FOUND, ERR_CMD_NOT_FOUND, file});
	if (!*file)
		return ((t_err){EFD_NOT_FOUND, ERR_CMD_NOT_FOUND, "\'\'"});
	if (!ft_strncmp(path, ".", 2))
		return ((t_err){2, ERR_SINGLE_DOT, file});
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == -1)
			return ((t_err){EFD_EXEC, ERR_PERM_DENIED, path});
		return ((t_err){EFD_SUCCESS, 42, NULL});
	}
	return ((t_err){EFD_NOT_FOUND, ERR_NO_SUCH_FILE, path});
}
