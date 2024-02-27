/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:33:21 by luyang            #+#    #+#             */
/*   Updated: 2024/02/27 19:24:45 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_program(char **args)
{
	char	*full_path;
	int		p_pid;
	int		status;

	if (!args || !*args)
		return (1); //error
	p_pid = fork();
	if (p_pid == -1)
		return (1); //error
	else if (p_pid == 0)
	{
		full_path = ft_getfullpath(args[0], NULL);
		if (!full_path)
			return (1); //error
		if (execve(full_path, args, ft_vars()->env) == -1)
			exit (status); //error
	}
	else
	{
		waitpid(p_pid, &status, 0);
		//WIFSIGNALED??
	}
	return (status);
}

int	ft_exec_redir(char **here_doc, char **redir)
{
	int	i;
	int	j;
	int	status;

	(free(NULL), i = 0, j = 0, status = 0);
	while (redir[i] && !status)
	{
		if (ft_is_here_doc(redir[i]))
			status = ft_here_doc(here_doc[j++]);
		else if (ft_is_input(redir[i]))
			status = ft_input(redir[i + 1]);
		else if (ft_is_output(redir[i]))
			status = ft_output(redir[i + 1]);
		else if (ft_is_append(redir[i]))
			status = ft_append(redir[i + 1]);
		i += 2;
	}
	return (status);
}

int	ft_exec_simple_cmd(t_cmd *cmd)
{
	int	original_io[2];
	int	status;

	original_io[0] = dup(STDIN_FILENO);
	original_io[1] = dup(STDOUT_FILENO);
	status = 0;
	if (!cmd)
		return (1); //handle error
	if (cmd->redirs[0])
	{
		if (ft_exec_redir(cmd->here_doc_files, cmd->redirs))
			return (ft_r_fd(original_io), close(original_io[0])
				, close(original_io[1]), 1); //error
	}
	if (cmd->args[0] && ft_is_builtin(cmd->args[0]))
		status = ft_exec_builtin(cmd->args);
	else if (cmd->args[0])
		status = ft_exec_program(cmd->args);
	ft_r_fd(original_io);
	close(original_io[0]);
	close(original_io[1]);
	return (status);
}

