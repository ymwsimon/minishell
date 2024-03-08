/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:22:58 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/08 19:51:57 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_get_user_input(char **old_line, int *parse_res)
{
	signal(SIGINT, &ft_signal_handler_waiting_input);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = ft_event;
	if (old_line)
		*old_line = NULL;
	if (parse_res)
		*parse_res = NO_PARSE_RESULT;
	ft_vars()->break_readline = FALSE;
}

void	ft_exit_shell(char **old_line)
{
	if (old_line)
		free(*old_line);
	printf("exit\n");
	ft_free_res(TRUE);
	exit(ft_vars()->last_exe_res);
}

int	ft_process_line(char **line, char **old_line, int *parse_res)
{
	ft_trim_write_history(*line);
	if (*old_line)
	{
		*line = ft_free_join_str(ft_strdup("\n"), *line);
		if (!(*line))
			return (ALLOCATE_FAIL);
		*line = ft_free_join_str(*old_line, *line);
	}
	if (!(*line))
		return (ALLOCATE_FAIL);
	ft_vars()->toklist = ft_tokenize(*line);
	if (!ft_vars()->toklist)
		return (free(*old_line), free(*line), ALLOCATE_FAIL);
	*parse_res = ft_parse_token(ft_vars()->toklist);
	if (*parse_res == IMCOMPELETE_CMD)
	{
		*old_line = *line;
		*line = NULL;
		ft_lstclear(&ft_vars()->toklist, &ft_free_token_node);
	}
	return (EXE_SUCCESS);
}

void	ft_cleanup(char *line, char *old_line, int parse_res)
{
	free(line);
	if (ft_vars()->break_readline)
	{
		parse_res = EMPTY_INPUT;
		free(old_line);
	}
	if (parse_res == PARSE_FAIL || parse_res == EMPTY_INPUT)
	{
		ft_lstclear(&ft_vars()->toklist, &ft_free_token_node);
		ft_vars()->toklist = NULL;
	}
}

int	ft_get_user_input(void)
{
	char	*line;
	char	*old_line;
	int		parse_res;

	ft_init_get_user_input(&old_line, &parse_res);
	line = readline(PROMPT);
	while (!ft_vars()->break_readline
		&& (parse_res == NO_PARSE_RESULT || parse_res == IMCOMPELETE_CMD))
	{
		if (!line && (parse_res == NO_PARSE_RESULT))
			ft_exit_shell(&old_line);
		if (!line && (parse_res == IMCOMPELETE_CMD))
			return (ft_putstr_fd("unexpected EOF\n", STDERR_FILENO),
				PARSE_FAIL);
		if ((!ft_space_only(line) || parse_res == IMCOMPELETE_CMD)
			&& (ft_process_line(&line, &old_line, &parse_res)))
			return (ALLOCATE_FAIL);
		else if (ft_space_only(line) && parse_res == NO_PARSE_RESULT)
			return (free(line), EMPTY_INPUT);
		if (parse_res == IMCOMPELETE_CMD)
			line = readline(PROMPT_CON);
	}
	ft_cleanup(line, old_line, parse_res);
	return (parse_res);
}
