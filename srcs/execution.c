#include "minishell.h"

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
	//clean?
	exit (status);
}

int	ft_exec_pipe(t_ast *ast)
{
	pid_t	l_pid;
	pid_t	r_pid;
	int	pfds[2];
	int	status;

	pipe(pfds);
	l_pid = fork();
	if (l_pid == 0)
		ft_exec_pipe_child(ast->left, LEFT_CHILD, pfds);
	else
	{
		r_pid = fork();
		if (r_pid == 0)
			ft_exec_pipe_child(ast->right, RIGHT_CHILD, pfds);
		else
		{
			close(pfds[0]);
			close(pfds[1]);
			waitpid(l_pid, &status, 0);
			waitpid(r_pid, &status, 0);
			return (status);
		}
	}
}

int	ft_exec_subshell(t_ast *ast)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (EXE_FAILURE);
	else if (pid == 0)
		ft_execute(ast);
	else
	{
		waitpid(pid, &status, 0);
		return (status);
	}
}

int	ft_execute(t_ast *ast)
{
	int	status;

	if (!ast)
		return (INVALID_POINTER);
	if (ast->toktype == PIPE)
		return (ft_exec_pipe(ast));
	else if (ast->toktype == AND)
	{
		status = ft_execute(ast->left);
		if (status == EXE_SUCCESS)
			return (ft_execute(ast->right));
		return (status);
	}
	else if (ast->toktype == OR)
	{
		status = ft_execute(ast->left);
		if (status == EXE_FAILURE)
			return (ft_execute(ast->right));
		return (status);
	}
	else if (ast->toktype == SUBSHELL)
		return (ft_exec_subshell(ast->left));
	else if (ast->toktype == SIMPLE_CMD)
		return (ft_execute_simple_cmd(ast->cmd));
}