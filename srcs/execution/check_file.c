#include "../../includes/minishell.h"

t_err	ft_check_read(char *file)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK) == -1)
			return ((t_err){EFD_GENERAL, ERR_PERM_DENIED, file});
		return ((t_err){EFD_SUCCESS, 3, NULL});
	}
	return ((t_err){EFD_NOT_FOUND, ERR_NO_SUCH_FILE, file});
}

t_err	ft_check_write(char *file)
{
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return ((t_err){EFD_GENERAL, ERR_PERM_DENIED, file});
		return ((t_err){EFD_SUCCESS, 3, NULL});
	}
	return ((t_err){EFD_NOT_FOUND, ERR_NO_SUCH_FILE, file});
}

t_err	ft_check_exec(char *path, char *file)
{
	if (!path)
		return ((t_err){EFD_NOT_FOUND, ERR_CMD_NOT_FOUND, file});
	if (access(path,F_OK) == 0)
	{
		if (access(path, X_OK) == -1)
			return ((t_err){EFD_EXEC, ERR_PERM_DENIED, path});
		return ((t_err){EFD_SUCCESS, 3, NULL});
	}		
	return ((t_err){EFD_NOT_FOUND, ERR_NO_SUCH_FILE, path});
}
