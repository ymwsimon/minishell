/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:21:42 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/06 01:24:57 by mayeung          ###   ########.fr       */
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
	while (1)
	{
		if (ft_get_user_input() == PARSE_OK)
		{
			ft_vars()->ast = ft_build_ast(ft_vars()->toklist);
			id = 0;
			if (!ft_vars()->ast)
				printf("empty ast\n");
			id = ft_create_here_doc(ft_vars()->ast, &id);
			//printf("create hd %d\n", id);
			if (id == 0)
				id = ft_fill_here_doc(ft_vars()->ast);
			//printf("fill hd %d\n", id);
			if (id == 0)
			{
				ft_vars()->last_exe_res = ft_execute(ft_vars()->ast);
				printf("%d\n", ft_vars()->last_exe_res);
			}
			ft_free_ast(&ft_vars()->ast, 1);
			ft_vars()->ast = NULL;
			ft_vars()->toklist = NULL;
		}
	}
	ft_free_res(1);
	return (0);
}
