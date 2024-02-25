/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:21:42 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/25 01:33:06 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char			*line;
	char			cwd[2000];
	//struct termios	ter;
	//t_list			*tokens;
	int				parse_res;
	char			*old_line;
	char			*old_mem;
	//t_ast			*ast;
	int				id;

	//tcgetattr(1, &ter);
	//ter.c_lflag |= ECHOCTL;
	//ter.c_lflag |= ICANON;t_list
	//tcsetattr(1, 0, &ter);
	argc += 0;
	argv += 0;
	env += 0;
	old_line = NULL;
	printf("current working path=%s\n", getcwd(cwd, 2000));
	ft_import_history();
	while (1)
	{
		parse_res = 2;
		while (parse_res == 2)
		{
			line = readline("42minishell>>> ");
			if (!line)
			{
				free(old_line);
				rl_clear_history();
				exit(0);
			}
			//printf("input=%s\n", line);
			if (!ft_space_only(line))
			{
				ft_trim_write_history(line);
				old_mem = line;
				line = ft_strjoin(old_line, line);
				free(old_mem);
				free(old_line);
				old_line = NULL;
				//printf("line=%s\n",line);
				ft_vars()->toklist = ft_tokenize(line);
				parse_res = ft_parse_token(ft_vars()->toklist);
				if (parse_res == PARSE_OK)
				{
					id = 0;
					//ft_print_tokens(ft_vars()->toklist);
					ft_vars()->ast = ft_build_ast(ft_vars()->toklist);
					//ft_print_ast(ft_vars()->ast);
					//printf("\n");
					ft_create_here_doc(ft_vars()->ast, &id);
					ft_vars()->last_exe_res = ft_execute(ft_vars()->ast);
					printf("%d\n", ft_vars()->last_exe_res);
					ft_free_ast(ft_vars()->ast);
				}
				else if (parse_res == IMCOMPELETE_CMD)
				{
					printf("need more input\n");
					old_line = line;
					ft_lstclear(&ft_vars()->toklist, &ft_free_token_node);
				}
				else if (parse_res == PARSE_FAIL)
				{	
					printf("parse error\n");
					ft_lstclear(&ft_vars()->toklist, &ft_free_token_node);
				}
			}
		}
		free(line);
	}
	return (0);
}