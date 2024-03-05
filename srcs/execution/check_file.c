/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:08:37 by luyang            #+#    #+#             */
/*   Updated: 2024/03/05 18:08:40 by luyang           ###   ########.fr       */
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

int	ft_check_dir(char *file)
{
	DIR	*directory;
	int	i;

	i = 0;
	while (file[i])
	{
		i++;
	}
	if (file[i - 1] == '/' || (file[0] == '.'
			&& file[1] == '/'))
	{
		directory = opendir(file);
		if (directory)
			return (closedir(directory), 1);
	}
	return (0);
}

t_err	ft_check_exec(char *path, char *file)
{
	if (ft_check_dir(file))
		return ((t_err){EFD_EXEC, ERR_IS_DIR, file});
	if (!path)
		return ((t_err){EFD_NOT_FOUND, ERR_CMD_NOT_FOUND, file});
	if (!*file)
		return ((t_err){EFD_NOT_FOUND, ERR_CMD_NOT_FOUND, "\'\'"});
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == -1)
			return ((t_err){EFD_EXEC, ERR_PERM_DENIED, path});
		return ((t_err){EFD_SUCCESS, 42, NULL});
	}
	return ((t_err){EFD_NOT_FOUND, ERR_NO_SUCH_FILE, path});
}
