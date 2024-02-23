#include "../../includes/minishell.h"

int	ft_here_doc(char *here_doc)
{
	int	fd;
	fd = open(here_doc, O_RDONLY);
	if (fd == -1)
		return (ft_err_msg(ft_check_read(here_doc))); //error
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_input(char *redir)
{
	int	fd;

	if (!redir || !*redir)
		return(1);
	fd = open(redir, O_RDONLY);
	if (fd == -1)
		return (ft_err_msg(ft_check_read(redir)));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_output(char *redir)
{
	int fd;

	fd = open(redir, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (ft_err_msg(ft_check_write(redir))); //error
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ft_append(char *redir)
{
	int fd;

	fd = open(redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ft_err_msg(ft_check_write(redir))); //error
	dup2(fd, STDOUT_FILENO);
	close (fd);
	return (0);
}