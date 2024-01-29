/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:21:42 by mayeung           #+#    #+#             */
/*   Updated: 2024/01/29 23:09:25 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	import_history(void)
{
	int		fd;
	char	*line;
	char	*trimmed_line;
	char	*path;

	path = ft_strjoin(getenv("HOME"), "/minishell_history");
	fd = open(path, O_RDONLY);
	printf("path=%s, fd=%d\n", path, fd);
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
		line = get_next_line(fd);
		trimmed_line = ft_strtrim(line, "\n");
		close(fd);
	}
	free(path);
}

void	ft_write_history(char *line)
{
	int		fd;
	char	*path;
	char	*line_with_newline;

	if (line && !ft_strlen(line))
		return ;
	path = ft_strjoin(getenv("HOME"), "/minishell_history");
	add_history(line);
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	printf("path=%s, fd=%d\n", path, fd);
	if (fd >= 0)
	{
		line_with_newline = ft_strjoin(line, "\n");
		write(fd, line_with_newline, ft_strlen(line_with_newline));
		free(line_with_newline);
		close(fd);
	}
	free(path);
}

int	main(void)
{
	char	*line;
	char	cwd[2000];
	struct termios ter;

	tcgetattr(1, &ter);
	//ter.c_lflag |= ECHOCTL;
	//ter.c_lflag |= ICANON;
	tcsetattr(1, 0, &ter);
	printf("%s\n", getcwd(cwd, 2000));
	import_history();
	while (1)
	{
		line = readline(">>>");
		if (!line)
			break ;
		ft_write_history(line);
		printf("input=%s\n", line);
		free(line);
	}
	return (0);
}