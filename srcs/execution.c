#include "minishell.h"

int	ft_execute(t_ast **ast)
{
	if (!ast || !*ast)
		return (INVALID_POINTER);
	if ((*ast)->toktype == PIPE)
	{
		
	}
	else if ((*ast)->toktype == AND)
	{
		if (ft_execute(&(*ast)->left) == EXE_SUCCESS)
			return (ft_execute(&(*ast)->right));
		return (EXE_FAILURE);
		
	}
	else if ((*ast)->toktype == OR)
	{
		if (ft_exedcute(&(*ast)->left) == EXE_FAILURE)
			return (ft_execute(&(*ast)->right));
		return (EXE_FAILURE);
	}
	else if ((*ast)->toktype == SUBSHELL)
	{
		(*ast) = (*ast)->left;
		ft_exe_subshell(ast);
	}
	else if ((*ast)->toktype == SIMPLE_CMD)
		return (ft_execute_simple_cmd(ast));
}