/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luyang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:33:21 by luyang            #+#    #+#             */
/*   Updated: 2024/02/16 16:45:03 by luyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exec_program(char **args)
{
}


int	ft_exec_redir2(char **redir, int *i)
{
	int	fd;
	
	if(ft_is_output(redir[(*i)++]))
	{
		fd = open(redir[(*i)++], O_WRONLY | O_TRUNC
				| O_CREAT, 0644);
		if (fd == -1)
			return (1); //error
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (ft_is_append(redir[(*i)++]))
	{
		fd = open(redir[(*i)++], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		if (fd == -1)
			return (1), //error
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
	else
		return (1);//error
	return (0);
}

int	ft_exec_redir(char **here_doc, char **redir, int *i, int *j)
{
	int	fd;

	if (ft_is_here_doc(redir[(*i)++]))
	{
		fd = open(here_doc[(*j)++], O_RDONLY);
		if (fd == -1)
			return (-1); //error
		dup2(fd, STDIN_FILENO);
		close(fd);
		(*i)++;
	}
	else if (ft_is_input(redir[(*i)++]))
	{
		fd = open(redir[(*i)++], O_RDONLY);
		if (fd == -1)
			return (-1);//error
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else 
		return (ft_exec_redir2(redir, i));
}

int	ft_exec_simple_cmd(t_ast *ast)
{
	int	i;
	int	j;
	int	original_io[2];

	original_io[0] = dup(STDIN_FILENO);
	original_io[1] = dup(STDOUT_FILENO);
	(i = 0, j == 0);
	if (!ast)
		return (1); //handle error
	while (ast->cmd->redirs[i])
	{
		if (ft_exec_redir(ast->cmd->here_doc_files,
			       ast->cmd->redirs, &i, &j))
			return (1); //error
	}
	if (ast->cmd->args[0] && ft_is_builtin(ast->cmd->args[0]))
		ft_exec_builtin(ast->cmd->args);
	else if (ast->cmd->args[0])
		ft_exec_program(ast->cmd->args);
	ft_r_fd(original_io);
}

