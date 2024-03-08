/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:21:42 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/08 16:57:20 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	int				id;

	argc += 0;
	argv += 0;
	env += 0;
	ft_vars()->env = ft_cpy_env(__environ);
	ft_import_history();
	while (TRUE)
	{
		if (ft_get_user_input() == PARSE_OK
			&& ft_build_ast(&ft_vars()->ast, ft_vars()->toklist) == EXE_SUCCESS
			&& ft_create_here_doc(ft_vars()->ast, &id) == EXE_SUCCESS
			&& ft_fill_here_doc(ft_vars()->ast) == EXE_SUCCESS
			&& ft_setup_signal_handler_child(FALSE) == EXE_SUCCESS)
			ft_vars()->last_exe_res = ft_execute(ft_vars()->ast);
		ft_free_ast(&ft_vars()->ast, TRUE);
		printf("last execution result: %d\n", ft_vars()->last_exe_res);
		if (!isatty(STDIN_FILENO))
			break ;
	}
	ft_free_res(1);
	return (0);
}

		/*
		if (ft_get_user_input() == PARSE_OK)
		{
			id = ft_build_ast(&ft_vars()->ast, ft_vars()->toklist);
			if (!id)
			{
				ft_print_ast(ft_vars()->ast);
				printf("\n");
			}
			id = 0;
			if (!ft_vars()->ast)
				printf("empty ast\n");
			id = ft_create_here_doc(ft_vars()->ast, &id);
			printf("create hd %d\n", id);
			if (id == 0)
				id = ft_fill_here_doc(ft_vars()->ast);
			printf("fill hd %d\n", id);
			ft_setup_signal_handler_child(0);
			if (id == 0)
			{
				ft_vars()->last_exe_res = ft_execute(ft_vars()->ast);
				printf("last execution result: %d\n", ft_vars()->last_exe_res);
			}
			ft_free_ast(&ft_vars()->ast, 1);
			ft_vars()->toklist = NULL;
		}
		//else
		//	printf("parse error\n");
		*/