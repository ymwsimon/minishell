/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:43:35 by mayeung           #+#    #+#             */
/*   Updated: 2024/01/29 21:29:55 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
		i++;
	j = 0;
	while (s2 && s2[j])
		j++;
	res = malloc(sizeof(char) * (i + j + 1));
	if (!res)
		return (NULL);
	i = -1 * (s1 != NULL);
	while (s1 && s1[++i])
		res[i] = s1[i];
	j = -1 * (s2 != NULL);
	while (s2 && s2[++j])
		res[i + j] = s2[j];
	res[i + j] = 0;
	return (res);
}

char	*ft_strdup(char *str)
{
	char	*res;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_res_update_remain(char **remain, char *buf, int rs, char *new_re)
{
	char	*res;

	free(buf);
	if (!remain)
		return (NULL);
	if (rs == -1 || !(*remain))
		return (free(*remain), *remain = NULL, NULL);
	if (!ft_strchr(*remain, '\n') || !(*(ft_strchr(*remain, '\n') + 1)))
	{
		res = ft_strdup(*remain);
		if (!res)
			return (NULL);
	}
	else
	{
		new_re = ft_strdup(ft_strchr(*remain, '\n') + 1);
		if (!new_re)
			return (NULL);
		*(ft_strchr(*remain, '\n') + 1) = 0;
		res = ft_strdup(*remain);
		if (!res)
			return (free(new_re), NULL);
	}
	return (free(*remain), *remain = new_re, res);
}

char	*get_next_line(int fd)
{
	static char	*remain = NULL;
	char		*buffer;
	char		*old_mem;
	int			readsize;

	if (fd < 0)
		return (NULL);
	readsize = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (readsize > 0 && !(remain && ft_strchr(remain, '\n')))
	{
		readsize = read(fd, buffer, BUFFER_SIZE);
		if (readsize > 0)
		{
			buffer[readsize] = 0;
			old_mem = remain;
			remain = ft_strjoin(remain, buffer);
			if (!remain)
				return (free(buffer), NULL);
			free(old_mem);
		}
	}
	return (ft_res_update_remain(&remain, buffer, readsize, NULL));
}
