NAME = minishell

SRCS = main get_next_line input_history is_type_str is_type_str2 is_type_str3 is_type_tok \
		is_type_tok2 is_type_tok3 is_type_tok4 is_valid_tok is_valid_tok2 is_valid_tok3 \
		parser token_utils tokenizer

SRCS_DIR = srcs

OBJS = $(SRCS:%=$(OBJ_DIR)/%.o)

OBJ_DIR = obj

INC_DIR = includes

FLAGS = -Wall -Werror -Wextra -g

LIBFT_DIR = lib/libft

LIBFT = libft.a

LIBS = -lreadline -lft -L$(LIBFT_DIR)

CC = cc

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT_DIR)/$(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(OBJ_DIR)/%.o : $(SRCS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT_DIR)/$(LIBFT) :
	make -C $(LIBFT_DIR) bonus

clean :
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)/*.o

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re : clean all

.PHONY : all clean fclean re