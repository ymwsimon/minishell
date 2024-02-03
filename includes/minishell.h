/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:45:03 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/02 23:26:38 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define NO_REDIRECT 0 
# define FROM_FILE 1
# define HERE_DOC 2
# define TO_FILE 3
# define APPEND_FILE 4
# define FROM_PIPE 5
# define TO_PIPE 6
# define CMD_NOT_FOUND 127

typedef struct s_cmd   {

    char    *cmd;
    char    **args;
    char    **env;
    char    *infile;
    char    *outfile;
    int     *fds;
    int     infd;
    int     outfd;
    int     in_redir;
    int     out_redir;
}   t_cmd;

# include <readline/readline.h>
# include <readline/history.h>
# include "get_next_line.h"
# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

#endif