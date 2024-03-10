/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:23:15 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/10 01:16:02 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_space_only(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i] == ' ')
		i++;
	if (str && !str[i])
		return (1);
	return (0);
}

void	ft_import_history(void)
{
	int		fd;
	char	*line;
	char	*trimmed_line;
	char	*path;

	path = ft_strjoin(ft_getenv("HOME"), HISTORY_FILE_NAME);
	fd = open(path, O_RDONLY);
	if (fd >= 0)
	{
		line = get_next_line(fd);
		trimmed_line = ft_strtrim(line, "\n");
		while (line)
		{
			add_history(trimmed_line);
			free(line);
			free(trimmed_line);
			line = get_next_line(fd);
			trimmed_line = ft_strtrim(line, "\n");
		}
		close(fd);
	}
	free(path);
}

void	ft_write_history(char *line)
{
	int		fd;
	char	*path;
	char	*line_with_newline;

	if (!(*line))
		return ;
	path = ft_strjoin(ft_getenv("HOME"), HISTORY_FILE_NAME);
	add_history(line);
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd >= 0)
	{
		line_with_newline = ft_strjoin(line, "\n");
		write(fd, line_with_newline, ft_strlen(line_with_newline));
		free(line_with_newline);
		close(fd);
	}
	free(path);
}
