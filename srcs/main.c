/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:21:42 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/03 22:53:48 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	int				parse_res;
	int				id;

	argc += 0;
	argv += 0;
	env += 0;
	ft_vars()->env = ft_cpy_env(__environ);
	ft_import_history();
	while (1)
	{
		parse_res = ft_get_user_input();
		if (parse_res == PARSE_OK)
		{
			ft_vars()->ast = ft_build_ast(ft_vars()->toklist);
			id = 0;
			if (ft_create_here_doc(ft_vars()->ast, &id) == 0)
			{
				ft_vars()->last_exe_res = ft_execute(ft_vars()->ast);
				printf("%d\n", ft_vars()->last_exe_res);
			}
			ft_free_ast(ft_vars()->ast);
			ft_vars()->ast = NULL;
			ft_vars()->toklist = NULL;
		}
		else if (parse_res == PARSE_FAIL)
			printf("parse error\n");
	}
	ft_free_res();
	return (0);
}