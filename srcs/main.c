/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:21:42 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/11 16:23:39 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	int				id;

	ft_vars()->env = ft_cpy_env(__environ);
	ft_import_history();
	ft_redir_file_arg(argc, argv);
	while (TRUE)
	{
		id = 0;
		if (ft_get_user_input() == PARSE_OK
			&& ft_build_ast(&ft_vars()->ast, ft_vars()->toklist) == EXE_SUCCESS
			&& ft_create_here_doc(ft_vars()->ast, &id) == EXE_SUCCESS
			&& ft_fill_here_doc(ft_vars()->ast) == EXE_SUCCESS
			&& ft_setup_signal_handler_child(FALSE) == EXE_SUCCESS)
			ft_vars()->last_exe_res = ft_execute(ft_vars()->ast);
		if (ft_vars()->exe_stop_by_sig == SIGINT)
			printf("\n");
		if (ft_vars()->exe_stop_by_sig == SIGQUIT && ft_vars()->last_exe_res)
			printf("Quit (core dumped)\n");
		ft_free_ast(&ft_vars()->ast, TRUE);
		ft_vars()->toklist = NULL;
		if (!isatty(STDIN_FILENO))
			break ;
	}
	ft_free_res(TRUE);
	return (EXE_SUCCESS);
}
