/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:05:05 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/12 19:37:33 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_resolve_env_var_only(char **res, char *str)
{
	size_t	i;
	size_t	j;

	if (!str || !res)
		return ;
	*res = ft_strdup("");
	i = 0;
	//printf("str:%s\n", str);
	while (str[i])
	{
		j = i;
		if (str[i] == '$')
			*res = ft_free_join_str(*res, ft_convert_env_var(str, i + 1, &j));
		else
		{
			if (str[i] == '\'' || str[i] == '"')
				while (str[++j] && (str[j] != str[i]))
					;
			else
				while (str[j] && !ft_strchr("\"'$", str[j]))
					j++;
			*res = ft_free_join_str(*res, ft_substr(str, i,
					j + (ft_strchr("\"'", str[i]) != NULL) - i));
		}
		//printf("i%ld j%ld\n", i, j);
		i = j + (ft_strchr("\"'", str[i]) != NULL);
		//printf("new i%ld j%ld\n", i, j);
	}
	//printf("new str:%s\n", *res);
}

int	ft_arg_to_linkedlist(t_list **res, char *arg)
{
	size_t	i;
	size_t	j;
	//DIR		*dir;

	*res = NULL;
	i = 0;
	while (arg && arg[i])
	{
		j = i;
		i = j;
	}
	return (EXE_SUCCESS);
}
