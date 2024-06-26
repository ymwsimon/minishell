NAME = minishell

SRCS = 	main \
		get_next_line \
		input_history \
		tokenizer/is_type_str \
		tokenizer/is_type_str2 \
		tokenizer/is_type_str3 \
		parser/is_type_tok \
		parser/is_type_tok2 \
		parser/is_type_tok3 \
		parser/is_type_tok4 \
		parser/is_valid_tok \
		parser/is_valid_tok2 \
		parser/is_valid_tok3 \
		parser/parser \
		tokenizer/token_utils \
		tokenizer/tokenizer \
		build_ast \
		build_ast2 \
		char_utils \
		create_here_doc \
		fill_here_doc \
		handle_env_quote \
		get_full_path \
		vars \
		get_user_input \
		signal \
		signal2 \
		builtins/cd \
		builtins/echo \
		builtins/env \
		builtins/exit \
		builtins/export \
		builtins/pwd \
		builtins/unset \
		builtins/builtins_utils \
		execution/exec_simple_cmd \
		execution/exec_utils \
		execution/execution \
		execution/exec_redir \
		execution/check_file \

SRCS_DIR = srcs

OBJS = $(SRCS:%=$(OBJ_DIR)/%.o)

OBJ_DIR = obj

INC_DIR = includes

FLAGS = -Wall -Werror -Wextra

LIBFT_DIR = lib/libft

LIBFT = libft.a

LIBS = -lreadline -lft -L$(LIBFT_DIR)

CC = cc

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT_DIR)/$(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/tokenizer
	@mkdir -p $(OBJ_DIR)/execution
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/execution
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT_DIR)/$(LIBFT) :
	make -C $(LIBFT_DIR) bonus

clean :
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)/*

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(OBJ_DIR)
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re