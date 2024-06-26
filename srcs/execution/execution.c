/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:32:57 by luyang            #+#    #+#             */
/*   Updated: 2024/03/11 17:04:53 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_pipe_child(t_ast *ast, int child, int *pfds)
{
	int	status;

	if (child == LEFT_CHILD)
	{
		close(pfds[0]);
		dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	if (child == RIGHT_CHILD)
	{
		close(pfds[1]);
		dup2(pfds[0], STDIN_FILENO);
		close(pfds[0]);
	}
	status = ft_execute(ast);
	ft_free_res(FALSE);
	exit (status);
}

int	ft_exec_pipe(t_ast *ast, int status)
{
	pid_t	l_pid;
	pid_t	r_pid;
	int		pfds[2];

	(pipe(pfds), l_pid = fork());
	if (l_pid == 0)
	{
		status = (ft_exec_pipe_child(ast->left, LEFT_CHILD, pfds));
		(ft_free_res(FALSE), exit(status));
	}
	else
	{
		r_pid = fork();
		if (r_pid == 0)
		{
			status = (ft_exec_pipe_child(ast->right, RIGHT_CHILD, pfds));
			(ft_free_res(FALSE), exit(status));
		}
		else
		{
			(ft_setup_signal_handler_parent(), close(pfds[0]), close(pfds[1]),
				waitpid(l_pid, &status, 0), waitpid(r_pid, &status, 0));
			return (ft_get_exit_status(status));
		}
	}
}

int	ft_exec_subshell(t_ast *ast)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (EXE_FAILURE);
	else if (pid == 0)
	{
		status = (ft_execute(ast));
		ft_free_res(FALSE);
		exit(status);
	}
	else
	{
		ft_setup_signal_handler_parent();
		waitpid(pid, &status, 0);
		return (ft_get_exit_status(status));
	}
}

int	ft_execute(t_ast *ast)
{
	int	status;

	if (!ast)
		return (INVALID_POINTER);
	if (ast->toktype == PIPE)
		return (ft_exec_pipe(ast, 0));
	else if (ast->toktype == AND || ast->toktype == OR)
	{
		status = ft_execute(ast->left);
		if (ast->toktype == AND && status == EXE_SUCCESS)
			return (ft_execute(ast->right));
		if (ast->toktype == OR && ft_vars()->exe_stop_by_sig == SIGQUIT)
			printf("Quit (core dumped)\n");
		if (ast->toktype == OR && status > EXE_SUCCESS
			&& status != SIGINT_CODE)
			return (ft_execute(ast->right));
		return (status);
	}
	else if (ast->toktype == SUBSHELL)
		return (ft_exec_subshell(ast->left));
	else if (ast->toktype == SIMPLE_CMD)
		return (ft_exec_simple_cmd(ast->cmd));
	return (EXE_GENERAL);
}
