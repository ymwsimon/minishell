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
