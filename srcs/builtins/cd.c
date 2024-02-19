#include "../../includes/minishell.h"

char	*ft_path_prefix(char *path)
{
	char	*res;

	res = NULL;
	return (res);
}

int ft_cd(char **args)
{
    char    *path;
	char	cwd[2000];

    if (ft_char_arr_size(args) > 2)
   {
        ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
        return (1);
    }
	printf("%s\n", getenv("HOME"));
	//path = NULL;
    if (ft_char_arr_size(args) == 1)
    {
		if (chdir(getenv("HOME")))
		{
    		//perror("cannot change to home directory\n");
        	return (1);
		}
		else
			return (0);
	}
	path = args[1];
	if (args[1][0] != '/')
	{
		getcwd(cwd, 2000);
		ft_strlcpy(&cwd[ft_strlen(cwd)], "/", 2);
		path = ft_strjoin(cwd, args[1]);
	}
	ft_putstr_fd(path, STDERR_FILENO);
	if (chdir(path))
	{
		perror(strerror(errno));
		return (1);
	}
    return (0);
}