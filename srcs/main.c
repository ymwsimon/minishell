/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:21:42 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/11 18:32:43 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char			*line;
	char			cwd[2000];
	//struct termios	ter;
	t_list			*cmds;
	t_list			*tokens;
	int				parse_res;
	char			*old_line;
	char			*old_mem;

	//tcgetattr(1, &ter);
	//ter.c_lflag |= ECHOCTL;
	//ter.c_lflag |= ICANON;t_list
	//tcsetattr(1, 0, &ter);
	argc += 0;
	argv += 0;
	env += 0;
	cmds = 0;
	cmds += 0;
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
				exit(0);
			}
			printf("input=%s\n", line);
			if (ft_strlen(line))
			{
				ft_trim_write_history(&line);
				old_mem = line;
				line = ft_strjoin(old_line, line);
				free(old_mem);
				free(old_line);
				old_line = NULL;
				printf("line=%s\n",line);
				tokens = ft_tokenize(line);
				parse_res = ft_parse_token(tokens);
				if (parse_res == PARSE_OK)
				{
					ft_print_tokens(tokens);

				}
				else if (parse_res == IMCOMPELETE_CMD)
				{
					printf("need more input\n");
					old_line = line;
				}
				else if (parse_res == PARSE_FAIL)
					printf("parse error\n");
				ft_lstclear(&tokens, &ft_free_token_node);
			}
		}
		free(line);
	}
	return (0);
}