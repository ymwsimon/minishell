/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:45:03 by mayeung           #+#    #+#             */
/*   Updated: 2024/02/13 21:42:00 by mayeung          ###   ########.fr       */
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

# define OPENPAR_AND_OR_PIPE 1
# define PAREN 2

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
	CLOSE_PAREN,
	AND,
	OR,
	SIMPLE_CMD,
	SUBSHELL
}			t_token_type;

typedef struct s_cmd
{
	char	**args;
	char	**redirs;
	char	**here_doc_files;
}				t_cmd;

typedef struct s_token
{
	char			*str;
	t_cmd			*cmd;
	t_token_type	toktype;
}				t_token;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_token			*tok;
}				t_ast;
//get_next_line
char	*get_next_line(int fd);
//input_history
void	ft_import_history(void);
void	ft_trim_write_history(char **line);
//tokenizer
t_list	*ft_tokenize(char *line);
//is_type_str
int		ft_is_double_quote(char *str);
int		ft_is_single_quote(char *str);
int		ft_is_open_paren(char *str);
int		ft_is_close_paren(char *str);
int		ft_is_pipe(char *str);
//is_type_str2
int		ft_is_here_doc(char *str);
int		ft_is_input(char *str);
int		ft_is_output(char *str);
int		ft_is_append(char *str);
int		ft_is_and(char *str);
//is_type_str3
int		ft_is_or(char *str);
int		ft_is_redir(char *str);
//is_type_tok
int		ft_is_double_quote_tok(t_token *t);
int		ft_is_single_quote_tok(t_token *t);
int		ft_is_open_paren_tok(t_token *t);
int		ft_is_close_paren_tok(t_token *t);
int		ft_is_pipe_tok(t_token *t);
//is_type_tok2
int		ft_is_here_doc_tok(t_token *t);
int		ft_is_input_tok(t_token *t);
int		ft_is_output_tok(t_token *t);
int		ft_is_append_tok(t_token *t);
int		ft_is_and_tok(t_token *t);
//is_type_tok3
int		ft_is_or_tok(t_token *t);
int		ft_is_redir_tok(t_token *t);
int		ft_is_arg_tok(t_token *t);
int		ft_is_delimiter_tok(t_token *t);
//is_type_tok4
int		ft_is_infile_tok(t_token *t);
int		ft_is_outfile_tok(t_token *t);
int		ft_is_raw_tok(t_token *t);
//is_valid_tok
int		ft_valid_pipe_tok(t_list *node, t_token *tok);
int		ft_valid_input_tok(t_list *node, t_token *tok);
int		ft_valid_output_tok(t_list *node, t_token *tok);
int		ft_valid_here_doc_tok(t_list *node, t_token *tok);
int		ft_valid_append_tok(t_list *node, t_token *tok);
//is_valid_tok2
int		ft_valid_infile_tok(t_list *node, t_token *tok);
int		ft_valid_delimiter_tok(t_list *node, t_token *tok);
int		ft_valid_outfile_tok(t_list *node, t_token *tok);
int		ft_valid_and_tok(t_list *node, t_token *tok);
int		ft_valid_arg_tok(t_list *node, t_token *tok);
//is_valid_tok3
int		ft_valid_open_paren_tok(t_list *node, t_token *tok, int *open_par);
int		ft_valid_close_paren_tok(t_list *node, t_token *tok, int *open_par);
int		ft_valid_or_tok(t_list *node, t_token *tok);
//parser
int		ft_parse_token(t_list *node);
int		ft_invalid_tok(t_list *n);
int		ft_need_more_input(t_token *t, int open_paren);
//token_utils
int		ft_push_token_to_list(t_list **list, char *str);
void	ft_print_enum(t_token_type tok);
void	ft_print_tokens(t_list *tokens);
void	ft_free_token_node(void *n);
//char_arr_utils
void	*ft_clear_char_arr(char **arr);
//build_ast
t_ast	*ft_build_ast(t_list *tokens);
void	ft_print_ast(t_ast *node);
void	ft_free_ast(t_ast *node);
//made_here_doc
int		ft_create_here_doc(t_ast *node, int *id);
#endif