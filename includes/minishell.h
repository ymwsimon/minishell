/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeung <mayeung@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:45:03 by mayeung           #+#    #+#             */
/*   Updated: 2024/03/11 17:43:49 by mayeung          ###   ########.fr       */
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
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <dirent.h>

# define HISTORY_FILE_NAME "/.minishell_cmd_history"
# define HERE_DOC_PREFIX ".here_doc_"
# define HD_NULL_MSG "warning: here-document delimited by end-of-file"
# define HD_NULL_MSG2 " (wanted `%s')\n"
# define PROMPT "minishell>>> "
# define PROMPT_CON "> "
# define FALSE 0
# define TRUE 1
# define ALLOCATE_FAIL -1
# define PARSE_OK 0
# define PARSE_FAIL 1
# define NO_PARSE_RESULT 2
# define IMCOMPELETE_CMD 3
# define OPEN_QUOTE 4
# define EMPTY_INPUT 5
# define EXE_SUCCESS 0
# define EXE_FAILURE 1
# define EXE_GENERAL 3
# define LEFT_CHILD 4
# define RIGHT_CHILD 5
# define SIGNAL_ERROR 6
# define INVALID_POINTER 7
# define OPENPAR_AND_OR_PIPE 1
# define PAREN 2
# define SIGINT_CODE 130
# define SIGQUIT_CODE 131

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
	t_token_type	toktype;
	char			*str;
}				t_token;

typedef struct s_ast
{
	t_token_type	toktype;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_vars
{
	t_list	*toklist;
	t_ast	*ast;
	char	**env;
	int		last_exe_res;
	int		break_readline;
	int		exe_stop_by_sig;
}				t_vars;

typedef enum s_err_fd
{
	EFD_SUCCESS,
	EFD_GENERAL,
	EFD_EXEC = 126,
	EFD_NOT_FOUND,
	EFD_CMD_EXEC = 255
}	t_err_fd;

typedef enum s_err_msg
{
	ERR_NO_SUCH_FILE,
	ERR_PERM_DENIED,
	ERR_CMD_NOT_FOUND,
	ERR_IS_DIR,
	ERR_INVALID_EXPORT,
	ERR_SINGLE_DOT
}	t_err_msg;

typedef struct s_err
{
	t_err_fd	fd;
	t_err_msg	msg;
	char		*file;
}	t_err;

//get_next_line
char	*get_next_line(int fd);
//input_history
int		ft_space_only(char *str);
void	ft_import_history(void);
void	ft_write_history(char *line);
//tokenizer
t_list	*ft_tokenize(char *line);
int		tokenize_helper1(t_list **stack, size_t *j, size_t i, char *line);
int		tokenize_helper2(t_list **stack, t_list **res);
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
int		ft_is_newline(char *str);
int		ft_is_redir(char *str);
int		ft_is_builtin(char *str);
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
int		ft_is_open_quote(t_token *t);
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
void	ft_parse_token_helper1(t_list **node, t_token *last, int *open_paren);
int		ft_parse_token_helper(t_list **node, t_token *last, int *open_paren);
int		ft_parse_token(t_list *node);
int		ft_invalid_tok(t_list *n);
int		ft_need_more_input(t_token *t, int open_paren);
//token_utils
int		ft_push_token_to_list(t_list **list, char *str);
void	ft_free_token_node(void *n);
//char_utils
void	*ft_clear_char_arr(char **arr);
char	*ft_free_join_str(char *str1, char *str2);
size_t	ft_char_arr_size(char **arr);
char	*ft_create_unexpected_message(char *str);
//build_ast
int		ft_build_ast(t_ast **ast, t_list *tokens);
//build_ast2
int		ft_break_into_sc(t_ast **ast, t_list *tokens);
void	ft_free_ast(t_ast **node, int del_hd);
//create_here_doc
int		ft_create_here_doc(t_ast *node, int *id);
//fill_here_doc
int		ft_fill_here_doc(t_ast *node);
//exection
int		ft_execute(t_ast *ast);
int		ft_exec_subshell(t_ast *ast);
int		ft_exec_pipe(t_ast *ast, int status);
int		ft_exec_pipe_child(t_ast *ast, int child, int *pfds);
//exec_simple_cmd
int		ft_exec_simple_cmd(t_cmd *cmd);
int		ft_exec_redir(char **here_doc, char **redir);
int		ft_exec_program(char **args);
//exec_redir
int		ft_here_doc(char *here_doc);
int		ft_input(char *redir);
int		ft_output(char *redir);
int		ft_append(char *redir);
//exec_utils
void	ft_r_fd(int *original);
int		ft_get_exit_status(int status);
int		ft_err_msg(t_err err);
//check_file
t_err	ft_check_read(char *file);
t_err	ft_check_write(char *file);
t_err	ft_check_exec(char *path, char *file, int need_slash);
int		ft_check_dir(char *file, int need_slash);
//get_full_path
char	*ft_getfullpath(char *pname, char *res);
//handle_env_quote
char	*ft_string_resolve(char *str, int is_deli);
//echo
int		ft_echo(char **args);
//cd
int		ft_cd(char **args);
//pwd
int		ft_pwd(void);
//export
int		ft_export(char **args);
int		ft_search_string_arr_prefix(char **arr, char *str, int full_len);
//vars
t_vars	*ft_vars(void);
int		ft_event(void);
//unset
int		ft_unset(char **args);
//env
int		ft_env(char **args);
int		ft_print_env(void);
char	**ft_cpy_env(char **arr);
char	*ft_getenv(char *str);
//exit
int		ft_exit(char **args);
void	ft_free_res(int del_hd);
//builtins_utils
int		ft_exec_builtin(char **args);
//get_user_input
int		ft_get_user_input(void);
//signal
void	ft_signal_handler_waiting_input(int i);
void	ft_signal_handler_exe_parent(int i);
void	ft_signal_handler_exe_child(int i);
int		ft_setup_signal_handler_child(int using_readline);
//signal2
int		ft_default_signal(void);
int		ft_ignore_signal(void);
int		ft_setup_signal_handler_parent(void);

#endif
