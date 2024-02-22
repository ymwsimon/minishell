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

#include "../../includes/minishell.h"

int	ft_exec_program(char **args)
{
	char	*full_path;
	int	p_pid;
	int	status;

	if (!args || !*args)
		return (1); //error
	p_pid = fork();
	if (p_pid == -1)
		return (1); //error
	else if (p_pid == 0)
	{
		full_path = NULL;
		ft_getfullpath(args[0], full_path);
		if (!full_path)
			return (1); //error
		args[0] = full_path;
		if (execve(full_path, args, NULL) == -1)
			exit(status); //error
	}
	else
	{
		waitpid(p_pid, &status, 0);
		//WIFSIGNALED??
	}
	return (0);
}

int	ft_exec_redir(char **here_doc, char **redir)
{
	int	i;
	int	j;
	int	status;

	(i = 0, j = 0, status = 0);
	while (redir[i] && !status)
	{
		if (ft_is_here_doc(redir[i++]))
		{
			status = ft_here_doc(here_doc[j++]);
			i++;
		}
		else if (ft_is_input(redir[i++]))
			status = ft_input(redir[i++]);
		else if (ft_is_output(redir[i++]))
			status = ft_output(redir[i++]);
		else if (ft_is_append(redir[i++]))
			status = ft_append(redir[i++]);
	}
	return (status);
}

int	ft_exec_simple_cmd(t_cmd *cmd)
{
	int	original_io[2];

	original_io[0] = dup(STDIN_FILENO);
	original_io[1] = dup(STDOUT_FILENO);
	if (!cmd)
		return (1); //handle error
	if (cmd->redirs[0])
	{
		if (ft_exec_redir(cmd->here_doc_files, cmd->redirs))
			return (1); //error
	}
	//if (ast->cmd->args[0] && ft_is_builtin(ast->cmd->args[0]))
	//	return (ft_exec_builtin(ast->cmd->args));
	if (cmd->args[0])
		return (ft_exec_program(cmd->args));
	ft_r_fd(original_io);
	return (0);
}

