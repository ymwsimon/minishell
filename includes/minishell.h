/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:45:03 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/06 19:17:32 by mayeung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define NO_REDIRECT 0 
# define FROM_FILE 1
# define FROM_HERE_DOC 2
# define TO_FILE 3
# define APPEND_FILE 4
# define FROM_PIPE 5
# define TO_PIPE 6
# define CMD_NOT_FOUND 127

# define ALLOCATE_FAIL -1
# define PARSE_FAIL 0
# define PARSE_OK 1
# define IMCOMPELETE_CMD 2

typedef enum e_token_type
{
	RAW,
	PIPE,
	HERE_DOC,
	INPUT,
	OUTPUT,
	APPEND,
	CMD,
	ARG,
	INFILE,
	OUTFILE,
	DELIMITER,
	OPEN_DOUBLE_QUOTE,
	OPEN_SINGLE_QUOTE,
	OPEN_PAREN,
	CLOSE_PAREN
}			t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	tok;
}				t_token;

typedef struct s_cmd
{

	char	*cmd;
	char	**args;
	char	**env;
	char	*infile;
	char	*outfile;
	int		*fds;
	int		infd;
	int		outfd;
	int		in_redir;
	int		out_redir;
}				t_cmd;

#endif